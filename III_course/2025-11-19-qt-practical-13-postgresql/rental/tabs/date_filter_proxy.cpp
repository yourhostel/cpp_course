//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/date_filter_proxy.cpp
#include "date_filter_proxy.h"

DateFilterProxyModel::DateFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{}

void DateFilterProxyModel::setEnabled(bool on)
{
    enabled = on;
    invalidateFilter();
}

void DateFilterProxyModel::setDateRange(QDate f, QDate t)
{
    from = f;
    to = t;
    invalidateFilter();
}

bool DateFilterProxyModel::filterAcceptsRow(const int sourceRow,
                                            const QModelIndex& sourceParent) const
{
    if (!enabled)
        return true;

    const QModelIndex idx = sourceModel()->index(sourceRow, 3);
    const QDate d = QDate::fromString(idx.data().toString(), "yyyy-MM-dd");

    return (d >= from && d <= to);
}
