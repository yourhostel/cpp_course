//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/records_view.h
#ifndef CPP_COURSE_RECORDS_VIEW_H
#define CPP_COURSE_RECORDS_VIEW_H

#include <QStandardItemModel>

class Ui_Rental;

class RecordsView final : public QObject
{
    Q_OBJECT

public:
    explicit RecordsView(Ui_Rental* ui,
                         QStandardItemModel* tapesModel,
                         QObject* parent = nullptr);

private:
    Ui_Rental* ui;
    QStandardItemModel* tapesModel;

    // "Назва Тип"
    [[nodiscard]] QString formatTapeLine(int row) const;
    // збирає всі рядки
    [[nodiscard]] QString buildText(bool forward) const;

private slots:
    void onForwardClicked() const;
    void onBackwardClicked() const;
};

#endif //CPP_COURSE_RECORDS_VIEW_H