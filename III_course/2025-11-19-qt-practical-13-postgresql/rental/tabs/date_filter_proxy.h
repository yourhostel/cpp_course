//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/date_filter_proxy.h
#ifndef CPP_COURSE_DATE_FILTER_PROXY_H
#define CPP_COURSE_DATE_FILTER_PROXY_H

#include <QSortFilterProxyModel>
#include <QDate>

// Проксі-модель для фільтрації записів за діапазоном дат
class DateFilterProxyModel final : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit DateFilterProxyModel(QObject* parent = nullptr);

    // Вмикає або вимикає фільтрацію
    void setEnabled(bool enabled);

    // Встановлює діапазон дат
    void setDateRange(QDate from, QDate to);

protected:
    // Перевіряє, чи проходить рядок фільтр
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex& sourceParent) const override;

private:
    // Чи активен фільтр
    bool enabled = false;

    // Межі діапазону дат
    QDate from;
    QDate to;
};

#endif //CPP_COURSE_DATE_FILTER_PROXY_H