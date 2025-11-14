//
// Created by tysser on 14.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/pen_brush_tab.cpp
#include "pen_brush_tab.h"

#include "../canvas/canvas.h"
#include "../widgets/analog_clock.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QRandomGenerator>

// Макрос CHECK для діагностики.
// Якщо елемент інтерфейсу не знайдено (nullptr), виводимо в консоль його ім'я.
// Шукаємо що в .ui файл неправильно вказано objectName.
#define CHECK(x) \
if (!(x)) { qDebug() << "NOT FOUND:" << #x; }

// Конструктор PenBrushTab отримує кореневий QWidget вкладки та Canvas.
// uiRoot - це QWidget вкладки PenBrush у Qt Designer.
// canvas - це чорний буфер, на якому малюємо всі фігури.
// У конструкторі під'єднуємо кнопку Очистити, встановлюємо фільтр подій на Canvas
// і створюємо годинник усередині правого контейнера.
PenBrushTab::PenBrushTab(QWidget *uiRoot, Canvas *canvas)
    : QObject(uiRoot),
      uiRoot_(uiRoot),
      canvas_(canvas)
{
    // Розмір області малювання
    canvas_->setCanvasSize(500, 400);

    // Кнопка очищення канваса
    const auto btnClear = uiRoot_->findChild<QPushButton*>("penBrushBtnClear");
    CHECK(btnClear);

    connect(btnClear, &QPushButton::clicked, [this]
    {
        canvas_->clear();
    });

    // Підключаємо обробку миші
    canvas_->installEventFilter(this);

    // Годинник
    timerWidget_ = uiRoot_->findChild<QWidget*>("penBrushTimerWidget");
    clock_ = AnalogClock::attachTo(timerWidget_);
}

// Фільтрує події миші, щоб малювати при кліку
bool PenBrushTab::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == canvas_ && event->type() == QEvent::MouseButtonPress) {
        const auto *ev = dynamic_cast<QMouseEvent*>(event);
        handleClick(ev->position().toPoint());
        return true;
    }
    return QObject::eventFilter(obj, event);
}

// Центральна функція - при кліку малюємо фігуру/текст/заливку
void PenBrushTab::handleClick(const QPoint &pos) const
{
    QPainter p(&canvas_->buffer());
    p.setRenderHint(QPainter::Antialiasing);

    // Випадкові розміри фігур
    const int sx = QRandomGenerator::global()->bounded(40, 120);
    const int sy = QRandomGenerator::global()->bounded(40, 120);

    // Застосувати режим пера (SourceOver/Xor/Diff)
    applyPenMode(p);

    // Застосувати стиль пензля (заливка)
    applyBrushStyle(p);

    // Зчитуємо дію з групи "Дія"
    const auto g = uiRoot_->findChild<QGroupBox*>("penBrushActionGroup");
    CHECK(g);

    int idx = -1;
    {
        // Шукаємо обрану радіокнопку
        const auto buttons = g->findChildren<QRadioButton*>();
        for (int i = 0; i < buttons.size(); i++)
            if (buttons[i]->isChecked())
                idx = i;
    }

    // Виконуємо обрану дію
    switch (idx)
    {
    case 0: // прямокутник
        p.drawRect(pos.x(), pos.y(), sx, sy);
        break;

    case 1: // еліпс
        p.drawEllipse(pos.x(), pos.y(), sx, sy);
        break;

    case 2: // текст
        {
            QFont f;
            f.setPointSize(14); // розмір
            f.setBold(true); // жирний стиль
            p.setFont(f);

            p.setPen(Qt::white);
            p.drawText(pos + QPoint(0, -5), "Графіка в Qt6");
            break;
        }

    case 3: // випадкова заливка
        {
            const QColor c = QColor::fromHsv(
                QRandomGenerator::global()->bounded(360),
                255,
                200
            );
            p.setBrush(c);
            p.drawRect(pos.x(), pos.y(), sx, sy);
            break;
        }

    default:
        break;
    }

    canvas_->update(); // оновити видимість
}

// Стиль пензля (заливка фігур)
void PenBrushTab::applyBrushStyle(QPainter &p) const
{
    const auto g = uiRoot_->findChild<QGroupBox*>("brushStylesGroup");
    CHECK(g);

    int idx = -1;
    // Шукаємо обрану радіокнопку
    const auto buttons = g->findChildren<QRadioButton*>();

    for (int i = 0; i < buttons.size(); i++)
        if (buttons[i]->isChecked())
            idx = i;

    // Стандартна заливка — зелена
    QBrush brush(Qt::green);

    // Шаблони заливки фігур у середовищі Qt.
    // SolidPattern - суцільна заливка.
    // CrossPattern - заливка у вигляді двох перехрещених сіток.
    // DiagCrossPattern - діагональна перехресна сітка.
    // Dense5Pattern - дрібна крапчаста заливка.
    switch (idx)
    {
    case 0: brush.setStyle(Qt::SolidPattern);
        break;
    case 1: brush.setStyle(Qt::CrossPattern);
        break;
    case 2: brush.setStyle(Qt::DiagCrossPattern);
        break;
    case 3: brush.setStyle(Qt::Dense5Pattern);
        break;
    default: break;
    }

    p.setBrush(brush);
}

// Режим пера (аналог Pen->Mode в Builder)
void PenBrushTab::applyPenMode(QPainter &p) const
{
    const auto g = uiRoot_->findChild<QGroupBox*>("penModesGroup");
    CHECK(g);

    int idx = -1;
    // Шукаємо обрану радіокнопку
    const auto buttons = g->findChildren<QRadioButton*>();

    for (int i = 0; i < buttons.size(); i++)
        if (buttons[i]->isChecked())
            idx = i;

    // CompositionMode визначає, як новий піксель накладається на старий.
    // Це аналог режимів пера у C++ Builder (pmCopy, pmXor, pmNotXor).
    // CompositionMode_SourceOver - Звичайний режим. Новий колір накладається поверх старого.
    // CompositionMode_Xor - Логічне XOR змішування кольорів. Дозволяє отримувати ефект інверсії.
    // CompositionMode_Difference - Відображає різницю між кольорами, дає ефект негативу.
    switch (idx) {
    case 0:
        p.setCompositionMode(QPainter::CompositionMode_SourceOver);
        break;
    case 1:
        p.setCompositionMode(QPainter::CompositionMode_Xor);
        break;
    case 2:
        p.setCompositionMode(QPainter::CompositionMode_Difference);
        break;
    default:
        break;
    }

    p.setPen(QPen(Qt::white, 2));
}
