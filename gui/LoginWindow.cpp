#include "LoginWindow.h"
#include "gui/ui_LoginWindow.h"

#include "../utils/Theme.h"
#include "components/PinInput.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QRadioButton>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LoginWindow),
    pinInput(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Miva SCAPMS | Login");

    //--login window styling
    setStyleSheet(QString(R"(
            QWidget#LoginWindow {
                background-color: %2;
            }

            QWidget#mainContainer {
                background-color: %1;
                border-radius: %15px;
            }

            QWidget#imageContainer {
                background-color: %2;
            }

            QWidget#brandingContainer {
                background-color: %3;
                border-bottom-left-radius: %15px;
            }

            QLabel#titleLabel {
                color: %4;
                font-size: %11px;
                font-weight: bold;
            }

            QLabel#subtitleLabel {
                color: %5;
                font-size: %13px;
            }

            QLabel#fullNameLabel {
                color: %4;
                font-size: %11px;
                font-weight: 500;
            }

            QLabel#welcomeTextLabel {
                color: %5;
                font-size: %13px;
            }

            QLabel#loginTitleLabel {
                color: %6;
                font-size: %10px;
                font-weight: bold;
            }

            QLabel#loginInstructionLabel {
                color: %7;
                font-size: %13px;
            }

            QLabel#roleLabel,
            QLabel#pinLabel {
                color: %8;
                font-size: %13px;
                font-weight: semibold;
            }

            QLabel#errorLabel {
                color: %18;
                font-size: %14px;
            }
            
            QRadioButton {
                color: %8;
                spacing: %17px;
                font-size: %12px;
                font-weight: 600;
                text-transform: uppercase;
            }
            
            QRadioButton::indicator {
                width: 18px;
                height: 18px;
                border: 2px solid %9;
                border-radius: %16px;
                background-color: %1;
            }
            
            QRadioButton::indicator:checked {
                border: 2px solid %3;
                background-color: %19;
            }
            
            QPushButton#loginButton {
                background-color: %3;
                color: %4;
                border: 0px;
                border-radius: %15px;
                font-size: %13px;
                font-weight: medium;
            }

            QPushButton#loginButton:hover {
                opacity: 0.8;
            }
        )")
                      .arg(SCAPMS::Theme::COLOR_BG_WHITE)
                      .arg(SCAPMS::Theme::COLOR_BG_GRAY50)
                      .arg(SCAPMS::Theme::COLOR_BG_PRIMARY)
                      .arg(SCAPMS::Theme::COLOR_TEXT_WHITE)
                      .arg(SCAPMS::Theme::COLOR_TEXT_GRAY50)
                      .arg(SCAPMS::Theme::COLOR_TEXT_BLACK)
                      .arg(SCAPMS::Theme::COLOR_TEXT_GRAY100)
                      .arg(SCAPMS::Theme::COLOR_TEXT_GRAY200)
                      .arg(SCAPMS::Theme::COLOR_BG_GRAY100)
                      .arg(SCAPMS::Theme::FONT_XB)
                      .arg(SCAPMS::Theme::FONT_B)
                      .arg(SCAPMS::Theme::FONT_M)
                      .arg(SCAPMS::Theme::FONT_S)
                      .arg(SCAPMS::Theme::FONT_XS)
                      .arg(SCAPMS::Theme::RADIUS_B)
                      .arg(SCAPMS::Theme::RADIUS_XS + 1)
                      .arg(SCAPMS::Theme::GAP_S)
                      .arg(SCAPMS::Theme::COLOR_ERROR)
                      .arg(SCAPMS::Theme::COLOR_SUCCESS_FADED));

    //--group role selection buttons.
    auto *roleGroup = new QButtonGroup(this);

    roleGroup->setExclusive(true);

    roleGroup->addButton(ui->staffRadioButton);
    roleGroup->addButton(ui->adminRadioButton);

    //--staff is selected by default.
    ui->staffRadioButton->setChecked(true);

    //--create the PIN input component.
    pinInput = new PinInput(this);

    //--insert PIN component into the existing container layout.
    QLayout *pinLayout = ui->pinBoxesContainer->layout();

    if (pinLayout) {
        pinLayout->addWidget(pinInput);
    } else {
        auto *layout = new QHBoxLayout(ui->pinBoxesContainer);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(pinInput);
    }

    //--connect the login button.
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);

    //--connect enterKey pressed listener
    connect(pinInput, &PinInput::submitKeyPressed, this, &LoginWindow::handleLogin);

    //--clear any error message on pin entered
    connect(pinInput, &PinInput::passcodeCompleted, this, [this](const QString &) {
        ui->errorLabel->clear();
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::handleLogin()
{
    QString role;

    if (ui->adminRadioButton->isChecked()) {
        role = "Admin";
    } else {
        role = "Staff";
    }

    //--require exactly four digits.
    if (!pinInput->isComplete()) {
        ui->errorLabel->setText("Please enter your 4-digit passcode.");
        ui->errorLabel->show();
        return;
    }

    //--demo credentials.
    const QString expectedPasscode = (role == "Admin") ? "5678" : "1234";

    if (pinInput->passcode() == expectedPasscode) {
        ui->errorLabel->clear();

        emit loginSuccessful(role);
    } else {
        ui->errorLabel->setText("Incorrect passcode. Please try again.");

        ui->errorLabel->show();

        pinInput->clear();
    }
}