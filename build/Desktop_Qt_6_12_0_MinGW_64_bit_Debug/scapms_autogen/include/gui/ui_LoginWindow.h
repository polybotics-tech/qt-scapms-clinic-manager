/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *mainContainer;
    QHBoxLayout *horizontalLayout;
    QWidget *leftPanel;
    QVBoxLayout *verticalLayout;
    QWidget *imageContainer;
    QWidget *brandingContainer;
    QVBoxLayout *verticalLayout_2;
    QWidget *brandingHeader;
    QHBoxLayout *horizontalLayout_3;
    QWidget *logoContainer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *logoLabel;
    QWidget *brandingTextContainer;
    QVBoxLayout *verticalLayout_4;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QWidget *welcomeMsgContainer;
    QVBoxLayout *verticalLayout_3;
    QLabel *fullnameLabel;
    QLabel *welcomeTextLabel;
    QWidget *rightPanel;
    QVBoxLayout *verticalLayout_5;
    QWidget *loginHeaderContainer;
    QVBoxLayout *verticalLayout_6;
    QLabel *loginTitleLabel;
    QLabel *loginInstructionLabel;
    QWidget *loginFormContainer;
    QVBoxLayout *verticalLayout_7;
    QWidget *roleSection;
    QVBoxLayout *verticalLayout_8;
    QLabel *roleLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *staffRadioButton;
    QRadioButton *adminRadioButton;
    QWidget *pinSection;
    QVBoxLayout *verticalLayout_9;
    QLabel *pinLabel;
    QWidget *pinBoxesContainer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *errorLabel;
    QWidget *loginButtonSection;
    QVBoxLayout *verticalLayout_10;
    QPushButton *loginButton;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(920, 560);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        LoginWindow->setMinimumSize(QSize(920, 560));
        LoginWindow->setMaximumSize(QSize(920, 560));
        horizontalLayout_2 = new QHBoxLayout(LoginWindow);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(24, 24, 24, 24);
        mainContainer = new QWidget(LoginWindow);
        mainContainer->setObjectName("mainContainer");
        horizontalLayout = new QHBoxLayout(mainContainer);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftPanel = new QWidget(mainContainer);
        leftPanel->setObjectName("leftPanel");
        verticalLayout = new QVBoxLayout(leftPanel);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        imageContainer = new QWidget(leftPanel);
        imageContainer->setObjectName("imageContainer");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imageContainer->sizePolicy().hasHeightForWidth());
        imageContainer->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(imageContainer);

        brandingContainer = new QWidget(leftPanel);
        brandingContainer->setObjectName("brandingContainer");
        sizePolicy1.setHeightForWidth(brandingContainer->sizePolicy().hasHeightForWidth());
        brandingContainer->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(brandingContainer);
        verticalLayout_2->setSpacing(32);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(24, 24, 24, 24);
        brandingHeader = new QWidget(brandingContainer);
        brandingHeader->setObjectName("brandingHeader");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(brandingHeader->sizePolicy().hasHeightForWidth());
        brandingHeader->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(brandingHeader);
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        logoContainer = new QWidget(brandingHeader);
        logoContainer->setObjectName("logoContainer");
        logoContainer->setMinimumSize(QSize(64, 64));
        logoContainer->setMaximumSize(QSize(64, 64));
        horizontalLayout_4 = new QHBoxLayout(logoContainer);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        logoLabel = new QLabel(logoContainer);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(64, 64));
        logoLabel->setMaximumSize(QSize(64, 64));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(logoLabel);


        horizontalLayout_3->addWidget(logoContainer);

        brandingTextContainer = new QWidget(brandingHeader);
        brandingTextContainer->setObjectName("brandingTextContainer");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(brandingTextContainer->sizePolicy().hasHeightForWidth());
        brandingTextContainer->setSizePolicy(sizePolicy3);
        verticalLayout_4 = new QVBoxLayout(brandingTextContainer);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(brandingTextContainer);
        titleLabel->setObjectName("titleLabel");
        sizePolicy2.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        titleLabel->setFont(font);

        verticalLayout_4->addWidget(titleLabel);

        subtitleLabel = new QLabel(brandingTextContainer);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font1;
        font1.setPointSize(11);
        subtitleLabel->setFont(font1);

        verticalLayout_4->addWidget(subtitleLabel);


        horizontalLayout_3->addWidget(brandingTextContainer);


        verticalLayout_2->addWidget(brandingHeader);

        welcomeMsgContainer = new QWidget(brandingContainer);
        welcomeMsgContainer->setObjectName("welcomeMsgContainer");
        sizePolicy2.setHeightForWidth(welcomeMsgContainer->sizePolicy().hasHeightForWidth());
        welcomeMsgContainer->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(welcomeMsgContainer);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        fullnameLabel = new QLabel(welcomeMsgContainer);
        fullnameLabel->setObjectName("fullnameLabel");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(fullnameLabel->sizePolicy().hasHeightForWidth());
        fullnameLabel->setSizePolicy(sizePolicy4);
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        fullnameLabel->setFont(font2);
        fullnameLabel->setWordWrap(true);

        verticalLayout_3->addWidget(fullnameLabel);

        welcomeTextLabel = new QLabel(welcomeMsgContainer);
        welcomeTextLabel->setObjectName("welcomeTextLabel");
        welcomeTextLabel->setFont(font1);
        welcomeTextLabel->setWordWrap(true);

        verticalLayout_3->addWidget(welcomeTextLabel);


        verticalLayout_2->addWidget(welcomeMsgContainer);


        verticalLayout->addWidget(brandingContainer);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        horizontalLayout->addWidget(leftPanel);

        rightPanel = new QWidget(mainContainer);
        rightPanel->setObjectName("rightPanel");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(rightPanel->sizePolicy().hasHeightForWidth());
        rightPanel->setSizePolicy(sizePolicy5);
        rightPanel->setMinimumSize(QSize(480, 0));
        rightPanel->setMaximumSize(QSize(480, 16777215));
        verticalLayout_5 = new QVBoxLayout(rightPanel);
        verticalLayout_5->setSpacing(48);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(24, 0, 24, 0);
        loginHeaderContainer = new QWidget(rightPanel);
        loginHeaderContainer->setObjectName("loginHeaderContainer");
        sizePolicy2.setHeightForWidth(loginHeaderContainer->sizePolicy().hasHeightForWidth());
        loginHeaderContainer->setSizePolicy(sizePolicy2);
        verticalLayout_6 = new QVBoxLayout(loginHeaderContainer);
        verticalLayout_6->setSpacing(4);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        loginTitleLabel = new QLabel(loginHeaderContainer);
        loginTitleLabel->setObjectName("loginTitleLabel");
        loginTitleLabel->setFont(font);
        loginTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(loginTitleLabel);

        loginInstructionLabel = new QLabel(loginHeaderContainer);
        loginInstructionLabel->setObjectName("loginInstructionLabel");
        sizePolicy4.setHeightForWidth(loginInstructionLabel->sizePolicy().hasHeightForWidth());
        loginInstructionLabel->setSizePolicy(sizePolicy4);
        loginInstructionLabel->setFont(font1);
        loginInstructionLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginInstructionLabel->setWordWrap(true);

        verticalLayout_6->addWidget(loginInstructionLabel);


        verticalLayout_5->addWidget(loginHeaderContainer);

        loginFormContainer = new QWidget(rightPanel);
        loginFormContainer->setObjectName("loginFormContainer");
        sizePolicy2.setHeightForWidth(loginFormContainer->sizePolicy().hasHeightForWidth());
        loginFormContainer->setSizePolicy(sizePolicy2);
        verticalLayout_7 = new QVBoxLayout(loginFormContainer);
        verticalLayout_7->setSpacing(24);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        roleSection = new QWidget(loginFormContainer);
        roleSection->setObjectName("roleSection");
        sizePolicy2.setHeightForWidth(roleSection->sizePolicy().hasHeightForWidth());
        roleSection->setSizePolicy(sizePolicy2);
        verticalLayout_8 = new QVBoxLayout(roleSection);
        verticalLayout_8->setSpacing(8);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        roleLabel = new QLabel(roleSection);
        roleLabel->setObjectName("roleLabel");
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        roleLabel->setFont(font3);
        roleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(roleLabel);

        widget = new QWidget(roleSection);
        widget->setObjectName("widget");
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        staffRadioButton = new QRadioButton(widget);
        staffRadioButton->setObjectName("staffRadioButton");
        staffRadioButton->setFont(font1);
        staffRadioButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        staffRadioButton->setChecked(true);

        horizontalLayout_6->addWidget(staffRadioButton);

        adminRadioButton = new QRadioButton(widget);
        adminRadioButton->setObjectName("adminRadioButton");
        adminRadioButton->setFont(font1);
        adminRadioButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_6->addWidget(adminRadioButton);


        verticalLayout_8->addWidget(widget);


        verticalLayout_7->addWidget(roleSection);

        pinSection = new QWidget(loginFormContainer);
        pinSection->setObjectName("pinSection");
        sizePolicy2.setHeightForWidth(pinSection->sizePolicy().hasHeightForWidth());
        pinSection->setSizePolicy(sizePolicy2);
        verticalLayout_9 = new QVBoxLayout(pinSection);
        verticalLayout_9->setSpacing(8);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        pinLabel = new QLabel(pinSection);
        pinLabel->setObjectName("pinLabel");
        pinLabel->setFont(font3);
        pinLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(pinLabel);

        pinBoxesContainer = new QWidget(pinSection);
        pinBoxesContainer->setObjectName("pinBoxesContainer");
        horizontalLayout_5 = new QHBoxLayout(pinBoxesContainer);
        horizontalLayout_5->setSpacing(16);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);

        verticalLayout_9->addWidget(pinBoxesContainer);

        errorLabel = new QLabel(pinSection);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setFont(font1);
        errorLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        errorLabel->setWordWrap(true);

        verticalLayout_9->addWidget(errorLabel);


        verticalLayout_7->addWidget(pinSection);

        loginButtonSection = new QWidget(loginFormContainer);
        loginButtonSection->setObjectName("loginButtonSection");
        sizePolicy2.setHeightForWidth(loginButtonSection->sizePolicy().hasHeightForWidth());
        loginButtonSection->setSizePolicy(sizePolicy2);
        verticalLayout_10 = new QVBoxLayout(loginButtonSection);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 48, 0, 0);
        loginButton = new QPushButton(loginButtonSection);
        loginButton->setObjectName("loginButton");
        sizePolicy3.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy3);
        loginButton->setMinimumSize(QSize(0, 48));
        loginButton->setFont(font2);
        loginButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_10->addWidget(loginButton);


        verticalLayout_7->addWidget(loginButtonSection);


        verticalLayout_5->addWidget(loginFormContainer);


        horizontalLayout->addWidget(rightPanel);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        horizontalLayout_2->addWidget(mainContainer);


        retranslateUi(LoginWindow);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Miva SCAPMS | Login", nullptr));
        logoLabel->setText(QString());
        titleLabel->setText(QCoreApplication::translate("LoginWindow", "Miva SCAPMS", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("LoginWindow", "Smart Clinic Management System", nullptr));
        fullnameLabel->setText(QCoreApplication::translate("LoginWindow", "Smart Clinic Appointment & Patient Management System", nullptr));
        welcomeTextLabel->setText(QCoreApplication::translate("LoginWindow", "Your trusted companion for smarter, more efficient clinic management.", nullptr));
        loginTitleLabel->setText(QCoreApplication::translate("LoginWindow", "Welcome Back", nullptr));
        loginInstructionLabel->setText(QCoreApplication::translate("LoginWindow", "Provide your role and passcode to continue", nullptr));
        roleLabel->setText(QCoreApplication::translate("LoginWindow", "Select your role", nullptr));
        staffRadioButton->setText(QCoreApplication::translate("LoginWindow", "Staff", nullptr));
        adminRadioButton->setText(QCoreApplication::translate("LoginWindow", "Admin", nullptr));
        pinLabel->setText(QCoreApplication::translate("LoginWindow", "Enter your 4-digit passcode", nullptr));
        errorLabel->setText(QString());
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Sign In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
