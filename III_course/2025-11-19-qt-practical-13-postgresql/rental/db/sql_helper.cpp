//
// Created by tysser on 21.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/db/sql_helper.cpp
#include "sql_helper.h"

#include <QSqlError>
#include <QSqlQuery>

#include "debug_log.h"

/** ========================================================================
 * Завантажує дані таблиці з PostgreSQL у QStandardItemModel.
 *
 * Алгоритм:
 *   1) Сформувати SQL-запит виду:
 *        SELECT idColumn, col1, col2, ... FROM tableName ORDER BY idColumn.
 *   2) Виконати запит через QSqlQuery.
 *   3) Якщо виконання неуспішне, зберегти текст помилки у error
 *      та повернути false.
 *   4) Очистити модель через removeRows().
 *   5) Для кожного рядка результату q.next():
 *        - вставити новий рядок у модель,
 *        - записати значення ID у колонку 0,
 *        - записати значення кожної колонки у відповідні позиції.
 *   6) Повернути true після успішного завантаження.
 *
 * Призначення:
 *   Використовується для синхронізації UI-моделей (касети, клієнти, прокат)
 *   з реальними даними у PostgreSQL. Формує модель, з якої таблиці Qt
 *   безпосередньо відображають дані у UI.
 *
 * @param model Модель, яку потрібно заповнити.
 * @param spec  Специфікація таблиці (назва, ID-колонка, список колонок).
 * @param error Текст помилки у випадку неуспішного виконання.
 *
 * @return true, якщо дані успішно завантажено; false, при помилці SQL.
 */
bool SqlHelper::loadModel(QStandardItemModel* model,
                          const TableSpec& spec,
                          QString& error) const
{
    QSqlQuery q(db_);

    // Формуємо SELECT
    QString sql = "SELECT " + spec.idColumn;
    for (const auto& col : spec.columns)
        sql += ", " + col;

    sql += " FROM " + spec.tableName +
           " ORDER BY " + spec.idColumn;

    if (!q.exec(sql))
    {
        error = q.lastError().text();
        return false;
    }

    model->removeRows(0, model->rowCount());

    int row = 0;
    while (q.next())
    {
        model->insertRow(row);

        // id (колонка 0)
        model->setItem(row, 0,
                       new QStandardItem(q.value(0).toString()));

        // інші колонки
        for (int i = 0; i < spec.columns.size(); i++)
        {
            model->setItem(row, i + 1, new QStandardItem(q.value(i + 1).toString()));
        }
        row++;
    }

    return true;
}

/** ========================================================================
 * Зберігає всі зміни з моделі у відповідну таблицю PostgreSQL.
 *
 * Алгоритм:
 *   Для кожного рядка моделі:
 *     1) Отримати значення ID з колонки 0.
 *     2) Якщо комірка відсутня, пропустити рядок.
 *     3) Зібрати значення всіх інших колонок у список values.
 *
 *     Вставка нового запису:
 *       - Якщо ID порожній або дорівнює "-":
 *           а) сформувати INSERT INTO ... RETURNING idColumn;
 *           б) підготовити запит q.prepare(sql);
 *           в) передати всі значення через bindValue();
 *           г) виконати запит; якщо помилка, повернути false;
 *           д) зчитати новий ID через q.next() і записати його у модель.
 *
 *     Оновлення існуючого запису:
 *       - Якщо ID непорожній:
 *           а) сформувати UPDATE table SET col=:col ... WHERE idColumn=:id;
 *           б) підготувати запит та прив’язати значення;
 *           в) виконати q.exec(); при помилці — повернути false.
 *
 *   4) Якщо всі рядки оброблено без помилок — повернути true.
 *
 * Призначення:
 *   Узгоджує стан UI-моделі з базою даних. Дозволяє одночасно
 *   обробляти зміни, нові рядки та редагування існуючих записів.
 *   Працює універсально для будь-якої таблиці, описаної у TableSpec.
 *
 * @param model Модель, з якої беруться значення для збереження.
 * @param spec  Опис структури таблиці (ID-колонка та поле columns).
 * @param error Текст помилки SQL у випадку невдалого виконання.
 *
 * @return true, якщо всі операції INSERT/UPDATE успішно виконано.
 */
bool SqlHelper::saveModel(QStandardItemModel* model,
                          const TableSpec& spec,
                          QString& error) const
{
    QSqlQuery q(db_);
    QSet<QString> newIdSet;

    for (int r = 0; r < model->rowCount(); r++)
    {
        DLOG("ROW" << r);
        // колонка ID
        const QStandardItem* idItem = model->item(r, 0);
        DLOG("ID item =" << idItem);
        if (!idItem) continue; // порожній рядок, пропускаємо

        const QString id = idItem->text().trimmed();

        DLOG("ID =" << id);
        // збираємо значення колонок
        QVector<QString> values;
        values.reserve(spec.columns.size());

        for (int i = 0; i < spec.columns.size(); i++)
        {
            const QStandardItem* item = model->item(r, i + 1);

            QString v = item ? item->text().trimmed() : "";

            DLOG("col" << spec.columns[i] << "=" << v);
            values.push_back(v);
        }

        if (id == "-" || id.isEmpty())
        {
            QString sql = "INSERT INTO " + spec.tableName + " (";
            QString vals = "VALUES (";
            DLOG("SQL INSERT:" << sql);
            DLOG("VALUES:" << values);

            for (const auto& col : spec.columns)
            {
                sql += col + ",";
                vals += ":" + col + ",";
            }

            sql.chop(1);
            vals.chop(1);

            sql += ") " + vals + ") RETURNING " + spec.idColumn;

            q.prepare(sql);

            for (int i = 0; i < spec.columns.size(); i++)
                q.bindValue(":" + spec.columns[i], values[i]);

            if (!q.exec())
            {
                error = q.lastError().text();
                return false;
            }

            if (q.next())
            {
                const QString newId = q.value(0).toString();
                model->setItem(r, 0, new QStandardItem(newId));
                newIdSet.insert(newId);
            }
        }
        else
        {
            QString sql = "UPDATE " + spec.tableName + " SET ";
            DLOG("SQL UPDATE:" << sql);
            DLOG("VALUES:" << values);

            for (const auto& col : spec.columns)
                sql += col + "=:" + col + ",";

            sql.chop(1);
            sql += " WHERE " + spec.idColumn + "= :id";

            q.prepare(sql);
            DLOG("SQL ERROR:" << q.lastError().text());
            for (int i = 0; i < spec.columns.size(); i++)
                q.bindValue(":" + spec.columns[i], values[i]);

            q.bindValue(":id", id);

            if (!q.exec())
            {
                error = q.lastError().text();
                return false;
            }

            newIdSet.insert(id);
        }
    }

    return true;
}

bool SqlHelper::deleteRow(const TableSpec& spec, int id, QString& error) const
{
    QSqlQuery q(db_);

    const QString sql = "DELETE FROM " + spec.tableName +
                  " WHERE " + spec.idColumn + " = :id";

    q.prepare(sql);
    q.bindValue(":id", id);

    if (!q.exec())
    {
        error = q.lastError().text();
        return false;
    }

    return true;
}

