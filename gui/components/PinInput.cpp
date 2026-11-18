#include "PinInput.h"
#include "../../utils/Theme.h"

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>

PinInput::PinInput(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

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
    for (int i = 0; i < 4; ++i) {
        pinBoxes[i] = new QLabel(this);

        pinBoxes[i]->setFixedSize(55, 55);
        pinBoxes[i]->setAlignment(Qt::AlignCenter);

        pinBoxes[i]->setStyleSheet(QString("QLabel {"
                                           "background-color: %1;"
                                           "border: 1px solid %2;"
                                           "border-radius: %3px;"
                                           "color: %4;"
                                           "font-size: %5px;"
                                           "font-weight: 600;"
                                           "}")
                                       .arg(SCAPMS::Theme::COLOR_BG_GRAY50)
                                       .arg(SCAPMS::Theme::COLOR_BG_GRAY100)
                                       .arg(SCAPMS::Theme::RADIUS_M)
                                       .arg(SCAPMS::Theme::COLOR_TEXT_PRIMARY)
                                       .arg(SCAPMS::Theme::FONT_B));

        boxesLayout->addWidget(pinBoxes[i]);
    }

    mainLayout->addLayout(boxesLayout);
    mainLayout->addWidget(input);

    mainLayout->setAlignment(Qt::AlignCenter);

    setFixedSize(4 * 55 + 3 * SCAPMS::Theme::GAP_M, 55);

    setFocusPolicy(Qt::StrongFocus);
}

void PinInput::mousePressEvent(QMouseEvent *event)
{
    input->setFocus();
    input->setCursorPosition(input->text().length());

    QWidget::mousePressEvent(event);
}

void PinInput::updatePinBoxes()
{
    const QString value = input->text();

    for (int i = 0; i < 4; ++i) {
        pinBoxes[i]->setText(i < value.length() ? QString(value[i]) : "");

        pinBoxes[i]->setStyleSheet(QString("QLabel {"
                                           "background-color: %1;"
                                           "border: 1px solid %2;"
                                           "border-radius: %3px;"
                                           "color: %4;"
                                           "font-size: %5px;"
                                           "font-weight: 600;"
                                           "}")
                                       .arg(SCAPMS::Theme::COLOR_BG_GRAY50)
                                       .arg(SCAPMS::Theme::COLOR_BG_GRAY100)
                                       .arg(SCAPMS::Theme::RADIUS_M)
                                       .arg(SCAPMS::Theme::COLOR_TEXT_PRIMARY)
                                       .arg(SCAPMS::Theme::FONT_B));
    }

    if (isComplete()) {
        emit passcodeCompleted(value);
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
}