/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *mainTabWidget;
    QWidget *dashboardTab;
    QVBoxLayout *verticalLayout_2;
    QWidget *overviewTopContainer;
    QHBoxLayout *horizontalLayout_8;
    QWidget *overviewTitleContainer;
    QVBoxLayout *verticalLayout_3;
    QLabel *overviewTitleLabel;
    QLabel *overviewSubtitleLabel;
    QWidget *statisticsContainer;
    QHBoxLayout *horizontalLayout_7;
    QWidget *totalPatientsCard;
    QVBoxLayout *verticalLayout_5;
    QLabel *totalPatientsTitleLabel;
    QWidget *totalPatientsInnerContainer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *totalPatientsValue;
    QWidget *todayAppointmentsCard;
    QVBoxLayout *verticalLayout_4;
    QLabel *todayAppointmentsTitleLabel;
    QWidget *todayAppointmentsInnerContainer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *todayAppointmentsValue;
    QWidget *waitingPatientsCard;
    QVBoxLayout *verticalLayout_7;
    QLabel *waitingPatientsTitleLabel;
    QWidget *waitingPatientsInnerContainer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *waitingPatientsValue;
    QWidget *emergencyPatientsCard;
    QVBoxLayout *verticalLayout_6;
    QLabel *emergencyPatientsTitleLabel;
    QWidget *emergencyPatientsInnerContainer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *emergencyPatientsValue;
    QWidget *overviewTablesContainer;
    QGridLayout *gridLayout;
    QWidget *waitingQueueContainer;
    QVBoxLayout *verticalLayout_8;
    QWidget *waitingQueueContainerTop;
    QHBoxLayout *horizontalLayout_9;
    QLabel *waitingQueueContainerTitleLabel;
    QPushButton *nextPatientButton;
    QTableWidget *waitingQueueTable;
    QWidget *upcomingAppointmentsContainer;
    QVBoxLayout *verticalLayout_9;
    QWidget *upcomingAppointmentsContainerTop;
    QHBoxLayout *horizontalLayout_10;
    QLabel *upcomingAppointmentsContainerTitleLabel;
    QPushButton *viewAllAppointmentsButton;
    QTableWidget *upcomingAppointmentsTable;
    QWidget *patientsTab;
    QVBoxLayout *verticalLayout_14;
    QWidget *patientsTabTopContainer;
    QHBoxLayout *horizontalLayout_11;
    QWidget *patientsTabTitleContainer;
    QVBoxLayout *verticalLayout_10;
    QLabel *patientsTabTitleLabel;
    QLabel *patientsTabSubtitleLabel;
    QWidget *patientsTabSearchSortContainer;
    QVBoxLayout *verticalLayout_12;
    QWidget *patientsSearchContainer;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *patientsSearchInput;
    QWidget *patientsSortContainer;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_21;
    QLabel *patientsSearchMethodLabel;
    QComboBox *patientsSearchMethodCombo;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_22;
    QLabel *patientsSortMethodLabel;
    QComboBox *patientsSortMethodCombo;
    QWidget *patientsTablesContainer;
    QGridLayout *gridLayout_2;
    QWidget *patientsListContainer;
    QVBoxLayout *verticalLayout_11;
    QWidget *patientsListContainerTop;
    QHBoxLayout *horizontalLayout_14;
    QLabel *patientsListContainerTitleLabel;
    QWidget *patientsActionsContainer;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *createPatientAppointmentButton;
    QPushButton *addToQueueButton;
    QTableWidget *patientsTable;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_20;
    QWidget *patientsFormContainer;
    QVBoxLayout *verticalLayout_13;
    QWidget *patientsFormContainerTop;
    QHBoxLayout *horizontalLayout_15;
    QLabel *patientsFormContainerTitleLabel;
    QPushButton *clearPatientFormButton;
    QWidget *patientFormCard;
    QVBoxLayout *verticalLayout_19;
    QWidget *patientFormField;
    QVBoxLayout *verticalLayout_15;
    QLabel *patientFormLabel;
    QLineEdit *patientNameInput;
    QWidget *patientFormField_2;
    QVBoxLayout *verticalLayout_16;
    QLabel *patientFormLabel_2;
    QSpinBox *patientAgeInput;
    QWidget *patientFormField_3;
    QVBoxLayout *verticalLayout_17;
    QLabel *patientFormLabel_3;
    QLineEdit *patientContactInput;
    QWidget *patientFormField_4;
    QVBoxLayout *verticalLayout_18;
    QLabel *patientFormLabel_4;
    QComboBox *patientCategoryCombo;
    QPushButton *registerPatientButton;
    QWidget *appointmentsTab;
    QVBoxLayout *verticalLayout_35;
    QWidget *appointmentsTabTopContainer;
    QHBoxLayout *horizontalLayout_13;
    QWidget *appointmentsTabTitleContainer;
    QVBoxLayout *verticalLayout_23;
    QLabel *appointmentsTabTitleLabel;
    QLabel *appointmentsTabSubtitleLabel;
    QWidget *appointmentsTablesContainer;
    QGridLayout *gridLayout_5;
    QWidget *appointmentsListContainer;
    QVBoxLayout *verticalLayout_27;
    QWidget *appointmentsListContainerTop;
    QHBoxLayout *horizontalLayout_18;
    QLabel *appointmentsListContainerTitleLabel;
    QWidget *appointmentsActionsContainer;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *cancelAppointmentButton;
    QTableWidget *appointmentsTable;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_28;
    QWidget *appointmentsFormContainer;
    QVBoxLayout *verticalLayout_29;
    QWidget *appointmentsFormContainerTop;
    QHBoxLayout *horizontalLayout_20;
    QLabel *appointmentsFormContainerTitleLabel;
    QPushButton *clearAppointmentFormButton;
    QWidget *appointmentFormCard;
    QVBoxLayout *verticalLayout_30;
    QWidget *appointmentFormField_1;
    QVBoxLayout *verticalLayout_31;
    QLabel *appointmentFormLabel;
    QLineEdit *appointmentPatientInput;
    QLabel *appointmentFormFieldInfoLabel;
    QWidget *appointmentFormField_2;
    QVBoxLayout *verticalLayout_32;
    QLabel *appointmentFormLabel_2;
    QLineEdit *appointmentReasonInput;
    QWidget *appointmentFormField_3;
    QVBoxLayout *verticalLayout_33;
    QLabel *appointmentFormLabel_3;
    QDateEdit *appointmentDateInput;
    QWidget *appointmentFormField_4;
    QVBoxLayout *verticalLayout_34;
    QLabel *appointmentFormLabel_4;
    QTimeEdit *appointmentTimeInput;
    QPushButton *scheduleAppointmentButton;
    QWidget *reportsTab;
    QWidget *adminTab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1280, 720));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(1280, 720));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        mainTabWidget = new QTabWidget(centralwidget);
        mainTabWidget->setObjectName("mainTabWidget");
        sizePolicy.setHeightForWidth(mainTabWidget->sizePolicy().hasHeightForWidth());
        mainTabWidget->setSizePolicy(sizePolicy);
        mainTabWidget->setMaximumSize(QSize(16777215, 16777215));
        mainTabWidget->setMovable(true);
        dashboardTab = new QWidget();
        dashboardTab->setObjectName("dashboardTab");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dashboardTab->sizePolicy().hasHeightForWidth());
        dashboardTab->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(dashboardTab);
        verticalLayout_2->setSpacing(24);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        overviewTopContainer = new QWidget(dashboardTab);
        overviewTopContainer->setObjectName("overviewTopContainer");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(overviewTopContainer->sizePolicy().hasHeightForWidth());
        overviewTopContainer->setSizePolicy(sizePolicy2);
        horizontalLayout_8 = new QHBoxLayout(overviewTopContainer);
        horizontalLayout_8->setSpacing(64);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        overviewTitleContainer = new QWidget(overviewTopContainer);
        overviewTitleContainer->setObjectName("overviewTitleContainer");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(overviewTitleContainer->sizePolicy().hasHeightForWidth());
        overviewTitleContainer->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(overviewTitleContainer);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        overviewTitleLabel = new QLabel(overviewTitleContainer);
        overviewTitleLabel->setObjectName("overviewTitleLabel");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(overviewTitleLabel->sizePolicy().hasHeightForWidth());
        overviewTitleLabel->setSizePolicy(sizePolicy4);
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        overviewTitleLabel->setFont(font);
        overviewTitleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_3->addWidget(overviewTitleLabel);

        overviewSubtitleLabel = new QLabel(overviewTitleContainer);
        overviewSubtitleLabel->setObjectName("overviewSubtitleLabel");
        sizePolicy2.setHeightForWidth(overviewSubtitleLabel->sizePolicy().hasHeightForWidth());
        overviewSubtitleLabel->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(11);
        overviewSubtitleLabel->setFont(font1);
        overviewSubtitleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        overviewSubtitleLabel->setWordWrap(true);

        verticalLayout_3->addWidget(overviewSubtitleLabel);


        horizontalLayout_8->addWidget(overviewTitleContainer);

        statisticsContainer = new QWidget(overviewTopContainer);
        statisticsContainer->setObjectName("statisticsContainer");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(statisticsContainer->sizePolicy().hasHeightForWidth());
        statisticsContainer->setSizePolicy(sizePolicy5);
        horizontalLayout_7 = new QHBoxLayout(statisticsContainer);
        horizontalLayout_7->setSpacing(16);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        totalPatientsCard = new QWidget(statisticsContainer);
        totalPatientsCard->setObjectName("totalPatientsCard");
        sizePolicy4.setHeightForWidth(totalPatientsCard->sizePolicy().hasHeightForWidth());
        totalPatientsCard->setSizePolicy(sizePolicy4);
        totalPatientsCard->setMinimumSize(QSize(180, 0));
        totalPatientsCard->setMaximumSize(QSize(180, 16777215));
        verticalLayout_5 = new QVBoxLayout(totalPatientsCard);
        verticalLayout_5->setSpacing(8);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(16, 16, 16, 16);
        totalPatientsTitleLabel = new QLabel(totalPatientsCard);
        totalPatientsTitleLabel->setObjectName("totalPatientsTitleLabel");
        sizePolicy2.setHeightForWidth(totalPatientsTitleLabel->sizePolicy().hasHeightForWidth());
        totalPatientsTitleLabel->setSizePolicy(sizePolicy2);
        totalPatientsTitleLabel->setFont(font1);

        verticalLayout_5->addWidget(totalPatientsTitleLabel);

        totalPatientsInnerContainer = new QWidget(totalPatientsCard);
        totalPatientsInnerContainer->setObjectName("totalPatientsInnerContainer");
        sizePolicy2.setHeightForWidth(totalPatientsInnerContainer->sizePolicy().hasHeightForWidth());
        totalPatientsInnerContainer->setSizePolicy(sizePolicy2);
        horizontalLayout_4 = new QHBoxLayout(totalPatientsInnerContainer);
        horizontalLayout_4->setSpacing(16);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        totalPatientsValue = new QLabel(totalPatientsInnerContainer);
        totalPatientsValue->setObjectName("totalPatientsValue");
        sizePolicy2.setHeightForWidth(totalPatientsValue->sizePolicy().hasHeightForWidth());
        totalPatientsValue->setSizePolicy(sizePolicy2);
        totalPatientsValue->setFont(font);

        horizontalLayout_4->addWidget(totalPatientsValue);


        verticalLayout_5->addWidget(totalPatientsInnerContainer);


        horizontalLayout_7->addWidget(totalPatientsCard);

        todayAppointmentsCard = new QWidget(statisticsContainer);
        todayAppointmentsCard->setObjectName("todayAppointmentsCard");
        sizePolicy4.setHeightForWidth(todayAppointmentsCard->sizePolicy().hasHeightForWidth());
        todayAppointmentsCard->setSizePolicy(sizePolicy4);
        todayAppointmentsCard->setMinimumSize(QSize(180, 0));
        todayAppointmentsCard->setMaximumSize(QSize(180, 16777215));
        verticalLayout_4 = new QVBoxLayout(todayAppointmentsCard);
        verticalLayout_4->setSpacing(8);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(16, 16, 16, 16);
        todayAppointmentsTitleLabel = new QLabel(todayAppointmentsCard);
        todayAppointmentsTitleLabel->setObjectName("todayAppointmentsTitleLabel");
        sizePolicy2.setHeightForWidth(todayAppointmentsTitleLabel->sizePolicy().hasHeightForWidth());
        todayAppointmentsTitleLabel->setSizePolicy(sizePolicy2);
        todayAppointmentsTitleLabel->setFont(font1);

        verticalLayout_4->addWidget(todayAppointmentsTitleLabel);

        todayAppointmentsInnerContainer = new QWidget(todayAppointmentsCard);
        todayAppointmentsInnerContainer->setObjectName("todayAppointmentsInnerContainer");
        sizePolicy2.setHeightForWidth(todayAppointmentsInnerContainer->sizePolicy().hasHeightForWidth());
        todayAppointmentsInnerContainer->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(todayAppointmentsInnerContainer);
        horizontalLayout_3->setSpacing(16);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        todayAppointmentsValue = new QLabel(todayAppointmentsInnerContainer);
        todayAppointmentsValue->setObjectName("todayAppointmentsValue");
        sizePolicy2.setHeightForWidth(todayAppointmentsValue->sizePolicy().hasHeightForWidth());
        todayAppointmentsValue->setSizePolicy(sizePolicy2);
        todayAppointmentsValue->setFont(font);

        horizontalLayout_3->addWidget(todayAppointmentsValue);


        verticalLayout_4->addWidget(todayAppointmentsInnerContainer);


        horizontalLayout_7->addWidget(todayAppointmentsCard);

        waitingPatientsCard = new QWidget(statisticsContainer);
        waitingPatientsCard->setObjectName("waitingPatientsCard");
        sizePolicy4.setHeightForWidth(waitingPatientsCard->sizePolicy().hasHeightForWidth());
        waitingPatientsCard->setSizePolicy(sizePolicy4);
        waitingPatientsCard->setMinimumSize(QSize(180, 0));
        waitingPatientsCard->setMaximumSize(QSize(180, 16777215));
        verticalLayout_7 = new QVBoxLayout(waitingPatientsCard);
        verticalLayout_7->setSpacing(8);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(16, 16, 16, 16);
        waitingPatientsTitleLabel = new QLabel(waitingPatientsCard);
        waitingPatientsTitleLabel->setObjectName("waitingPatientsTitleLabel");
        sizePolicy2.setHeightForWidth(waitingPatientsTitleLabel->sizePolicy().hasHeightForWidth());
        waitingPatientsTitleLabel->setSizePolicy(sizePolicy2);
        waitingPatientsTitleLabel->setFont(font1);

        verticalLayout_7->addWidget(waitingPatientsTitleLabel);

        waitingPatientsInnerContainer = new QWidget(waitingPatientsCard);
        waitingPatientsInnerContainer->setObjectName("waitingPatientsInnerContainer");
        sizePolicy2.setHeightForWidth(waitingPatientsInnerContainer->sizePolicy().hasHeightForWidth());
        waitingPatientsInnerContainer->setSizePolicy(sizePolicy2);
        horizontalLayout_6 = new QHBoxLayout(waitingPatientsInnerContainer);
        horizontalLayout_6->setSpacing(16);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        waitingPatientsValue = new QLabel(waitingPatientsInnerContainer);
        waitingPatientsValue->setObjectName("waitingPatientsValue");
        sizePolicy2.setHeightForWidth(waitingPatientsValue->sizePolicy().hasHeightForWidth());
        waitingPatientsValue->setSizePolicy(sizePolicy2);
        waitingPatientsValue->setFont(font);

        horizontalLayout_6->addWidget(waitingPatientsValue);


        verticalLayout_7->addWidget(waitingPatientsInnerContainer);


        horizontalLayout_7->addWidget(waitingPatientsCard);

        emergencyPatientsCard = new QWidget(statisticsContainer);
        emergencyPatientsCard->setObjectName("emergencyPatientsCard");
        sizePolicy4.setHeightForWidth(emergencyPatientsCard->sizePolicy().hasHeightForWidth());
        emergencyPatientsCard->setSizePolicy(sizePolicy4);
        emergencyPatientsCard->setMinimumSize(QSize(180, 0));
        emergencyPatientsCard->setMaximumSize(QSize(180, 16777215));
        verticalLayout_6 = new QVBoxLayout(emergencyPatientsCard);
        verticalLayout_6->setSpacing(8);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(16, 16, 16, 16);
        emergencyPatientsTitleLabel = new QLabel(emergencyPatientsCard);
        emergencyPatientsTitleLabel->setObjectName("emergencyPatientsTitleLabel");
        sizePolicy2.setHeightForWidth(emergencyPatientsTitleLabel->sizePolicy().hasHeightForWidth());
        emergencyPatientsTitleLabel->setSizePolicy(sizePolicy2);
        emergencyPatientsTitleLabel->setFont(font1);

        verticalLayout_6->addWidget(emergencyPatientsTitleLabel);

        emergencyPatientsInnerContainer = new QWidget(emergencyPatientsCard);
        emergencyPatientsInnerContainer->setObjectName("emergencyPatientsInnerContainer");
        sizePolicy2.setHeightForWidth(emergencyPatientsInnerContainer->sizePolicy().hasHeightForWidth());
        emergencyPatientsInnerContainer->setSizePolicy(sizePolicy2);
        horizontalLayout_5 = new QHBoxLayout(emergencyPatientsInnerContainer);
        horizontalLayout_5->setSpacing(16);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        emergencyPatientsValue = new QLabel(emergencyPatientsInnerContainer);
        emergencyPatientsValue->setObjectName("emergencyPatientsValue");
        sizePolicy2.setHeightForWidth(emergencyPatientsValue->sizePolicy().hasHeightForWidth());
        emergencyPatientsValue->setSizePolicy(sizePolicy2);
        emergencyPatientsValue->setFont(font);

        horizontalLayout_5->addWidget(emergencyPatientsValue);


        verticalLayout_6->addWidget(emergencyPatientsInnerContainer);


        horizontalLayout_7->addWidget(emergencyPatientsCard);

        waitingPatientsCard->raise();
        todayAppointmentsCard->raise();
        totalPatientsCard->raise();
        emergencyPatientsCard->raise();

        horizontalLayout_8->addWidget(statisticsContainer);


        verticalLayout_2->addWidget(overviewTopContainer);

        overviewTablesContainer = new QWidget(dashboardTab);
        overviewTablesContainer->setObjectName("overviewTablesContainer");
        gridLayout = new QGridLayout(overviewTablesContainer);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(24);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        waitingQueueContainer = new QWidget(overviewTablesContainer);
        waitingQueueContainer->setObjectName("waitingQueueContainer");
        verticalLayout_8 = new QVBoxLayout(waitingQueueContainer);
        verticalLayout_8->setSpacing(12);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(16, 16, 16, 16);
        waitingQueueContainerTop = new QWidget(waitingQueueContainer);
        waitingQueueContainerTop->setObjectName("waitingQueueContainerTop");
        sizePolicy2.setHeightForWidth(waitingQueueContainerTop->sizePolicy().hasHeightForWidth());
        waitingQueueContainerTop->setSizePolicy(sizePolicy2);
        horizontalLayout_9 = new QHBoxLayout(waitingQueueContainerTop);
        horizontalLayout_9->setSpacing(48);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        waitingQueueContainerTitleLabel = new QLabel(waitingQueueContainerTop);
        waitingQueueContainerTitleLabel->setObjectName("waitingQueueContainerTitleLabel");
        sizePolicy2.setHeightForWidth(waitingQueueContainerTitleLabel->sizePolicy().hasHeightForWidth());
        waitingQueueContainerTitleLabel->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        waitingQueueContainerTitleLabel->setFont(font2);

        horizontalLayout_9->addWidget(waitingQueueContainerTitleLabel);

        nextPatientButton = new QPushButton(waitingQueueContainerTop);
        nextPatientButton->setObjectName("nextPatientButton");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(nextPatientButton->sizePolicy().hasHeightForWidth());
        nextPatientButton->setSizePolicy(sizePolicy6);
        nextPatientButton->setMaximumSize(QSize(78, 16777215));
        QFont font3;
        font3.setPointSize(9);
        nextPatientButton->setFont(font3);
        nextPatientButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_9->addWidget(nextPatientButton);


        verticalLayout_8->addWidget(waitingQueueContainerTop);

        waitingQueueTable = new QTableWidget(waitingQueueContainer);
        waitingQueueTable->setObjectName("waitingQueueTable");

        verticalLayout_8->addWidget(waitingQueueTable);


        gridLayout->addWidget(waitingQueueContainer, 0, 0, 1, 1);

        upcomingAppointmentsContainer = new QWidget(overviewTablesContainer);
        upcomingAppointmentsContainer->setObjectName("upcomingAppointmentsContainer");
        verticalLayout_9 = new QVBoxLayout(upcomingAppointmentsContainer);
        verticalLayout_9->setSpacing(12);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(16, 16, 16, 16);
        upcomingAppointmentsContainerTop = new QWidget(upcomingAppointmentsContainer);
        upcomingAppointmentsContainerTop->setObjectName("upcomingAppointmentsContainerTop");
        sizePolicy2.setHeightForWidth(upcomingAppointmentsContainerTop->sizePolicy().hasHeightForWidth());
        upcomingAppointmentsContainerTop->setSizePolicy(sizePolicy2);
        horizontalLayout_10 = new QHBoxLayout(upcomingAppointmentsContainerTop);
        horizontalLayout_10->setSpacing(48);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        upcomingAppointmentsContainerTitleLabel = new QLabel(upcomingAppointmentsContainerTop);
        upcomingAppointmentsContainerTitleLabel->setObjectName("upcomingAppointmentsContainerTitleLabel");
        sizePolicy2.setHeightForWidth(upcomingAppointmentsContainerTitleLabel->sizePolicy().hasHeightForWidth());
        upcomingAppointmentsContainerTitleLabel->setSizePolicy(sizePolicy2);
        upcomingAppointmentsContainerTitleLabel->setFont(font2);

        horizontalLayout_10->addWidget(upcomingAppointmentsContainerTitleLabel);

        viewAllAppointmentsButton = new QPushButton(upcomingAppointmentsContainerTop);
        viewAllAppointmentsButton->setObjectName("viewAllAppointmentsButton");
        sizePolicy6.setHeightForWidth(viewAllAppointmentsButton->sizePolicy().hasHeightForWidth());
        viewAllAppointmentsButton->setSizePolicy(sizePolicy6);
        viewAllAppointmentsButton->setMaximumSize(QSize(54, 16777215));
        QFont font4;
        font4.setPointSize(9);
        font4.setBold(false);
        viewAllAppointmentsButton->setFont(font4);
        viewAllAppointmentsButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_10->addWidget(viewAllAppointmentsButton);


        verticalLayout_9->addWidget(upcomingAppointmentsContainerTop);

        upcomingAppointmentsTable = new QTableWidget(upcomingAppointmentsContainer);
        upcomingAppointmentsTable->setObjectName("upcomingAppointmentsTable");

        verticalLayout_9->addWidget(upcomingAppointmentsTable);


        gridLayout->addWidget(upcomingAppointmentsContainer, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 7);
        gridLayout->setColumnStretch(1, 8);

        verticalLayout_2->addWidget(overviewTablesContainer);

        mainTabWidget->addTab(dashboardTab, QString());
        patientsTab = new QWidget();
        patientsTab->setObjectName("patientsTab");
        verticalLayout_14 = new QVBoxLayout(patientsTab);
        verticalLayout_14->setSpacing(24);
        verticalLayout_14->setObjectName("verticalLayout_14");
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        patientsTabTopContainer = new QWidget(patientsTab);
        patientsTabTopContainer->setObjectName("patientsTabTopContainer");
        horizontalLayout_11 = new QHBoxLayout(patientsTabTopContainer);
        horizontalLayout_11->setSpacing(64);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        patientsTabTitleContainer = new QWidget(patientsTabTopContainer);
        patientsTabTitleContainer->setObjectName("patientsTabTitleContainer");
        sizePolicy3.setHeightForWidth(patientsTabTitleContainer->sizePolicy().hasHeightForWidth());
        patientsTabTitleContainer->setSizePolicy(sizePolicy3);
        verticalLayout_10 = new QVBoxLayout(patientsTabTitleContainer);
        verticalLayout_10->setSpacing(4);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        patientsTabTitleLabel = new QLabel(patientsTabTitleContainer);
        patientsTabTitleLabel->setObjectName("patientsTabTitleLabel");
        sizePolicy4.setHeightForWidth(patientsTabTitleLabel->sizePolicy().hasHeightForWidth());
        patientsTabTitleLabel->setSizePolicy(sizePolicy4);
        patientsTabTitleLabel->setFont(font);
        patientsTabTitleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_10->addWidget(patientsTabTitleLabel);

        patientsTabSubtitleLabel = new QLabel(patientsTabTitleContainer);
        patientsTabSubtitleLabel->setObjectName("patientsTabSubtitleLabel");
        sizePolicy2.setHeightForWidth(patientsTabSubtitleLabel->sizePolicy().hasHeightForWidth());
        patientsTabSubtitleLabel->setSizePolicy(sizePolicy2);
        patientsTabSubtitleLabel->setFont(font1);
        patientsTabSubtitleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        patientsTabSubtitleLabel->setWordWrap(true);

        verticalLayout_10->addWidget(patientsTabSubtitleLabel);


        horizontalLayout_11->addWidget(patientsTabTitleContainer);

        patientsTabSearchSortContainer = new QWidget(patientsTabTopContainer);
        patientsTabSearchSortContainer->setObjectName("patientsTabSearchSortContainer");
        verticalLayout_12 = new QVBoxLayout(patientsTabSearchSortContainer);
        verticalLayout_12->setSpacing(12);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(16, 16, 16, 16);
        patientsSearchContainer = new QWidget(patientsTabSearchSortContainer);
        patientsSearchContainer->setObjectName("patientsSearchContainer");
        horizontalLayout_12 = new QHBoxLayout(patientsSearchContainer);
        horizontalLayout_12->setSpacing(16);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        patientsSearchInput = new QLineEdit(patientsSearchContainer);
        patientsSearchInput->setObjectName("patientsSearchInput");
        patientsSearchInput->setMinimumSize(QSize(540, 0));
        patientsSearchInput->setClearButtonEnabled(true);

        horizontalLayout_12->addWidget(patientsSearchInput);


        verticalLayout_12->addWidget(patientsSearchContainer);

        patientsSortContainer = new QWidget(patientsTabSearchSortContainer);
        patientsSortContainer->setObjectName("patientsSortContainer");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(patientsSortContainer->sizePolicy().hasHeightForWidth());
        patientsSortContainer->setSizePolicy(sizePolicy7);
        patientsSortContainer->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        gridLayout_3 = new QGridLayout(patientsSortContainer);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(patientsSortContainer);
        widget->setObjectName("widget");
        verticalLayout_21 = new QVBoxLayout(widget);
        verticalLayout_21->setSpacing(8);
        verticalLayout_21->setObjectName("verticalLayout_21");
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        patientsSearchMethodLabel = new QLabel(widget);
        patientsSearchMethodLabel->setObjectName("patientsSearchMethodLabel");
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(true);
        patientsSearchMethodLabel->setFont(font5);

        verticalLayout_21->addWidget(patientsSearchMethodLabel);

        patientsSearchMethodCombo = new QComboBox(widget);
        patientsSearchMethodCombo->setObjectName("patientsSearchMethodCombo");
        patientsSearchMethodCombo->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_21->addWidget(patientsSearchMethodCombo);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(patientsSortContainer);
        widget_2->setObjectName("widget_2");
        verticalLayout_22 = new QVBoxLayout(widget_2);
        verticalLayout_22->setSpacing(8);
        verticalLayout_22->setObjectName("verticalLayout_22");
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        patientsSortMethodLabel = new QLabel(widget_2);
        patientsSortMethodLabel->setObjectName("patientsSortMethodLabel");
        patientsSortMethodLabel->setFont(font5);

        verticalLayout_22->addWidget(patientsSortMethodLabel);

        patientsSortMethodCombo = new QComboBox(widget_2);
        patientsSortMethodCombo->setObjectName("patientsSortMethodCombo");
        sizePolicy2.setHeightForWidth(patientsSortMethodCombo->sizePolicy().hasHeightForWidth());
        patientsSortMethodCombo->setSizePolicy(sizePolicy2);
        patientsSortMethodCombo->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_22->addWidget(patientsSortMethodCombo);


        gridLayout_3->addWidget(widget_2, 0, 1, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);

        verticalLayout_12->addWidget(patientsSortContainer);


        horizontalLayout_11->addWidget(patientsTabSearchSortContainer);


        verticalLayout_14->addWidget(patientsTabTopContainer);

        patientsTablesContainer = new QWidget(patientsTab);
        patientsTablesContainer->setObjectName("patientsTablesContainer");
        gridLayout_2 = new QGridLayout(patientsTablesContainer);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(24);
        gridLayout_2->setVerticalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        patientsListContainer = new QWidget(patientsTablesContainer);
        patientsListContainer->setObjectName("patientsListContainer");
        sizePolicy1.setHeightForWidth(patientsListContainer->sizePolicy().hasHeightForWidth());
        patientsListContainer->setSizePolicy(sizePolicy1);
        verticalLayout_11 = new QVBoxLayout(patientsListContainer);
        verticalLayout_11->setSpacing(12);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_11->setContentsMargins(16, 16, 16, 16);
        patientsListContainerTop = new QWidget(patientsListContainer);
        patientsListContainerTop->setObjectName("patientsListContainerTop");
        sizePolicy2.setHeightForWidth(patientsListContainerTop->sizePolicy().hasHeightForWidth());
        patientsListContainerTop->setSizePolicy(sizePolicy2);
        horizontalLayout_14 = new QHBoxLayout(patientsListContainerTop);
        horizontalLayout_14->setSpacing(48);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        patientsListContainerTitleLabel = new QLabel(patientsListContainerTop);
        patientsListContainerTitleLabel->setObjectName("patientsListContainerTitleLabel");
        sizePolicy2.setHeightForWidth(patientsListContainerTitleLabel->sizePolicy().hasHeightForWidth());
        patientsListContainerTitleLabel->setSizePolicy(sizePolicy2);
        patientsListContainerTitleLabel->setFont(font2);

        horizontalLayout_14->addWidget(patientsListContainerTitleLabel);

        patientsActionsContainer = new QWidget(patientsListContainerTop);
        patientsActionsContainer->setObjectName("patientsActionsContainer");
        sizePolicy5.setHeightForWidth(patientsActionsContainer->sizePolicy().hasHeightForWidth());
        patientsActionsContainer->setSizePolicy(sizePolicy5);
        horizontalLayout_16 = new QHBoxLayout(patientsActionsContainer);
        horizontalLayout_16->setSpacing(16);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        createPatientAppointmentButton = new QPushButton(patientsActionsContainer);
        createPatientAppointmentButton->setObjectName("createPatientAppointmentButton");
        sizePolicy4.setHeightForWidth(createPatientAppointmentButton->sizePolicy().hasHeightForWidth());
        createPatientAppointmentButton->setSizePolicy(sizePolicy4);
        createPatientAppointmentButton->setMinimumSize(QSize(150, 36));
        createPatientAppointmentButton->setMaximumSize(QSize(150, 44));
        createPatientAppointmentButton->setFont(font3);
        createPatientAppointmentButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_16->addWidget(createPatientAppointmentButton);

        addToQueueButton = new QPushButton(patientsActionsContainer);
        addToQueueButton->setObjectName("addToQueueButton");
        sizePolicy4.setHeightForWidth(addToQueueButton->sizePolicy().hasHeightForWidth());
        addToQueueButton->setSizePolicy(sizePolicy4);
        addToQueueButton->setMinimumSize(QSize(120, 36));
        addToQueueButton->setMaximumSize(QSize(120, 44));
        addToQueueButton->setFont(font3);
        addToQueueButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_16->addWidget(addToQueueButton);


        horizontalLayout_14->addWidget(patientsActionsContainer);


        verticalLayout_11->addWidget(patientsListContainerTop);

        patientsTable = new QTableWidget(patientsListContainer);
        patientsTable->setObjectName("patientsTable");

        verticalLayout_11->addWidget(patientsTable);


        gridLayout_2->addWidget(patientsListContainer, 0, 0, 1, 1);

        scrollArea = new QScrollArea(patientsTablesContainer);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy8);
        scrollArea->setMinimumSize(QSize(380, 0));
        scrollArea->setMaximumSize(QSize(0, 16777215));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(false);
        scrollArea->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 468));
        sizePolicy5.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy5);
        scrollAreaWidgetContents->setMinimumSize(QSize(380, 0));
        scrollAreaWidgetContents->setMaximumSize(QSize(0, 16777215));
        verticalLayout_20 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_20->setSpacing(0);
        verticalLayout_20->setObjectName("verticalLayout_20");
        verticalLayout_20->setContentsMargins(0, 0, 24, 0);
        patientsFormContainer = new QWidget(scrollAreaWidgetContents);
        patientsFormContainer->setObjectName("patientsFormContainer");
        sizePolicy8.setHeightForWidth(patientsFormContainer->sizePolicy().hasHeightForWidth());
        patientsFormContainer->setSizePolicy(sizePolicy8);
        patientsFormContainer->setMinimumSize(QSize(380, 0));
        verticalLayout_13 = new QVBoxLayout(patientsFormContainer);
        verticalLayout_13->setSpacing(12);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_13->setContentsMargins(16, 16, 16, 16);
        patientsFormContainerTop = new QWidget(patientsFormContainer);
        patientsFormContainerTop->setObjectName("patientsFormContainerTop");
        sizePolicy2.setHeightForWidth(patientsFormContainerTop->sizePolicy().hasHeightForWidth());
        patientsFormContainerTop->setSizePolicy(sizePolicy2);
        horizontalLayout_15 = new QHBoxLayout(patientsFormContainerTop);
        horizontalLayout_15->setSpacing(48);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        patientsFormContainerTitleLabel = new QLabel(patientsFormContainerTop);
        patientsFormContainerTitleLabel->setObjectName("patientsFormContainerTitleLabel");
        sizePolicy2.setHeightForWidth(patientsFormContainerTitleLabel->sizePolicy().hasHeightForWidth());
        patientsFormContainerTitleLabel->setSizePolicy(sizePolicy2);
        patientsFormContainerTitleLabel->setFont(font2);

        horizontalLayout_15->addWidget(patientsFormContainerTitleLabel);

        clearPatientFormButton = new QPushButton(patientsFormContainerTop);
        clearPatientFormButton->setObjectName("clearPatientFormButton");
        sizePolicy4.setHeightForWidth(clearPatientFormButton->sizePolicy().hasHeightForWidth());
        clearPatientFormButton->setSizePolicy(sizePolicy4);
        clearPatientFormButton->setMaximumSize(QSize(64, 16777215));
        clearPatientFormButton->setFont(font4);
        clearPatientFormButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_15->addWidget(clearPatientFormButton);


        verticalLayout_13->addWidget(patientsFormContainerTop);

        patientFormCard = new QWidget(patientsFormContainer);
        patientFormCard->setObjectName("patientFormCard");
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(patientFormCard->sizePolicy().hasHeightForWidth());
        patientFormCard->setSizePolicy(sizePolicy9);
        verticalLayout_19 = new QVBoxLayout(patientFormCard);
        verticalLayout_19->setSpacing(16);
        verticalLayout_19->setObjectName("verticalLayout_19");
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        patientFormField = new QWidget(patientFormCard);
        patientFormField->setObjectName("patientFormField");
        sizePolicy2.setHeightForWidth(patientFormField->sizePolicy().hasHeightForWidth());
        patientFormField->setSizePolicy(sizePolicy2);
        verticalLayout_15 = new QVBoxLayout(patientFormField);
        verticalLayout_15->setSpacing(8);
        verticalLayout_15->setObjectName("verticalLayout_15");
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        patientFormLabel = new QLabel(patientFormField);
        patientFormLabel->setObjectName("patientFormLabel");
        sizePolicy2.setHeightForWidth(patientFormLabel->sizePolicy().hasHeightForWidth());
        patientFormLabel->setSizePolicy(sizePolicy2);
        QFont font6;
        font6.setBold(true);
        patientFormLabel->setFont(font6);

        verticalLayout_15->addWidget(patientFormLabel);

        patientNameInput = new QLineEdit(patientFormField);
        patientNameInput->setObjectName("patientNameInput");

        verticalLayout_15->addWidget(patientNameInput);


        verticalLayout_19->addWidget(patientFormField);

        patientFormField_2 = new QWidget(patientFormCard);
        patientFormField_2->setObjectName("patientFormField_2");
        sizePolicy2.setHeightForWidth(patientFormField_2->sizePolicy().hasHeightForWidth());
        patientFormField_2->setSizePolicy(sizePolicy2);
        verticalLayout_16 = new QVBoxLayout(patientFormField_2);
        verticalLayout_16->setSpacing(8);
        verticalLayout_16->setObjectName("verticalLayout_16");
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        patientFormLabel_2 = new QLabel(patientFormField_2);
        patientFormLabel_2->setObjectName("patientFormLabel_2");
        sizePolicy2.setHeightForWidth(patientFormLabel_2->sizePolicy().hasHeightForWidth());
        patientFormLabel_2->setSizePolicy(sizePolicy2);
        patientFormLabel_2->setFont(font6);

        verticalLayout_16->addWidget(patientFormLabel_2);

        patientAgeInput = new QSpinBox(patientFormField_2);
        patientAgeInput->setObjectName("patientAgeInput");
        patientAgeInput->setCursor(QCursor(Qt::CursorShape::IBeamCursor));
        patientAgeInput->setMinimum(1);
        patientAgeInput->setValue(18);

        verticalLayout_16->addWidget(patientAgeInput);


        verticalLayout_19->addWidget(patientFormField_2);

        patientFormField_3 = new QWidget(patientFormCard);
        patientFormField_3->setObjectName("patientFormField_3");
        sizePolicy2.setHeightForWidth(patientFormField_3->sizePolicy().hasHeightForWidth());
        patientFormField_3->setSizePolicy(sizePolicy2);
        verticalLayout_17 = new QVBoxLayout(patientFormField_3);
        verticalLayout_17->setSpacing(8);
        verticalLayout_17->setObjectName("verticalLayout_17");
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        patientFormLabel_3 = new QLabel(patientFormField_3);
        patientFormLabel_3->setObjectName("patientFormLabel_3");
        sizePolicy2.setHeightForWidth(patientFormLabel_3->sizePolicy().hasHeightForWidth());
        patientFormLabel_3->setSizePolicy(sizePolicy2);
        patientFormLabel_3->setFont(font6);

        verticalLayout_17->addWidget(patientFormLabel_3);

        patientContactInput = new QLineEdit(patientFormField_3);
        patientContactInput->setObjectName("patientContactInput");
        patientContactInput->setMaxLength(32767);

        verticalLayout_17->addWidget(patientContactInput);


        verticalLayout_19->addWidget(patientFormField_3);

        patientFormField_4 = new QWidget(patientFormCard);
        patientFormField_4->setObjectName("patientFormField_4");
        sizePolicy2.setHeightForWidth(patientFormField_4->sizePolicy().hasHeightForWidth());
        patientFormField_4->setSizePolicy(sizePolicy2);
        verticalLayout_18 = new QVBoxLayout(patientFormField_4);
        verticalLayout_18->setSpacing(8);
        verticalLayout_18->setObjectName("verticalLayout_18");
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        patientFormLabel_4 = new QLabel(patientFormField_4);
        patientFormLabel_4->setObjectName("patientFormLabel_4");
        sizePolicy2.setHeightForWidth(patientFormLabel_4->sizePolicy().hasHeightForWidth());
        patientFormLabel_4->setSizePolicy(sizePolicy2);
        patientFormLabel_4->setFont(font6);

        verticalLayout_18->addWidget(patientFormLabel_4);

        patientCategoryCombo = new QComboBox(patientFormField_4);
        patientCategoryCombo->setObjectName("patientCategoryCombo");
        patientCategoryCombo->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_18->addWidget(patientCategoryCombo);


        verticalLayout_19->addWidget(patientFormField_4);

        registerPatientButton = new QPushButton(patientFormCard);
        registerPatientButton->setObjectName("registerPatientButton");
        registerPatientButton->setMinimumSize(QSize(0, 48));
        registerPatientButton->setMaximumSize(QSize(16777215, 48));
        registerPatientButton->setFont(font6);
        registerPatientButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_19->addWidget(registerPatientButton);


        verticalLayout_13->addWidget(patientFormCard);


        verticalLayout_20->addWidget(patientsFormContainer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 3);
        gridLayout_2->setColumnStretch(1, 2);

        verticalLayout_14->addWidget(patientsTablesContainer);

        mainTabWidget->addTab(patientsTab, QString());
        appointmentsTab = new QWidget();
        appointmentsTab->setObjectName("appointmentsTab");
        verticalLayout_35 = new QVBoxLayout(appointmentsTab);
        verticalLayout_35->setSpacing(24);
        verticalLayout_35->setObjectName("verticalLayout_35");
        verticalLayout_35->setContentsMargins(0, 0, 0, 0);
        appointmentsTabTopContainer = new QWidget(appointmentsTab);
        appointmentsTabTopContainer->setObjectName("appointmentsTabTopContainer");
        horizontalLayout_13 = new QHBoxLayout(appointmentsTabTopContainer);
        horizontalLayout_13->setSpacing(64);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        appointmentsTabTitleContainer = new QWidget(appointmentsTabTopContainer);
        appointmentsTabTitleContainer->setObjectName("appointmentsTabTitleContainer");
        sizePolicy3.setHeightForWidth(appointmentsTabTitleContainer->sizePolicy().hasHeightForWidth());
        appointmentsTabTitleContainer->setSizePolicy(sizePolicy3);
        verticalLayout_23 = new QVBoxLayout(appointmentsTabTitleContainer);
        verticalLayout_23->setSpacing(4);
        verticalLayout_23->setObjectName("verticalLayout_23");
        verticalLayout_23->setContentsMargins(0, 0, 0, 0);
        appointmentsTabTitleLabel = new QLabel(appointmentsTabTitleContainer);
        appointmentsTabTitleLabel->setObjectName("appointmentsTabTitleLabel");
        sizePolicy4.setHeightForWidth(appointmentsTabTitleLabel->sizePolicy().hasHeightForWidth());
        appointmentsTabTitleLabel->setSizePolicy(sizePolicy4);
        appointmentsTabTitleLabel->setFont(font);
        appointmentsTabTitleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_23->addWidget(appointmentsTabTitleLabel);

        appointmentsTabSubtitleLabel = new QLabel(appointmentsTabTitleContainer);
        appointmentsTabSubtitleLabel->setObjectName("appointmentsTabSubtitleLabel");
        sizePolicy2.setHeightForWidth(appointmentsTabSubtitleLabel->sizePolicy().hasHeightForWidth());
        appointmentsTabSubtitleLabel->setSizePolicy(sizePolicy2);
        appointmentsTabSubtitleLabel->setFont(font1);
        appointmentsTabSubtitleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        appointmentsTabSubtitleLabel->setWordWrap(true);

        verticalLayout_23->addWidget(appointmentsTabSubtitleLabel);


        horizontalLayout_13->addWidget(appointmentsTabTitleContainer);


        verticalLayout_35->addWidget(appointmentsTabTopContainer);

        appointmentsTablesContainer = new QWidget(appointmentsTab);
        appointmentsTablesContainer->setObjectName("appointmentsTablesContainer");
        gridLayout_5 = new QGridLayout(appointmentsTablesContainer);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setHorizontalSpacing(24);
        gridLayout_5->setVerticalSpacing(0);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        appointmentsListContainer = new QWidget(appointmentsTablesContainer);
        appointmentsListContainer->setObjectName("appointmentsListContainer");
        sizePolicy1.setHeightForWidth(appointmentsListContainer->sizePolicy().hasHeightForWidth());
        appointmentsListContainer->setSizePolicy(sizePolicy1);
        verticalLayout_27 = new QVBoxLayout(appointmentsListContainer);
        verticalLayout_27->setSpacing(12);
        verticalLayout_27->setObjectName("verticalLayout_27");
        verticalLayout_27->setContentsMargins(16, 16, 16, 16);
        appointmentsListContainerTop = new QWidget(appointmentsListContainer);
        appointmentsListContainerTop->setObjectName("appointmentsListContainerTop");
        sizePolicy2.setHeightForWidth(appointmentsListContainerTop->sizePolicy().hasHeightForWidth());
        appointmentsListContainerTop->setSizePolicy(sizePolicy2);
        horizontalLayout_18 = new QHBoxLayout(appointmentsListContainerTop);
        horizontalLayout_18->setSpacing(48);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        appointmentsListContainerTitleLabel = new QLabel(appointmentsListContainerTop);
        appointmentsListContainerTitleLabel->setObjectName("appointmentsListContainerTitleLabel");
        sizePolicy2.setHeightForWidth(appointmentsListContainerTitleLabel->sizePolicy().hasHeightForWidth());
        appointmentsListContainerTitleLabel->setSizePolicy(sizePolicy2);
        appointmentsListContainerTitleLabel->setFont(font2);

        horizontalLayout_18->addWidget(appointmentsListContainerTitleLabel);

        appointmentsActionsContainer = new QWidget(appointmentsListContainerTop);
        appointmentsActionsContainer->setObjectName("appointmentsActionsContainer");
        sizePolicy5.setHeightForWidth(appointmentsActionsContainer->sizePolicy().hasHeightForWidth());
        appointmentsActionsContainer->setSizePolicy(sizePolicy5);
        horizontalLayout_19 = new QHBoxLayout(appointmentsActionsContainer);
        horizontalLayout_19->setSpacing(16);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        cancelAppointmentButton = new QPushButton(appointmentsActionsContainer);
        cancelAppointmentButton->setObjectName("cancelAppointmentButton");
        sizePolicy4.setHeightForWidth(cancelAppointmentButton->sizePolicy().hasHeightForWidth());
        cancelAppointmentButton->setSizePolicy(sizePolicy4);
        cancelAppointmentButton->setMinimumSize(QSize(150, 36));
        cancelAppointmentButton->setMaximumSize(QSize(150, 44));
        cancelAppointmentButton->setFont(font3);
        cancelAppointmentButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_19->addWidget(cancelAppointmentButton);


        horizontalLayout_18->addWidget(appointmentsActionsContainer);


        verticalLayout_27->addWidget(appointmentsListContainerTop);

        appointmentsTable = new QTableWidget(appointmentsListContainer);
        appointmentsTable->setObjectName("appointmentsTable");

        verticalLayout_27->addWidget(appointmentsTable);


        gridLayout_5->addWidget(appointmentsListContainer, 0, 0, 1, 1);

        scrollArea_2 = new QScrollArea(appointmentsTablesContainer);
        scrollArea_2->setObjectName("scrollArea_2");
        sizePolicy8.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy8);
        scrollArea_2->setMinimumSize(QSize(380, 0));
        scrollArea_2->setMaximumSize(QSize(0, 16777215));
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(false);
        scrollArea_2->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 380, 468));
        sizePolicy5.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy5);
        scrollAreaWidgetContents_2->setMinimumSize(QSize(380, 0));
        scrollAreaWidgetContents_2->setMaximumSize(QSize(0, 16777215));
        verticalLayout_28 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_28->setSpacing(0);
        verticalLayout_28->setObjectName("verticalLayout_28");
        verticalLayout_28->setContentsMargins(0, 0, 24, 0);
        appointmentsFormContainer = new QWidget(scrollAreaWidgetContents_2);
        appointmentsFormContainer->setObjectName("appointmentsFormContainer");
        sizePolicy8.setHeightForWidth(appointmentsFormContainer->sizePolicy().hasHeightForWidth());
        appointmentsFormContainer->setSizePolicy(sizePolicy8);
        appointmentsFormContainer->setMinimumSize(QSize(380, 0));
        verticalLayout_29 = new QVBoxLayout(appointmentsFormContainer);
        verticalLayout_29->setSpacing(12);
        verticalLayout_29->setObjectName("verticalLayout_29");
        verticalLayout_29->setContentsMargins(16, 16, 16, 16);
        appointmentsFormContainerTop = new QWidget(appointmentsFormContainer);
        appointmentsFormContainerTop->setObjectName("appointmentsFormContainerTop");
        sizePolicy2.setHeightForWidth(appointmentsFormContainerTop->sizePolicy().hasHeightForWidth());
        appointmentsFormContainerTop->setSizePolicy(sizePolicy2);
        horizontalLayout_20 = new QHBoxLayout(appointmentsFormContainerTop);
        horizontalLayout_20->setSpacing(48);
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        appointmentsFormContainerTitleLabel = new QLabel(appointmentsFormContainerTop);
        appointmentsFormContainerTitleLabel->setObjectName("appointmentsFormContainerTitleLabel");
        sizePolicy2.setHeightForWidth(appointmentsFormContainerTitleLabel->sizePolicy().hasHeightForWidth());
        appointmentsFormContainerTitleLabel->setSizePolicy(sizePolicy2);
        appointmentsFormContainerTitleLabel->setFont(font2);

        horizontalLayout_20->addWidget(appointmentsFormContainerTitleLabel);

        clearAppointmentFormButton = new QPushButton(appointmentsFormContainerTop);
        clearAppointmentFormButton->setObjectName("clearAppointmentFormButton");
        sizePolicy4.setHeightForWidth(clearAppointmentFormButton->sizePolicy().hasHeightForWidth());
        clearAppointmentFormButton->setSizePolicy(sizePolicy4);
        clearAppointmentFormButton->setMaximumSize(QSize(64, 16777215));
        clearAppointmentFormButton->setFont(font4);
        clearAppointmentFormButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_20->addWidget(clearAppointmentFormButton);


        verticalLayout_29->addWidget(appointmentsFormContainerTop);

        appointmentFormCard = new QWidget(appointmentsFormContainer);
        appointmentFormCard->setObjectName("appointmentFormCard");
        sizePolicy9.setHeightForWidth(appointmentFormCard->sizePolicy().hasHeightForWidth());
        appointmentFormCard->setSizePolicy(sizePolicy9);
        verticalLayout_30 = new QVBoxLayout(appointmentFormCard);
        verticalLayout_30->setSpacing(16);
        verticalLayout_30->setObjectName("verticalLayout_30");
        verticalLayout_30->setContentsMargins(0, 0, 0, 0);
        appointmentFormField_1 = new QWidget(appointmentFormCard);
        appointmentFormField_1->setObjectName("appointmentFormField_1");
        sizePolicy2.setHeightForWidth(appointmentFormField_1->sizePolicy().hasHeightForWidth());
        appointmentFormField_1->setSizePolicy(sizePolicy2);
        verticalLayout_31 = new QVBoxLayout(appointmentFormField_1);
        verticalLayout_31->setSpacing(8);
        verticalLayout_31->setObjectName("verticalLayout_31");
        verticalLayout_31->setContentsMargins(0, 0, 0, 0);
        appointmentFormLabel = new QLabel(appointmentFormField_1);
        appointmentFormLabel->setObjectName("appointmentFormLabel");
        sizePolicy2.setHeightForWidth(appointmentFormLabel->sizePolicy().hasHeightForWidth());
        appointmentFormLabel->setSizePolicy(sizePolicy2);
        appointmentFormLabel->setFont(font6);

        verticalLayout_31->addWidget(appointmentFormLabel);

        appointmentPatientInput = new QLineEdit(appointmentFormField_1);
        appointmentPatientInput->setObjectName("appointmentPatientInput");
        appointmentPatientInput->setCursor(QCursor(Qt::CursorShape::ForbiddenCursor));
        appointmentPatientInput->setReadOnly(true);

        verticalLayout_31->addWidget(appointmentPatientInput);

        appointmentFormFieldInfoLabel = new QLabel(appointmentFormField_1);
        appointmentFormFieldInfoLabel->setObjectName("appointmentFormFieldInfoLabel");

        verticalLayout_31->addWidget(appointmentFormFieldInfoLabel);


        verticalLayout_30->addWidget(appointmentFormField_1);

        appointmentFormField_2 = new QWidget(appointmentFormCard);
        appointmentFormField_2->setObjectName("appointmentFormField_2");
        sizePolicy2.setHeightForWidth(appointmentFormField_2->sizePolicy().hasHeightForWidth());
        appointmentFormField_2->setSizePolicy(sizePolicy2);
        verticalLayout_32 = new QVBoxLayout(appointmentFormField_2);
        verticalLayout_32->setSpacing(8);
        verticalLayout_32->setObjectName("verticalLayout_32");
        verticalLayout_32->setContentsMargins(0, 0, 0, 0);
        appointmentFormLabel_2 = new QLabel(appointmentFormField_2);
        appointmentFormLabel_2->setObjectName("appointmentFormLabel_2");
        sizePolicy2.setHeightForWidth(appointmentFormLabel_2->sizePolicy().hasHeightForWidth());
        appointmentFormLabel_2->setSizePolicy(sizePolicy2);
        appointmentFormLabel_2->setFont(font6);

        verticalLayout_32->addWidget(appointmentFormLabel_2);

        appointmentReasonInput = new QLineEdit(appointmentFormField_2);
        appointmentReasonInput->setObjectName("appointmentReasonInput");

        verticalLayout_32->addWidget(appointmentReasonInput);


        verticalLayout_30->addWidget(appointmentFormField_2);

        appointmentFormField_3 = new QWidget(appointmentFormCard);
        appointmentFormField_3->setObjectName("appointmentFormField_3");
        sizePolicy2.setHeightForWidth(appointmentFormField_3->sizePolicy().hasHeightForWidth());
        appointmentFormField_3->setSizePolicy(sizePolicy2);
        verticalLayout_33 = new QVBoxLayout(appointmentFormField_3);
        verticalLayout_33->setSpacing(8);
        verticalLayout_33->setObjectName("verticalLayout_33");
        verticalLayout_33->setContentsMargins(0, 0, 0, 0);
        appointmentFormLabel_3 = new QLabel(appointmentFormField_3);
        appointmentFormLabel_3->setObjectName("appointmentFormLabel_3");
        sizePolicy2.setHeightForWidth(appointmentFormLabel_3->sizePolicy().hasHeightForWidth());
        appointmentFormLabel_3->setSizePolicy(sizePolicy2);
        appointmentFormLabel_3->setFont(font6);

        verticalLayout_33->addWidget(appointmentFormLabel_3);

        appointmentDateInput = new QDateEdit(appointmentFormField_3);
        appointmentDateInput->setObjectName("appointmentDateInput");
        appointmentDateInput->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        appointmentDateInput->setMaximumDate(QDate(2099, 12, 31));
        appointmentDateInput->setCalendarPopup(true);

        verticalLayout_33->addWidget(appointmentDateInput);


        verticalLayout_30->addWidget(appointmentFormField_3);

        appointmentFormField_4 = new QWidget(appointmentFormCard);
        appointmentFormField_4->setObjectName("appointmentFormField_4");
        sizePolicy2.setHeightForWidth(appointmentFormField_4->sizePolicy().hasHeightForWidth());
        appointmentFormField_4->setSizePolicy(sizePolicy2);
        verticalLayout_34 = new QVBoxLayout(appointmentFormField_4);
        verticalLayout_34->setSpacing(8);
        verticalLayout_34->setObjectName("verticalLayout_34");
        verticalLayout_34->setContentsMargins(0, 0, 0, 0);
        appointmentFormLabel_4 = new QLabel(appointmentFormField_4);
        appointmentFormLabel_4->setObjectName("appointmentFormLabel_4");
        sizePolicy2.setHeightForWidth(appointmentFormLabel_4->sizePolicy().hasHeightForWidth());
        appointmentFormLabel_4->setSizePolicy(sizePolicy2);
        appointmentFormLabel_4->setFont(font6);

        verticalLayout_34->addWidget(appointmentFormLabel_4);

        appointmentTimeInput = new QTimeEdit(appointmentFormField_4);
        appointmentTimeInput->setObjectName("appointmentTimeInput");
        appointmentTimeInput->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_34->addWidget(appointmentTimeInput);


        verticalLayout_30->addWidget(appointmentFormField_4);

        scheduleAppointmentButton = new QPushButton(appointmentFormCard);
        scheduleAppointmentButton->setObjectName("scheduleAppointmentButton");
        scheduleAppointmentButton->setMinimumSize(QSize(0, 48));
        scheduleAppointmentButton->setMaximumSize(QSize(16777215, 48));
        scheduleAppointmentButton->setFont(font6);
        scheduleAppointmentButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_30->addWidget(scheduleAppointmentButton);


        verticalLayout_29->addWidget(appointmentFormCard);


        verticalLayout_28->addWidget(appointmentsFormContainer);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_5->addWidget(scrollArea_2, 0, 1, 1, 1);

        gridLayout_5->setColumnStretch(0, 3);
        gridLayout_5->setColumnStretch(1, 2);

        verticalLayout_35->addWidget(appointmentsTablesContainer);

        mainTabWidget->addTab(appointmentsTab, QString());
        reportsTab = new QWidget();
        reportsTab->setObjectName("reportsTab");
        mainTabWidget->addTab(reportsTab, QString());
        adminTab = new QWidget();
        adminTab->setObjectName("adminTab");
        mainTabWidget->addTab(adminTab, QString());

        verticalLayout->addWidget(mainTabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        mainTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        overviewTitleLabel->setText(QCoreApplication::translate("MainWindow", "Clinical Overview", nullptr));
        overviewSubtitleLabel->setText(QCoreApplication::translate("MainWindow", "Monitor clinic activities, patient statistics, waiting queues and upcoming appointments", nullptr));
        totalPatientsTitleLabel->setText(QCoreApplication::translate("MainWindow", "Total Patients", nullptr));
        totalPatientsValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        todayAppointmentsTitleLabel->setText(QCoreApplication::translate("MainWindow", "Today's Appointments", nullptr));
        todayAppointmentsValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        waitingPatientsTitleLabel->setText(QCoreApplication::translate("MainWindow", "Waiting Patients", nullptr));
        waitingPatientsValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        emergencyPatientsTitleLabel->setText(QCoreApplication::translate("MainWindow", "Emergency Patients", nullptr));
        emergencyPatientsValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        waitingQueueContainerTitleLabel->setText(QCoreApplication::translate("MainWindow", "Patients Waiting Queue", nullptr));
        nextPatientButton->setText(QCoreApplication::translate("MainWindow", "Next patient", nullptr));
        upcomingAppointmentsContainerTitleLabel->setText(QCoreApplication::translate("MainWindow", "Upcoming Appointments", nullptr));
        viewAllAppointmentsButton->setText(QCoreApplication::translate("MainWindow", "View all", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(dashboardTab), QCoreApplication::translate("MainWindow", "Clinical Overview", nullptr));
        patientsTabTitleLabel->setText(QCoreApplication::translate("MainWindow", "Patients Management", nullptr));
        patientsTabSubtitleLabel->setText(QCoreApplication::translate("MainWindow", "Register new patients, manage patient records and quickly find the information you need", nullptr));
        patientsSearchMethodLabel->setText(QCoreApplication::translate("MainWindow", "Search Method", nullptr));
        patientsSortMethodLabel->setText(QCoreApplication::translate("MainWindow", "Sort Method", nullptr));
        patientsListContainerTitleLabel->setText(QString());
        createPatientAppointmentButton->setText(QCoreApplication::translate("MainWindow", "Create Appointment", nullptr));
        addToQueueButton->setText(QCoreApplication::translate("MainWindow", "Add to queue", nullptr));
        patientsFormContainerTitleLabel->setText(QCoreApplication::translate("MainWindow", "Add New Patients", nullptr));
        clearPatientFormButton->setText(QCoreApplication::translate("MainWindow", "Clear form", nullptr));
        patientFormLabel->setText(QCoreApplication::translate("MainWindow", "Full Name", nullptr));
        patientNameInput->setInputMask(QString());
        patientNameInput->setText(QString());
        patientFormLabel_2->setText(QCoreApplication::translate("MainWindow", "Patient Age", nullptr));
        patientFormLabel_3->setText(QCoreApplication::translate("MainWindow", "Contact Phone Number", nullptr));
        patientContactInput->setInputMask(QString());
        patientContactInput->setText(QString());
        patientFormLabel_4->setText(QCoreApplication::translate("MainWindow", "Patient Category", nullptr));
        registerPatientButton->setText(QCoreApplication::translate("MainWindow", "Register Patient", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(patientsTab), QCoreApplication::translate("MainWindow", "Patients Management", nullptr));
        appointmentsTabTitleLabel->setText(QCoreApplication::translate("MainWindow", "Appointment Schedule Management", nullptr));
        appointmentsTabSubtitleLabel->setText(QCoreApplication::translate("MainWindow", "Schedule consultations, track upcoming appointments and manage appointment requests", nullptr));
        appointmentsListContainerTitleLabel->setText(QString());
        cancelAppointmentButton->setText(QCoreApplication::translate("MainWindow", "Cancel Appointment", nullptr));
        appointmentsFormContainerTitleLabel->setText(QCoreApplication::translate("MainWindow", "Add New Appointment", nullptr));
        clearAppointmentFormButton->setText(QCoreApplication::translate("MainWindow", "Clear form", nullptr));
        appointmentFormLabel->setText(QCoreApplication::translate("MainWindow", "Patient Name", nullptr));
        appointmentPatientInput->setInputMask(QString());
        appointmentPatientInput->setText(QString());
        appointmentFormFieldInfoLabel->setText(QCoreApplication::translate("MainWindow", "Select a patient from the patient management list", nullptr));
        appointmentFormLabel_2->setText(QCoreApplication::translate("MainWindow", "Reason For Appointment", nullptr));
        appointmentFormLabel_3->setText(QCoreApplication::translate("MainWindow", "Date Of Appointment", nullptr));
        appointmentDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd MMM, yyyy", nullptr));
        appointmentFormLabel_4->setText(QCoreApplication::translate("MainWindow", "Time Of Appointment", nullptr));
        appointmentTimeInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "hh:mm AP", nullptr));
        scheduleAppointmentButton->setText(QCoreApplication::translate("MainWindow", "Schedule Appointment", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(appointmentsTab), QCoreApplication::translate("MainWindow", "Appointment Schedules", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(reportsTab), QCoreApplication::translate("MainWindow", "Reports Analysis", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(adminTab), QCoreApplication::translate("MainWindow", "Administration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
