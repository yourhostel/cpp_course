//
// Created by tysser on 02.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/records_view.cpp
#include "records_view.h"
#include "../ui_rental.h"

#include <QTextEdit>
#include <QPushButton>

RecordsView::RecordsView(Ui_Rental* ui,
                         QStandardItemModel* tapesModel,
                         QObject* parent)
    : QObject(parent),
      ui(ui),
      tapesModel(tapesModel)
{
    // прив'язуємо кнопки
    QObject::connect(ui->rvForwardButton,  &QPushButton::clicked,
                     this, &RecordsView::onForwardClicked);

    QObject::connect(ui->rvBackwardButton, &QPushButton::clicked,
                     this, &RecordsView::onBackwardClicked);
}

QString RecordsView::formatTapeLine(const int row) const
{
    if (!tapesModel || row < 0 || row >= tapesModel->rowCount())
        return {};

    // "Назва"
    const QStandardItem* titleItem = tapesModel->item(row, 1);
    // "Тип"
    const QStandardItem* typeItem  = tapesModel->item(row, 2);

    const QString title = titleItem ? titleItem->text() : "";
    const QString type  = typeItem  ? typeItem->text()  : "";

    // формат: Назва<пробіл>Тип
    return title + " " + type;
}

QString RecordsView::buildText(const bool forward) const
{
    QStringList lines;

    if (!tapesModel || tapesModel->rowCount() == 0)
        return {};

    if (forward)
    {
        for (int r = 0; r < tapesModel->rowCount(); ++r)
            lines << formatTapeLine(r);
    }
    else
    {
        for (int r = tapesModel->rowCount() - 1; r >= 0; --r)
            lines << formatTapeLine(r);
    }

    return lines.join('\n');
}

void RecordsView::onForwardClicked() const
{
    ui->rvForwardTextEdit->setPlainText(buildText(true));
}

void RecordsView::onBackwardClicked() const
{
    ui->rvBackwardTextEdit->setPlainText(buildText(false));
}
