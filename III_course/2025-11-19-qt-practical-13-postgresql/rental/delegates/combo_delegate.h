//
// Created by tysser on 21.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/delegates/combo_delegate.h
#ifndef CPP_COURSE_COMBO_DELEGATE_H
#define CPP_COURSE_COMBO_DELEGATE_H

#ifndef COMBO_DELEGATE_H
#define COMBO_DELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <utility>

/**
 * ComboDelegate
 *
 * Делегат для відображення та редагування комірок через QComboBox,
 * коли модель зберігає не текст, а числовий ID.
 *
 * Призначення:
 *   - показує у таблиці текстове значення відповідного елементу (фільм, клієнт);
 *   - при редагуванні відображає комбобокс з текстами, але у модель записує ID;
 *   - підтримує оновлення списку значень через метод updateData().
 *
 * Механіка:
 *   - texts_ містить список назв для відображення;
 *   - ids_ містить відповідні ID у тому ж порядку;
 *   - displayText() виконує маппінг ID => текст.
 */
class ComboDelegate final : public QStyledItemDelegate
{
public:
    /**
     * Конструктор делегата.
     *
     * Алгоритм:
     *   1) Виклик базового конструктора QStyledItemDelegate.
     *   2) Зберегти початкові списки текстів та ID.
     *
     * @param texts   Список текстових назв для комбобокса.
     * @param ids     Відповідний список IDs (у тому ж порядку).
     * @param parent  Батьківський QObject або nullptr.
     */
    ComboDelegate(QStringList  texts,
                  const QList<int>& ids,
                  QObject* parent = nullptr)
        : QStyledItemDelegate(parent),
          texts_(std::move(texts)),
          ids_(ids)
    {}

    /**
     * Оновлює внутрішні списки текстів та IDs.
     *
     * Використовується при зміні даних у моделях (каси, клієнти),
     * щоб делегат відображав актуальні значення.
     *
     * @param texts Новий список текстів.
     * @param ids   Новий список IDs.
     */
    void updateData(const QStringList& texts,
                    const QList<int>& ids)
    {
        texts_ = texts;
        ids_ = ids;
    }

private:
    // Список текстів (назви касет або ПІБ клієнтів).
    QStringList texts_;
    // Відповідні IDs елементів, що зберігаються у моделі.
    QList<int> ids_;

    /**
     * Створює редактор — QComboBox.
     *
     * Алгоритм:
     *   1) Створити QComboBox.
     *   2) Заповнити його елементами:
     *        - текст (visible text),
     *        - ID (UserRole).
     *   3) Повернути комбобокс як редактор.
     *
     * Примітка:
     *   Комбобокс показує текст, але дані записуються як ID.
     *
     * @param parent QWidget-батько редактора.
     * @return QWidget* — створений QComboBox.
     */
    QWidget* createEditor(QWidget* parent,
                          const QStyleOptionViewItem&,
                          const QModelIndex&) const override
    {
        auto *combo = new QComboBox(parent);

        for (int i = 0; i < texts_.size(); i++)
            combo->addItem(texts_[i], ids_[i]);  // UserRole = ID

        return combo;
    }

    /**
     * Встановлює поточне значення редактора (QComboBox)
     * відповідно до значення у моделі.
     *
     * Алгоритм:
     *   1) Отримати ID з моделі.
     *   2) Знайти елемент комбобокса, який має такий ID.
     *   3) Встановити відповідний індекс.
     *
     * @param editor Вказівник на QComboBox.
     * @param index  Індекс моделі, значення якої редагується.
     */
    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const override
    {
        auto* combo = dynamic_cast<QComboBox*>(editor);

        const int currentId = index.data().toInt();  // Модель зберігає ID

        if (const int idx = combo->findData(currentId); idx >= 0)
            combo->setCurrentIndex(idx);
    }

    /**
      * Повертає текст для відображення у таблиці
      * (коли комірка не у режимі редагування).
      *
      * Алгоритм:
      *   1) Отримати ID із значення комірки.
      *   2) Знайти ID у списку ids_.
      *   3) Якщо знайдено — повернути відповідний текст.
      *   4) Інакше — повернути сам ID.
      *
      * @param value Значення моделі (ID).
      * @return Текст для відображення.
      */
    [[nodiscard]] QString displayText(const QVariant &value, const QLocale &) const override
    {
        const int id = value.toInt();

        if (const int index = ids_.indexOf(id); index >= 0)
            return texts_[index];

        return QString::number(id);
    }

    /**
      * Записує вибране значення редактора у модель.
      *
      * Алгоритм:
      *   1) Витягти з комбобокса вибраний ID (UserRole).
      *   2) Записати ID у модель через setData().
      *
      * Примітка:
      *   У моделі зберігається саме ID, а не текст
      *   для SQL-зв'язків та збереження у базу.
      *
      * @param editor QComboBox з вибраним значенням.
      * @param model  Модель, у яку записується значення.
      * @param index  Індекс комірки моделі.
      */
    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override
    {
        const auto* combo = dynamic_cast<QComboBox*>(editor);
        const int id = combo->currentData().toInt();  // Дістали  ID
        model->setData(index, id);                 // Пишемо ID замість тексту
    }

};

#endif

#endif //CPP_COURSE_COMBO_DELEGATE_H