//
// Created by tysser on 01.12.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/tabs/visual_components.h
#ifndef CPP_COURSE_VISUAL_COMPONENTS_H
#define CPP_COURSE_VISUAL_COMPONENTS_H

#include "sql_helper.h"

class Ui_Rental; // forward declaration не тягнемо весь ui

class VisualComponents final : public QObject
{
    Q_OBJECT

    TableSpec tapeSpec;
    TableSpec rentalSpec;

public:
    explicit VisualComponents(Ui_Rental* ui,
                              QStandardItemModel* tapesModel,
                              QStandardItemModel* customersModel,
                              QStandardItemModel* rentalsModel,
                              SqlHelper* helper,
                              QObject* parent = nullptr);

    void loadFirstTape();
    [[nodiscard]] QString getTapeNameById(int id) const;
    [[nodiscard]] QString getCustomerNameById(int id) const;
    void loadFirstRental();

private:
    Ui_Rental* ui;
    QStandardItemModel* tapesModel;
    QStandardItemModel* customersModel;
    QStandardItemModel* rentalsModel;
    SqlHelper* helper;

    // Універсальна структура стану для скасування
private:
    struct EditState
    {
        bool adding = false;          // додавання чи ні
        bool editing = false;         // редагування чи ні
        int prevIndex = -1;           // індекс попереднього запису
        int newIndex = -1;            // індекс нового запису (якщо був add)
    };
    EditState tapeState;
    EditState rentalState;

private:
    int currentTapeIndex = 0;
    int currentRentalIndex = 0;

    // ==== helpers ====
    void loadTapeFields(int row);
    void fillTapeCombo() const;
    void loadRentalFields(int row);
    void fillCustomerCombo() const;
    void setTapeFieldsEditable(bool enabled) const;
    void setRentalFieldsEditable(bool enabled) const;
    void clearTapeFields() const;
    void clearRentalFields() const;
    [[nodiscard]] int findTapeIdByName(const QString& name) const;
    [[nodiscard]] int findCustomerIdByName(const QString& name) const;
    static bool askCancelEditing(const QString& title = "Увага",
                                 const QString& message = "Скасувати?");

private slots:
    // ===== NAV TAPE =====
    void onTapeFirst();
    void onTapePrev();
    void onTapeNext();
    void onTapeLast();
    bool checkTapeEditingBeforeNavigate();

    // ===== NAV RENTAL =====
    void onRentalFirst();
    void onRentalPrev();
    void onRentalNext();
    void onRentalLast();
    bool checkRentalEditingBeforeNavigate();

    // ===== TAPE BUTTONS =====
    void onTapeAdd();
    void onTapeEdit();
    void onTapeDelete();
    void onTapeCancel();
    void onTapeSave();

    // ===== RENTAL BUTTONS =====
    void onRentalAdd();
    void onRentalEdit();
    void onRentalDelete();
    void onRentalCancel();
    void onRentalSave();
};


#endif //CPP_COURSE_VISUAL_COMPONENTS_H