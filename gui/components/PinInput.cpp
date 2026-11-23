#include "PinInput.h"
#include "../../utils/Theme.h"

#include <QEvent>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QTimer>
#include <QVBoxLayout>

PinInput::PinInput(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    blinkTimer = new QTimer(this);
    blinkTimer->setInterval(500);

    connect(blinkTimer, &QTimer::timeout, this, [this]() {
        blinkVisible = !blinkVisible;
        refreshPinBoxes();
    });

    input->installEventFilter(this);

    connect(input, &QLineEdit::textChanged, this, &PinInput::updatePinBoxes);

    connect(input, &QLineEdit::returnPressed, this, [this]() {
        emit submitKeyPressed(input->text());
    });
}

void PinInput::setupUI()
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *boxesLayout = new QHBoxLayout();

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    boxesLayout->setSpacing(SCAPMS::Theme::GAP_M);
    boxesLayout->setAlignment(Qt::AlignCenter);

    //--actual keyboard input.
    input = new QLineEdit(this);

    input->setMaxLength(4);

    input->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,4}"), input));

    //--hide the actual input.
    input->setFixedSize(1, 1);

    input->setStyleSheet("QLineEdit {"
                         "background: transparent;"
                         "color: transparent;"
                         "border: none;"
                         "}");

    //--populate 4 visual PIN boxes.
    //--populate 4 visual PIN boxes.
    for (int i = 0; i < 4; ++i) {
        pinBoxes[i] = new QLabel(this);

        pinBoxes[i]->setFixedSize(55, 55);
        pinBoxes[i]->setAlignment(Qt::AlignCenter);

        // Allow clicks on the boxes to reach the parent widget.
        pinBoxes[i]->setAttribute(Qt::WA_TransparentForMouseEvents);

        boxesLayout->addWidget(pinBoxes[i]);
    }

    refreshPinBoxes();

    mainLayout->addLayout(boxesLayout);
    mainLayout->addWidget(input);

    mainLayout->setAlignment(Qt::AlignCenter);

    setFixedSize(4 * 55 + 3 * SCAPMS::Theme::GAP_M, 55);

    setFocusPolicy(Qt::StrongFocus);
}

void PinInput::refreshPinBoxes()
{
    const QString value = input->text();

    int activeIndex = value.length();

    for (int i = 0; i < 4; ++i) {
        bool hasValue = i < value.length();

        pinBoxes[i]->setText(hasValue ? QString(value[i]) : "");

        QString borderColor = SCAPMS::Theme::COLOR_BG_GRAY100;
        int borderWidth = 1;

        // Boxes containing entered digits.
        if (hasValue) {
            borderColor = SCAPMS::Theme::COLOR_BG_PRIMARY;
            borderWidth = 3;
        }

        // Currently active box.
        else if (inputFocused && i == activeIndex && activeIndex < 4) {
            borderWidth = 3;

            borderColor = blinkVisible ? SCAPMS::Theme::COLOR_BG_PRIMARY
                                       : SCAPMS::Theme::COLOR_BG_GRAY100;
        }

        pinBoxes[i]->setStyleSheet(QString("QLabel {"
                                           "background-color: %1;"
                                           "border: %2px solid %3;"
                                           "border-radius: %4px;"
                                           "color: %5;"
                                           "font-size: %6px;"
                                           "font-weight: 600;"
                                           "}")
                                       .arg(SCAPMS::Theme::COLOR_BG_GRAY50)
                                       .arg(borderWidth)
                                       .arg(borderColor)
                                       .arg(SCAPMS::Theme::RADIUS_M)
                                       .arg(SCAPMS::Theme::COLOR_TEXT_PRIMARY)
                                       .arg(SCAPMS::Theme::FONT_B));
    }
}

bool PinInput::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == input) {
        if (event->type() == QEvent::FocusIn) {
            inputFocused = true;
            blinkVisible = true;

            if (!isComplete()) {
                blinkTimer->start();
            }

            refreshPinBoxes();
        }

        else if (event->type() == QEvent::FocusOut) {
            inputFocused = false;
            blinkTimer->stop();

            refreshPinBoxes();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void PinInput::mousePressEvent(QMouseEvent *event)
{
    input->setFocus();
    input->setCursorPosition(input->text().length());

    refreshPinBoxes();

    QWidget::mousePressEvent(event);
}

void PinInput::updatePinBoxes()
{
    refreshPinBoxes();

    if (isComplete()) {
        blinkTimer->stop();
        emit passcodeCompleted(input->text());
    }
}

QString PinInput::passcode() const
{
    return input->text();
}

bool PinInput::isComplete() const
{
    return input->text().length() == 4;
}

void PinInput::clear()
{
    input->clear();
    input->setFocus();
    input->setCursorPosition(0);

    blinkVisible = true;

    if (!isComplete()) {
        blinkTimer->start();
    }

    refreshPinBoxes();
}