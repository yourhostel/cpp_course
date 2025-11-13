//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/tabs/pixel_pen_tab.cpp
#include "pixel_pen_tab.h"
#include "../canvas/canvas.h"
#include "../modules/astroid_math.h"

#include <QPushButton>
#include <QRadioButton>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

PixelPenTab::PixelPenTab(QWidget *uiRoot, Canvas *canvas)
    : QObject(uiRoot),   // QObject прив'язаний до uiRoot, щоб жити разом з вкладкою
      uiRoot_(uiRoot),   // зберігаємо вказівник на корінь UI вкладки
      canvas_(canvas)    // зберігаємо вказівник на канвас цієї вкладки
{
    // Потрібний розмір полотна для цієї вкладки
    canvas_->setCanvasSize(400, 400);

    // Дістаємо потрібні віджети за objectName з ui
    const auto btnPixel = uiRoot_->findChild<QPushButton*>("btnPixel");
    const auto btnPen   = uiRoot_->findChild<QPushButton*>("btnPen");
    const auto btnClear = uiRoot_->findChild<QPushButton*>("btnClear");

    const auto rPoints = uiRoot_->findChild<QRadioButton*>("radioPoints");
    const auto rLines  = uiRoot_->findChild<QRadioButton*>("radioLines");

    // Кнопка "Піксель" малює астроїду точками
    connect(btnPixel, &QPushButton::clicked, [this]
    {
        drawAstroidPixels();
    });

    // Кнопка "Перо" малює астроїду лінією від центру
    connect(btnPen, &QPushButton::clicked, [this]
    {
        drawAstroidPen();
    });

    // Кнопка "Очистити" стирає буфер і скидає стан лінійного режиму
    connect(btnClear, &QPushButton::clicked, [this]
    {
        canvas_->clear();
        hasLast_ = false;
    });

    // Режим "Точки" активує малювання пікселями по drag'у
    connect(rPoints, &QRadioButton::toggled, [this](const bool c)
    {
        if (c) {
            drawLines_ = false;
            hasLast_ = false; // скидаємо запам'ятовану точку для ліній
        }
    });

    // Режим "Відрізки" активує покрокове малювання ліній
    connect(rLines, &QRadioButton::toggled, [this](const bool c)
    {
        if (c) {
            drawLines_ = true;
            hasLast_ = false; // починаємо з чистого стану
        }
    });

    // Підписуємося на події миші на Canvas через eventFilter
    canvas_->installEventFilter(this);

    // Додаємо годинник
    clock_ = AnalogClock::attachTo(uiRoot_->findChild<QWidget*>("pixelPenTimerWidget"));
}

// Обробляємо події миші для конкретного Canvas
bool PixelPenTab::eventFilter(QObject *obj, QEvent *ev)
{
    // Якщо подія не від нашого canvas, віддаємо базовій реалізації
    if (obj != canvas_) return QObject::eventFilter(obj, ev);

    switch (ev->type())
    {
    case QEvent::MouseButtonPress:
    {
        const auto *me = dynamic_cast<QMouseEvent*>(ev);
        // Якщо режим точок - стартуємо drag малювання пікселями
        // Якщо режим відрізків - відпрацьовуємо черговий клік для лінії
        if (!drawLines_) handlePixelPress(me->pos());
        else             handlePenClick(me->pos());
        return true;
    }

    case QEvent::MouseMove:
    {
        // У режимі точок при затиснутій кнопці миші тягнемо "кисть"
        if (!drawLines_ && drawing_) {
            const auto *me = dynamic_cast<QMouseEvent*>(ev);
            handlePixelMove(me->pos());
        }
        return true;
    }

    case QEvent::MouseButtonRelease:
        // Для пікселів по відпусканню миші завершуємо drag
        if (!drawLines_) drawing_ = false;
        return true;

    default:
        // Все інше віддаємо базовому QObject
        return QObject::eventFilter(obj, ev);
    }
}

// Початок малювання пікселями при натисканні миші
void PixelPenTab::handlePixelPress(const QPoint &p)
{
    drawing_ = true;

    QPainter painter(&canvas_->buffer());
    painter.setPen(Qt::red);
    painter.drawPoint(p);

    canvas_->update();
}

// Продовження малювання пікселями при русі миші з затиснутою кнопкою
void PixelPenTab::handlePixelMove(const QPoint &p) const
{
    QPainter painter(&canvas_->buffer());
    painter.setPen(Qt::red);
    painter.drawPoint(p);

    canvas_->update();
}

// Логіка режиму "Перо" для покрокового малювання відрізків (click / click)
void PixelPenTab::handlePenClick(const QPoint &p)
{
    QPainter painter(&canvas_->buffer());
    painter.setPen(Qt::red);

    // Якщо це перший клік - запам'ятовуємо точку
    if (!hasLast_) {
        last_ = p;
        hasLast_ = true;
    } else {
        // Інакше проводимо відрізок від минулої точки до нової
        painter.drawLine(last_, p);
        last_ = p;
    }

    canvas_->update();
}

// Малювання астроїди пікселями
void PixelPenTab::drawAstroidPixels()
{
    canvas_->clear();

    QPainter p(&canvas_->buffer());
    p.setPen(Qt::blue);

    const int cx = canvas_->buffer().width()  / 2;
    const int cy = canvas_->buffer().height() / 2;

    // Обходимо параметр t по кроках і малюємо точки астроїди
    for (int i = 0; i <= ASTROID_STEPS; i++) {
        QPoint pt = AstroidMath::computePixel(i, ASTROID_A);
        p.drawPoint(cx + pt.x(), cy + pt.y());
    }

    canvas_->update();

    // Скидаємо стан для режиму ліній
    hasLast_ = false;
}

// Малювання астроїди "пером" з центру екрану
void PixelPenTab::drawAstroidPen()
{
    canvas_->clear();

    QPainter p(&canvas_->buffer());
    p.setPen(Qt::red);

    const int cx = canvas_->buffer().width()  / 2;
    const int cy = canvas_->buffer().height() / 2;

    QPainterPath path;

    // Стартуємо строго з центру
    path.moveTo(cx, cy);

    // Малюємо ламану, яка йде від центру до кривої астроїди
    for (int i = 0; i <= ASTROID_STEPS; i++){
        QPoint pt = AstroidMath::computePixel(i, ASTROID_A);
        path.lineTo(cx + pt.x(), cy + pt.y());
    }

    p.drawPath(path);
    canvas_->update();

    // Скидаємо стан для режиму ліній
    hasLast_ = false;
}
