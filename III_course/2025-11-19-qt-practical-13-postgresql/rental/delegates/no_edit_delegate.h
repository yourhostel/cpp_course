//
// Created by tysser on 21.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/delegates/no_edit_delegate.h
#ifndef CPP_COURSE_NO_EDIT_DELEGATE_H
#define CPP_COURSE_NO_EDIT_DELEGATE_H

#include <QStyledItemDelegate>

class NoEditDelegate final : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget* createEditor(QWidget*,
                          const QStyleOptionViewItem&,
                          const QModelIndex&) const override
    {
        return nullptr;
    }
};


#endif //CPP_COURSE_NO_EDIT_DELEGATE_H