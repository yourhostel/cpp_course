//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/filtering_view.h
#ifndef CPP_COURSE_FILTERING_VIEW_H
#define CPP_COURSE_FILTERING_VIEW_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

#include "date_filter_proxy.h"

class Ui_Rental;

class FilteringView : public QObject
{
    Q_OBJECT

public:
    FilteringView(Ui_Rental* ui,
                  QStandardItemModel* tapesModel,
                  QStandardItemModel* rentalsModel,
                  QObject* parent = nullptr);

private:
    Ui_Rental* ui;
    QStandardItemModel* tapesModel;
    QStandardItemModel* rentalsModel;

    QSortFilterProxyModel* tapesProxy;
    DateFilterProxyModel* rentalsProxy;

private slots:
    void onTitleChanged(const QString& text) const;
    void onTitleCheckChanged(bool) const;
    void onDateCheckChanged(bool) const;
    void onDateFromChanged(const QDate&) const;
    void onDateToChanged(const QDate&) const;

public slots:
    void reloadView() const;
};

#endif //CPP_COURSE_FILTERING_VIEW_H