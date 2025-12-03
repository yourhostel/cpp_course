//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/search_view.h
#ifndef CPP_COURSE_SEARCH_VIEW_H
#define CPP_COURSE_SEARCH_VIEW_H

#include <QObject>
#include <QStandardItemModel>

class Ui_Rental;

class SearchView final : public QObject
{
    Q_OBJECT

public:
    SearchView(Ui_Rental* ui,
               QStandardItemModel* tapesModel,
               QStandardItemModel* rentalsModel,
               QStandardItemModel* customersModel,
               QObject* parent = nullptr);
    void fillCombo();

private:
    Ui_Rental* ui;
    QStandardItemModel* tapesModel;
    QStandardItemModel* rentalsModel;
    QStandardItemModel* customersModel;

private:
    void moveCursorClients(int row) const;
    void moveCursorRentals(int row) const;

    [[nodiscard]] int findClientRowByName(const QString& text) const;
    [[nodiscard]] int findRentalRow(const QDate& date,
                      const QString& clientCode) const;
    bool lookupTape(const QString& title,
                    const QString& type,
                    QString& outCode,
                    QString& outPrice) const;

private slots:
    void onSearchByName();
    void onSearchTwoFields();
    void onSearchLookup();

    void onClientsFirst();
    void onClientsPrev();
    void onClientsNext();
    void onClientsLast();

    void onRentalsFirst();
    void onRentalsPrev();
    void onRentalsNext();
    void onRentalsLast();
public slots:
    void reloadView();
};

#endif //CPP_COURSE_SEARCH_VIEW_H