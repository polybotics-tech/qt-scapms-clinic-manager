#include "MainWindow.h"
#include "gui/ui_MainWindow.h"

#include "models/EmergencyPatient.h"
#include "models/FollowUpPatient.h"
#include "models/GeneralPatient.h"

#include <QAbstractItemView>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QHeaderView>
#include <QIcon>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QStandardPaths>
#include <QTableWidgetItem>
#include <QTimer>
#include <algorithm>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Miva SCAPMS | Dashboard");

    //--initialize persisted data file path
    QString dataDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDirectory);
    dataFilePath = dataDirectory + "/scapms_data.json";
    if (QFile::exists(dataFilePath)) {
        if (!database.loadDataFromJson(dataFilePath)) {
            QMessageBox::warning(this,
                                 "Data Loading Error",
                                 "The saved application data could not be loaded.\n"
                                 "The application will start with an empty database.");
        }
    }

    //--setup and populate the overview tables
    setupOverviewTables();
    refreshOverviewTables();

    //--setup and populate the patients table
    setupPatientsTable();
    refreshPatientsTable();

    //--setup and populate the appointments table
    setupAppointmentsTable();
    refreshAppointmentsTable();

    //--setup and populate the reports table
    setupReportsTable();

    //--setup and populate the admins table
    setupAdminTable();
    refreshAdminTable();
    refreshAdminStatistics();

    //--populate patient search options
    ui->patientsSearchMethodCombo->addItem("Recursive Search (Patient Name)", "recursive_name");
    ui->patientsSearchMethodCombo->addItem("Linear Search (Patient ID)", "linear_id");
    ui->patientsSearchMethodCombo->addItem("Binary Search (Patient Name)", "binary_name");

    //--populate patient sorting options
    ui->patientsSortMethodCombo->addItem("Patient Name (A - Z)", "name");
    ui->patientsSortMethodCombo->addItem("Patient Age (Ascending)", "age");
    applyPatientFiltersAndSort();

    //--populate patient category options
    ui->patientCategoryCombo->addItem("Select Category", "");
    ui->patientCategoryCombo->addItem("General Patient", "General");
    ui->patientCategoryCombo->addItem("Emergency Patient", "Emergency");
    ui->patientCategoryCombo->addItem("Follow-up Patient", "Follow-up");

    //--populate patient input placeholders
    ui->patientsSearchInput->setPlaceholderText("Search patient by ID or name...");
    ui->patientNameInput->setPlaceholderText("Ex. Ogbuju Emeka");
    ui->patientContactInput->setPlaceholderText("Ex. 07010000000");

    //--populate age spinner metadata
    ui->patientAgeInput->setRange(1, 120);
    ui->patientAgeInput->setValue(18);
    ui->patientAgeInput->setSpecialValueText("Select age");

    //--populate appointment date & time metadata
    ui->appointmentDateInput->setCalendarPopup(true);
    ui->appointmentDateInput->setDisplayFormat("dd MMM, yyyy");
    ui->appointmentDateInput->setMinimumDate(QDate::currentDate());
    ui->appointmentTimeInput->setDisplayFormat("hh:mm AP");

    //--populate reports type options
    ui->reportTypeCombo->addItem("Daily Appointment Summary", "daily_summary");
    ui->reportTypeCombo->addItem("Frequent Patients", "frequent_patients");
    ui->reportTypeCombo->addItem("Pending Appointments", "pending_appointments");
    ui->reportTypeCombo->addItem("Patient Category Distribution", "category_distribution");

    //--main window styling
    setStyleSheet(QString(R"(
            QWidget#MainWindow {
                background-color: #ffffff;
            }

            QLabel#brandNameLabel {
                font-size: 13px;
                color: #121736;
                font-weight: bold;
            }

            QWidget#centralWidget {
                padding: 24px;
            }

            QLabel#overviewTitleLabel,
            QLabel#patientsTabTitleLabel,
            QLabel#appointmentsTabTitleLabel,
            QLabel#reportsTabTitleLabel,
            QLabel#adminTabTitleLabel {
                font-size: 20px;
                color: #121736;
                font-weight: bold;
            }

            QLabel#overviewSubtitleLabel,
            QLabel#patientsTabSubtitleLabel,
            QLabel#appointmentsTabSubtitleLabel,
            QLabel#reportsTabSubtitleLabel,
            QLabel#adminTabSubtitleLabel {
                font-size: 11px;
                color: #8996a3;
                font-weight: normal;
            }

            QWidget#waitingQueueContainer,
            QWidget#upcomingAppointmentsContainer,
            QWidget#patientsTabSearchSortContainer,
            QWidget#patientsListContainer,
            QWidget#patientsFormContainer,
            QWidget#appointmentsTabSearchSortContainer,
            QWidget#appointmentsListContainer,
            QWidget#appointmentsFormContainer,
            QWidget#reportsTabTableContainer,
            QWidget#reportsTabSortContainer,
            QWidget#adminTabTableContainer {
                background-color: #ffffff;
                border-radius: 16px;
                border: 1px solid #e0e6eb;
            }

            QLabel#waitingQueueContainerTitleLabel,
            QLabel#upcomingAppointmentsContainerTitleLabel,
            QLabel#patientsFormContainerTitleLabel,
            QLabel#appointmentsFormContainerTitleLabel {
                font-size: 16px;
                color: #121736;
                font-weight: bold;
            }

            QLabel#adminHistoryTitleLabel {
                font-size: 13px;
                color: #121736;
                font-weight: bold;
            }

            QScrollArea {
                background-color: transparent;
                border: none;
            }
        
            QScrollArea > QWidget > QWidget {
                background-color: transparent;
            }
        
            QScrollBar:vertical {
                background-color: transparent;
                width: 8px;
                margin: 0px;
                border: none;
            }
        
            QScrollBar::handle:vertical {
                background-color: #e0e6eb;
                border-radius: 4px;
                min-height: 30px;
            }
        
            QScrollBar::handle:vertical:hover {
                background-color: #8996a3;
            }
        
            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical {
                height: 0px;
                background: transparent;
                border: none;
            }
        
            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background: transparent;
            }

            QTableWidget {
                background-color: #FFFFFF;
                alternate-background-color: #F5F7FA;
                color: #273044;
                border: 1px solid #E2E8F0;
                border-radius: 10px;
                gridline-color: #EDF0F4;
                selection-background-color: rgba(13, 155, 131, 0.14);
                selection-color: #0D6F61;
                outline: none;
                font-size: 13px;
            }
    
            QTableWidget::item {
                padding: 9px 8px;
                border: none;
                border-bottom: 1px solid #EDF0F4;
            }
    
            QTableWidget::item:selected {
                background-color: rgba(13, 155, 131, 0.14);
                color: #0D6F61;
            }
    
            QHeaderView::section {
                background-color: #F0F3F7;
                color: #263449;
                font-size: 14px;
                font-weight: 700;
                padding: 12px 8px;
                border: none;
                border-bottom: 2px solid #DCE3EA;
            }
    
            QHeaderView::section:horizontal {
                border-right: 1px solid #E2E8F0;
            }
    
            QHeaderView::section:vertical {
                background-color: #F8FAFC;
            }
    
            QTableCornerButton::section {
                background-color: #F0F3F7;
                border: none;
                border-bottom: 2px solid #DCE3EA;
            }
        )"));

    //--tab widget styling
    QString tabWidgetStyle = QString(R"(
            QTabWidget::pane {
                background-color: #f5f6f7;
                border: 1px solid #e0e6eb;
                border-radius: 24px;
                padding: 24px;
            }
        
            QTabBar::tab {
                background-color: #f5f6f7;
                color: #8996a3;
                border: 1px solid #e0e6eb;
                border-radius: 16px;
                padding: 8px 12px;
                margin-right: 16px;
                margin-bottom: 16px;
                font-size: 11px;
                font-weight: semibold;
            }
        
            QTabBar::tab:selected {
                background-color: rgba(73, 179, 162, 0.1);
                color: #49b3a2;
                font-weight: bold;
            }
        
            QTabBar::tab:!selected:hover {
                opacity: 0.7
            }
        
            QTabBar::tab:focus {
                outline: none;
            }
    )");
    ui->mainTabWidget->setStyleSheet(tabWidgetStyle);

    //--dashboard tab styling
    QString dashboardTabStyle = QString(R"(         
            QWidget#totalPatientsCard,
            QWidget#todayAppointmentsCard,
            QWidget#waitingPatientsCard,
            QWidget#emergencyPatientsCard {
                padding: 16px;
                background-color: #ffffff;
                border-radius: 16px;
                border: 1px solid #e0e6eb;
            }

            QLabel#totalPatientsTitleLabel,
            QLabel#todayAppointmentsTitleLabel,
            QLabel#waitingPatientsTitleLabel,
            QLabel#emergencyPatientsTitleLabel {
                font-size: 13px;
                color: #3a3e58;
                font-weight: semibold;
            }

            QLabel#totalPatientsValue,
            QLabel#todayAppointmentsValue,
            QLabel#waitingPatientsValue,
            QLabel#emergencyPatientsValue {
                font-size: 24px;
                color: #121736;
                font-weight: bold;
            }

            QPushButton#nextPatientButton,
            QPushButton#viewAllAppointmentsButton {
                outline: none;
                border: none;
                color: #49b3a2;
                font-size: 11px;
                font-weight: semibold;
                background-color: transparent;
            }
            
    )");
    ui->dashboardTab->setStyleSheet(dashboardTabStyle);

    //--patients tab styling
    QString patientsTabStyle = QString(R"(         
            QPushButton#createPatientAppointmentButton,
            QPushButton#addToQueueButton,
            QPushButton#clearPatientFormButton {
                outline: none;
                font-size: 11px;
                font-weight: medium;
            }

            QPushButton#createPatientAppointmentButton {
                color: #49b3a2;
                background-color: rgba(13, 155, 131, 0.1);
                border-radius: 18px;
            }

            QPushButton#addToQueueButton {
                color: #2563eb;
                background-color: rgba(37, 99, 235, 0.1);
                border-radius: 18px;
            }

            QPushButton#clearPatientFormButton {
                color: #dc2b2b;
                background-color: transparent;
            }

            QPushButton#registerPatientButton {
                background-color: #0D9B83;
                color: #fffdf7;
                border: 0px;
                border-radius: 24px;
                font-size: 13px;
                font-weight: medium;
            }

            QLabel#patientFormLabel,
            QLabel#patientFormLabel_2,
            QLabel#patientFormLabel_3,
            QLabel#patientFormLabel_4,
            QLabel#patientsSearchMethodLabel,
            QLabel#patientsSortMethodLabel {
                color: #3a3e58;
                font-size: 13px;
                font-weight: bold;
            }
    )");
    ui->patientsTab->setStyleSheet(patientsTabStyle);

    //--appointments tab styling
    QString appointmentsTabStyle = QString(R"(         
            QPushButton#cancelAppointmentButton,
            QPushButton#clearAppointmentFormButton {
                outline: none;
                font-size: 11px;
                font-weight: medium;
            }

            QPushButton#cancelAppointmentButton {
                color: #dc2b2b;
                background-color: rgba(220, 43, 43, 0.1);
                border-radius: 18px;
            }

            QPushButton#clearAppointmentFormButton {
                color: #dc2b2b;
                background-color: transparent;
            }

            QPushButton#scheduleAppointmentButton {
                background-color: #0D9B83;
                color: #fffdf7;
                border: 0px;
                border-radius: 24px;
                font-size: 13px;
                font-weight: medium;
            }

            QLabel#appointmentFormLabel,
            QLabel#appointmentFormLabel_2,
            QLabel#appointmentFormLabel_3,
            QLabel#appointmentFormLabel_4 {
                color: #3a3e58;
                font-size: 13px;
                font-weight: bold;
            }

            QLabel#appointmentFormFieldInfoLabel {
                color: #8996a3;
                font-size: 11px;
            }
            
    )");
    ui->appointmentsTab->setStyleSheet(appointmentsTabStyle);

    //--reports tab styling
    QString reportsTabStyle = QString(R"(         
            QPushButton#generateReportButton {
                outline: none;
                font-size: 11px;
                font-weight: medium;
                color: #49b3a2;
                background-color: rgba(73, 179, 162, 0.1);
                border-radius: 18px;
            }

            QLabel#reportsTabSortContainerLabel {
                color: #3a3e58;
                font-size: 13px;
                font-weight: bold;
            }

            QLabel#reportDescriptionLabel,
            QLabel#reportSummaryLabel {
                color: #8996a3;
                font-size: 11px;
            }
            
    )");
    ui->reportsTab->setStyleSheet(reportsTabStyle);

    //--admin tab styling
    QString adminTabStyle = QString(R"(         
            QWidget#totalPatientsCard,
            QWidget#todayAppointmentsCard,
            QWidget#waitingPatientsCard,
            QWidget#emergencyPatientsCard,
            QWidget#totalAdminActionsCard,
            QWidget#reversibleActionsCard,
            QWidget#lastActionCard {
                padding: 16px;
                background-color: #ffffff;
                border-radius: 16px;
                border: 1px solid #e0e6eb;
            }

            QLabel#totalPatientsTitleLabel,
            QLabel#todayAppointmentsTitleLabel,
            QLabel#waitingPatientsTitleLabel,
            QLabel#emergencyPatientsTitleLabel,
            QLabel#totalAdminActionsTitleLabel,
            QLabel#reversibleActionsTitleLabel,
            QLabel#lastActionTitleLabel {
                font-size: 13px;
                color: #3a3e58;
                font-weight: semibold;
            }

            QLabel#totalPatientsValue,
            QLabel#todayAppointmentsValue,
            QLabel#waitingPatientsValue,
            QLabel#emergencyPatientsValue,
            QLabel#totalAdminActionsValue,
            QLabel#reversibleActionsValue,
            QLabel#lastActionValue {
                font-size: 24px;
                color: #121736;
                font-weight: bold;
            }

            QPushButton#undoLastActionButton,
            QPushButton#clearAdminHistoryButton {
                outline: none;
                font-size: 11px;
                font-weight: medium;
                border-radius: 18px;
            }

            QPushButton#undoLastActionButton {
                color: #2563eb;
                background-color: rgba(37, 99, 235, 0.1);
            }

            QPushButton#clearAdminHistoryButton {
                color: #dc2b2b;
                background-color: rgba(220, 43, 43, 0.1);
            }
    )");
    ui->adminTab->setStyleSheet(adminTabStyle);

    //--reuseable input stylings
    QString inputStyle = QString(R"(
        QLineEdit {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            border-radius: 8px;
            padding: 10px 12px;
            font-size: 13px;
            selection-background-color: #0D9B83;
        }
    
        QLineEdit:hover {
            border: 1px solid #0D9B83;
        }
    
        QLineEdit:focus {
            border: 1px solid #0D9B83;
            background-color: #ffffff;
        }
    
        QLineEdit:disabled {
            background-color: #f5f6f7;
            color: #8996a3;
        }
    
    
        QComboBox {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            border-radius: 8px;
            padding: 10px 12px;
            font-size: 13px;
        }
    
        QComboBox:hover {
            border: 1px solid #0D9B83;
        }
    
        QComboBox:focus {
            border: 1px solid #0D9B83;
        }
    
        QComboBox::drop-down {
            border: none;
            width: 24px;
        }
    
        QComboBox QAbstractItemView {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            selection-background-color: rgba(73, 179, 162, 0.1);
            selection-color: #121736;
            outline: none;
            padding: 4px;
        }
    
        QSpinBox {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            border-radius: 8px;
            padding: 10px 12px;
            font-size: 13px;
        }
    
        QSpinBox:hover {
            border: 1px solid #0D9B83;
        }
    
        QSpinBox:focus {
            border: 1px solid #0D9B83;
        }
    
        QSpinBox::up-button,
        QSpinBox::down-button {
            background-color: #f5f6f7;
            border: none;
            width: 24px;
            border-radius: 4px;
            margin: 2px;
        }
    
        QSpinBox::up-button:hover,
        QSpinBox::down-button:hover {
            background-color: rgba(73, 179, 162, 0.1);
        }

        QDateEdit,
        QTimeEdit {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            border-radius: 8px;
            padding: 10px 12px;
            font-size: 13px;
            selection-background-color: #0D9B83;
        }

        QDateEdit:hover,
        QTimeEdit:hover {
            border: 1px solid #0D9B83;
        }

        QDateEdit:focus,
        QTimeEdit:focus {
            border: 1px solid #0D9B83;
            background-color: #ffffff;
        }

        QDateEdit:disabled,
        QTimeEdit:disabled {
            background-color: #f5f6f7;
            color: #8996a3;
        }

        QDateEdit::drop-down,
        QTimeEdit::drop-down {
            border: none;
            width: 28px;
            subcontrol-origin: padding;
            subcontrol-position: top right;
        }

        QTimeEdit::up-button,
        QTimeEdit::down-button {
            background-color: #f5f6f7;
            border: none;
            width: 24px;
            border-radius: 4px;
            margin: 2px;
        }

        QDateEdit::down-arrow,
        QTimeEdit::down-arrow {
            width: 10px;
            height: 10px;
        }

        QDateEdit QAbstractItemView,
        QTimeEdit QAbstractItemView {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            selection-background-color: rgba(73, 179, 162, 0.1);
            selection-color: #121736;
        }

        QCalendarWidget QWidget {
            background-color: #ffffff;
            color: #121736;
            padding: 8px;
        }

        QCalendarWidget QToolButton {
            background-color: #ffffff;
            color: #121736;
            border: none;
            border-radius: 6px;
            padding: 6px;
            font-size: 13px;
        }

        QCalendarWidget QToolButton:hover {
            background-color: rgba(73, 179, 162, 0.1);
        }

        QCalendarWidget QMenu {
            background-color: #ffffff;
            color: #121736;
        }

        QCalendarWidget QSpinBox {
            background-color: #ffffff;
            color: #121736;
            border: 1px solid #e0e6eb;
            border-radius: 4px;
            padding: 4px;
        }

        QCalendarWidget QAbstractItemView {
            background-color: #ffffff;
            color: #121736;
            selection-background-color: #0D9B83;
            selection-color: #ffffff;
            outline: none;
        }
    )");
    ui->patientsSearchInput->setStyleSheet(inputStyle);
    ui->patientsSearchMethodCombo->setStyleSheet(inputStyle);
    ui->patientsSortMethodCombo->setStyleSheet(inputStyle);
    ui->patientNameInput->setStyleSheet(inputStyle);
    ui->patientAgeInput->setStyleSheet(inputStyle);
    ui->patientContactInput->setStyleSheet(inputStyle);
    ui->patientCategoryCombo->setStyleSheet(inputStyle);

    ui->appointmentPatientInput->setStyleSheet(inputStyle);
    ui->appointmentReasonInput->setStyleSheet(inputStyle);
    ui->appointmentDateInput->setStyleSheet(inputStyle);
    ui->appointmentTimeInput->setStyleSheet(inputStyle);

    ui->reportTypeCombo->setStyleSheet(inputStyle);

    //--link viewAllAppointments button to the appointments tab
    connect(ui->viewAllAppointmentsButton, &QPushButton::clicked, this, [this]() {
        ui->mainTabWidget->setCurrentWidget(ui->appointmentsTab);
    });

    //--link the register patient button
    connect(ui->registerPatientButton, &QPushButton::clicked, this, &MainWindow::registerPatient);

    //--link the clear patient form button
    connect(ui->clearPatientFormButton, &QPushButton::clicked, this, &MainWindow::clearPatientForm);

    //--link automatic patient search on input value changed, with debounce.
    QTimer *patientSearchTimer = new QTimer(this);
    patientSearchTimer->setSingleShot(true);
    connect(ui->patientsSearchInput, &QLineEdit::textChanged, this, [patientSearchTimer]() {
        patientSearchTimer->start(300);
    });
    connect(patientSearchTimer, &QTimer::timeout, this, &MainWindow::applyPatientFiltersAndSort);

    //--link the search method combo box for changed value
    connect(ui->patientsSearchMethodCombo, &QComboBox::currentIndexChanged, this, [this](int) {
        applyPatientFiltersAndSort();
    });

    //--link the sort method combo box for changed value
    connect(ui->patientsSortMethodCombo, &QComboBox::currentIndexChanged, this, [this](int) {
        applyPatientFiltersAndSort();
    });

    //--link button to create patient appointment
    connect(ui->createPatientAppointmentButton,
            &QPushButton::clicked,
            this,
            &MainWindow::preparePatientAppointment);

    //--link button to add selected patient to queue
    connect(ui->addToQueueButton,
            &QPushButton::clicked,
            this,
            &MainWindow::addSelectedPatientToQueue);

    //--link button in dashboard overview to remove the next patient from the waiting queue
    connect(ui->nextPatientButton, &QPushButton::clicked, this, [this]() {
        SCAPMS::PatientRecord *patient = database.dequeuePatient();

        if (!patient) {
            QMessageBox::information(this,
                                     "Waiting Queue",
                                     "There are no patients currently waiting.");
            return;
        }

        refreshOverviewTables();
        ui->waitingPatientsValue->setText(QString::number(database.getWaitingCount()));

        QMessageBox::information(this,
                                 "Next Patient",
                                 patient->getName() + " is now off the queue.");
    });

    //--link button to create new appointment schedule
    connect(ui->scheduleAppointmentButton,
            &QPushButton::clicked,
            this,
            &MainWindow::scheduleAppointment);

    //--link the clear appointment form button
    connect(ui->clearAppointmentFormButton,
            &QPushButton::clicked,
            this,
            &MainWindow::clearAppointmentForm);

    //--link button to cancel appointment
    connect(ui->cancelAppointmentButton,
            &QPushButton::clicked,
            this,
            &MainWindow::cancelAppointment);

    //--link button to generate secific reports
    connect(ui->generateReportButton, &QPushButton::clicked, this, &MainWindow::generateReport);

    //--link button for undoing last action for admin
    connect(ui->undoLastActionButton, &QPushButton::clicked, this, &MainWindow::undoLastAdminAction);

    //--link button for clearing all admin action history
    connect(ui->clearAdminHistoryButton,
            &QPushButton::clicked,
            this,
            &MainWindow::clearAdminHistory);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupOverviewTables()
{
    //--waiting Queue Table
    ui->waitingQueueTable->setColumnCount(4);

    ui->waitingQueueTable->setHorizontalHeaderLabels(
        {"Patient ID", "Patient Name", "Category", "Priority"});

    ui->waitingQueueTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->waitingQueueTable->verticalHeader()->setVisible(false);
    ui->waitingQueueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->waitingQueueTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->waitingQueueTable->setAlternatingRowColors(true);

    QHeaderView *waitingHeader = ui->waitingQueueTable->horizontalHeader();

    waitingHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    waitingHeader->setSectionResizeMode(1, QHeaderView::Stretch);

    //--upcoming Appointments Table
    ui->upcomingAppointmentsTable->setColumnCount(4);

    ui->upcomingAppointmentsTable->setHorizontalHeaderLabels(
        {"Patient", "Reason", "Date & Time", "Status"});

    ui->upcomingAppointmentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->upcomingAppointmentsTable->verticalHeader()->setVisible(false);
    ui->upcomingAppointmentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->upcomingAppointmentsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->upcomingAppointmentsTable->setAlternatingRowColors(true);

    QHeaderView *upcomingHeader = ui->upcomingAppointmentsTable->horizontalHeader();

    upcomingHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    upcomingHeader->setSectionResizeMode(0, QHeaderView::Stretch);
    upcomingHeader->setSectionResizeMode(1, QHeaderView::Stretch);
}

void MainWindow::refreshOverviewTables()
{
    //--patients waiting queue table
    ui->waitingQueueTable->setRowCount(0);

    std::vector<SCAPMS::PatientRecord *> waitingPatients = database.getWaitingPatients();

    for (SCAPMS::PatientRecord *patient : waitingPatients) {
        int row = ui->waitingQueueTable->rowCount();

        ui->waitingQueueTable->insertRow(row);

        QString priorityText = patient->getPriority() == 1   ? "High"
                               : patient->getPriority() == 2 ? "Medium"
                                                             : "Normal";

        ui->waitingQueueTable->setItem(row, 0, new QTableWidgetItem(patient->getId()));

        ui->waitingQueueTable->setItem(row, 1, new QTableWidgetItem(patient->getName()));

        ui->waitingQueueTable->setItem(row, 2, new QTableWidgetItem(patient->getPatientType()));

        ui->waitingQueueTable->setItem(row, 3, new QTableWidgetItem(priorityText));
    }

    //--upcoming appointments table
    std::vector<SCAPMS::Appointment *> upcomingAppointments;

    QDateTime now = QDateTime::currentDateTime();

    for (const auto &appointment : database.getAppointments()) {
        if (appointment->getStatus() != "Scheduled") {
            continue;
        }

        QDateTime appointmentDate = appointment->getDateTime();

        //--only appointments that haven't passed.
        if (appointmentDate.isValid() && appointmentDate >= now) {
            upcomingAppointments.push_back(appointment.get());
        }
    }

    //--sort appointments by scheduled date/time.
    std::sort(upcomingAppointments.begin(),
              upcomingAppointments.end(),
              [](SCAPMS::Appointment *a, SCAPMS::Appointment *b) {
                  return a->getDateTime() < b->getDateTime();
              });

    //-populate the table.
    ui->upcomingAppointmentsTable->setRowCount(0);

    for (SCAPMS::Appointment *appointment : upcomingAppointments) {
        int row = ui->upcomingAppointmentsTable->rowCount();

        ui->upcomingAppointmentsTable->insertRow(row);

        ui->upcomingAppointmentsTable
            ->setItem(row, 0, new QTableWidgetItem(appointment->getPatient()->getName()));

        ui->upcomingAppointmentsTable->setItem(row,
                                               1,
                                               new QTableWidgetItem(appointment->getReason()));

        ui->upcomingAppointmentsTable->setItem(row,
                                               2,
                                               new QTableWidgetItem(
                                                   appointment->getDateTime().toString(
                                                       "dd MMM yyyy, hh:mm AP")));

        ui->upcomingAppointmentsTable->setItem(row,
                                               3,
                                               new QTableWidgetItem(appointment->getStatus()));
    }

    //--update total patients count
    ui->totalPatientsValue->setText(QString::number(database.getPatientCount()));

    //--update waiting patients statistic.
    ui->waitingPatientsValue->setText(QString::number(database.getWaitingCount()));

    //--update today's appointments statistic
    int todayCount = 0;
    for (const auto &item : database.getAppointments()) {
        if (item->getStatus() != "Cancelled" && item->getDateTime().isValid()
            && item->getDateTime().date() == QDate::currentDate()) {
            todayCount++;
        }
    }
    ui->todayAppointmentsValue->setText(QString::number(todayCount));

    //--update emergency patients count
    int emergencyCount = 0;
    for (const auto &patient : database.getPatients()) {
        if (patient->getPatientType() == "Emergency") {
            emergencyCount++;
        }
    }
    ui->emergencyPatientsValue->setText(QString::number(emergencyCount));
}

void MainWindow::setupPatientsTable()
{
    ui->patientsTable->setColumnCount(5);

    ui->patientsTable->setHorizontalHeaderLabels(
        {"Patient ID", "Full Name", "Age", "Category", "Contact"});

    ui->patientsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->patientsTable->verticalHeader()->setVisible(false);

    ui->patientsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->patientsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->patientsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->patientsTable->setAlternatingRowColors(true);

    QHeaderView *header = ui->patientsTable->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::ResizeToContents);

    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(4, QHeaderView::Stretch);
}

void MainWindow::refreshPatientsTable()
{
    ui->patientsTable->setRowCount(0);

    for (SCAPMS::PatientRecord *patient : displayedPatients) {
        int row = ui->patientsTable->rowCount();

        ui->patientsTable->insertRow(row);

        ui->patientsTable->setItem(row, 0, new QTableWidgetItem(patient->getId()));

        ui->patientsTable->setItem(row, 1, new QTableWidgetItem(patient->getName()));

        ui->patientsTable->setItem(row, 2, new QTableWidgetItem(QString::number(patient->getAge())));

        ui->patientsTable->setItem(row, 3, new QTableWidgetItem(patient->getPatientType()));

        ui->patientsTable->setItem(row, 4, new QTableWidgetItem(patient->getContact()));
    }
}

void MainWindow::setupAppointmentsTable()
{
    ui->appointmentsTable->setColumnCount(6);

    ui->appointmentsTable->setHorizontalHeaderLabels(
        {"ID", "Patient", "Patient ID", "Reason", "Date & Time", "Status"});

    QHeaderView *header = ui->appointmentsTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    ui->appointmentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->appointmentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->appointmentsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->appointmentsTable->setAlternatingRowColors(true);
    ui->appointmentsTable->verticalHeader()->setVisible(false);

    ui->appointmentsTable->setShowGrid(false);
    ui->appointmentsTable->setWordWrap(false);

    QHeaderView *appointmentHeader = ui->appointmentsTable->horizontalHeader();

    appointmentHeader->setSectionResizeMode(QHeaderView::ResizeToContents);

    appointmentHeader->setSectionResizeMode(1, QHeaderView::Stretch);
    appointmentHeader->setSectionResizeMode(3, QHeaderView::Stretch);
}

void MainWindow::refreshAppointmentsTable()
{
    ui->appointmentsTable->setRowCount(0);

    for (const auto &appointment : database.getAppointments()) {
        SCAPMS::PatientRecord *patient = appointment->getPatient();

        if (!patient)
            continue;

        int row = ui->appointmentsTable->rowCount();

        ui->appointmentsTable->insertRow(row);

        QString dateTimeText = appointment->getDateTime().isValid()
                                   ? appointment->getDateTime().toString("dd MMM yyyy, hh:mm AP")
                                   : "Not scheduled";

        ui->appointmentsTable->setItem(row, 0, new QTableWidgetItem(appointment->getId()));

        ui->appointmentsTable->setItem(row, 1, new QTableWidgetItem(patient->getName()));

        ui->appointmentsTable->setItem(row, 2, new QTableWidgetItem(patient->getId()));

        ui->appointmentsTable->setItem(row, 3, new QTableWidgetItem(appointment->getReason()));

        ui->appointmentsTable->setItem(row, 4, new QTableWidgetItem(dateTimeText));

        ui->appointmentsTable->setItem(row, 5, new QTableWidgetItem(appointment->getStatus()));
    }
}

void MainWindow::registerPatient()
{
    //--get form values
    QString name = ui->patientNameInput->text().trimmed();
    int age = ui->patientAgeInput->value();
    QString contact = ui->patientContactInput->text().trimmed();
    QString category = ui->patientCategoryCombo->currentData().toString();

    //--perform basic validation
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please enter the patient's full name.");
        return;
    }

    if (contact.isEmpty()) {
        QMessageBox::warning(this,
                             "Registration Error",
                             "Please enter the patient's contact information.");
        return;
    }

    if (category.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please select a patient category.");
        return;
    }

    try {
        //--try to auto-generate patient ID
        QString patientId = database.generatePatientId();

        //--create the appropriate patient object
        std::unique_ptr<SCAPMS::PatientRecord> newPatient;

        if (category == "General") {
            newPatient = std::make_unique<SCAPMS::GeneralPatient>(patientId, name, age, contact);

        } else if (category == "Emergency") {
            newPatient = std::make_unique<SCAPMS::EmergencyPatient>(patientId, name, age, contact);

        } else if (category == "Follow-up") {
            newPatient = std::make_unique<SCAPMS::FollowUpPatient>(patientId, name, age, contact);

        } else {
            QMessageBox::warning(this, "Registration Error", "Invalid patient category selected.");
            return;
        }

        //--add patient to database
        database.addPatient(std::move(newPatient));
        database.recordAdminAction(QString("Patient %1 registered").arg(patientId),
                                   false,
                                   "patient_registered",
                                   patientId);

        //--refresh the interface
        applyPatientFiltersAndSort();
        refreshOverviewTables();
        refreshAdminTable();
        refreshAdminStatistics();

        clearPatientForm();
        saveApplicationData();

        QMessageBox::information(this,
                                 "Registration Successful",
                                 "New patient registered successfully!\n\n"
                                 "Name: "
                                     + name + "\nPatient ID: " + patientId);

    } catch (const std::exception &error) {
        QMessageBox::critical(this, "Registration Failed", QString::fromUtf8(error.what()));
    }
}

void MainWindow::clearPatientForm()
{
    ui->patientNameInput->clear();
    ui->patientAgeInput->setValue(18);
    ui->patientContactInput->clear();
    ui->patientCategoryCombo->setCurrentIndex(0);
}

void MainWindow::applyPatientFiltersAndSort()
{
    displayedPatients.clear();

    QString searchText = ui->patientsSearchInput->text().trimmed();

    QString searchMethod = ui->patientsSearchMethodCombo->currentData().toString();

    //--apply search filtering.
    if (searchText.isEmpty()) {
        //--if no search query, display every patient.
        for (const auto &patient : database.getPatients()) {
            displayedPatients.push_back(patient.get());
        }
    } else if (searchMethod == "linear_id") {
        displayedPatients = database.linearSearchPatientById(searchText);
    } else if (searchMethod == "binary_name") {
        displayedPatients = database.binarySearchPatientByName(searchText);
    } else if (searchMethod == "recursive_name") {
        displayedPatients = database.recursiveSearchPatientByName(searchText);
    }

    //--apply sorting to the filtered results.
    QString sortMethod = ui->patientsSortMethodCombo->currentData().toString();

    if (sortMethod == "name") {
        database.selectionSortPatientByName(displayedPatients);
    } else if (sortMethod == "age") {
        database.insertionSortPatientByAge(displayedPatients);
    }

    //--display the final collection.
    refreshPatientsTable();
}

void MainWindow::searchPatients()
{
    applyPatientFiltersAndSort();
}

void MainWindow::sortPatients()
{
    applyPatientFiltersAndSort();
}

void MainWindow::addSelectedPatientToQueue()
{
    //--check whether a patient row is selected.
    int selectedRow = ui->patientsTable->currentRow();

    if (selectedRow < 0) {
        QMessageBox::warning(this,
                             "Waiting Queue",
                             "Please select a patient from the records table first.");
        return;
    }

    //--get the selected patient's ID.
    QTableWidgetItem *idItem = ui->patientsTable->item(selectedRow, 0);

    if (!idItem) {
        QMessageBox::warning(this,
                             "Waiting Queue",
                             "Unable to retrieve the selected patient's information.");
        return;
    }
    QString patientId = idItem->text();

    //--retrieve the actual patient record from the database.
    SCAPMS::PatientRecord *patient = database.findPatientById(patientId);

    if (!patient) {
        QMessageBox::warning(this, "Waiting Queue", "The selected patient could not be found.");
        return;
    }

    //--check if the patient is already waiting.
    std::vector<SCAPMS::PatientRecord *> waitingPatients = database.getWaitingPatients();

    for (SCAPMS::PatientRecord *waitingPatient : waitingPatients) {
        if (waitingPatient->getId() == patientId) {
            QMessageBox::information(this,
                                     "Waiting Queue",
                                     patient->getName() + " is already in the waiting queue.");
            return;
        }
    }

    //--add the patient to the queue.
    database.enqueuePatient(patient);

    //--refresh dashboard information.
    refreshOverviewTables();

    saveApplicationData();

    QMessageBox::information(this,
                             "Waiting Queue",
                             patient->getName()
                                 + " has been successfully added to the waiting queue.");
}

void MainWindow::preparePatientAppointment()
{
    //--get the currently selected patient row.
    int selectedRow = ui->patientsTable->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this,
                             "Create Appointment",
                             "Please select a patient from the records table first.");
        return;
    }

    //--get the patient's ID.
    QTableWidgetItem *idItem = ui->patientsTable->item(selectedRow, 0);
    if (!idItem) {
        QMessageBox::warning(this,
                             "Create Appointment",
                             "Unable to retrieve the selected patient's information.");
        return;
    }

    //--retrieve the actual patient record.
    SCAPMS::PatientRecord *patient = database.findPatientById(idItem->text());
    if (!patient) {
        QMessageBox::warning(this, "Create Appointment", "The selected patient could not be found.");
        return;
    }

    //--store the selected patient.
    selectedAppointmentPatient = patient;

    //--populate the appointment form.
    ui->appointmentPatientInput->setText(patient->getName() + " (" + patient->getId() + ")");

    //--navigate to the appointments tab.
    ui->mainTabWidget->setCurrentWidget(ui->appointmentsTab);

    //--automatically focus the appointment reason input.
    ui->appointmentReasonInput->setFocus();
}

void MainWindow::scheduleAppointment()
{
    //--ensure a patient has been selected
    if (!selectedAppointmentPatient) {
        QMessageBox::warning(this,
                             "Schedule Appointment",
                             "Please select a patient from the Patients Management tab first.");
        return;
    }

    QString reason = ui->appointmentReasonInput->text().trimmed();
    if (reason.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter the reason for the appointment.");
        ui->appointmentReasonInput->setFocus();
        return;
    }

    //--combine selected date and time
    QDateTime appointmentDateTime(ui->appointmentDateInput->date(),
                                  ui->appointmentTimeInput->time());

    try {
        //--create appointment
        auto appointment = std::make_unique<SCAPMS::Appointment>(selectedAppointmentPatient, reason);

        //--generate unique appointment ID
        appointment->setId(database.generateAppointmentId());

        //--schedule appointment
        if (!appointment->schedule(appointmentDateTime)) {
            QMessageBox::warning(this,
                                 "Invalid Appointment Time",
                                 "The selected appointment date and time must be in the future.");
            return;
        }

        //--save appointment in database
        if (!database.addAppointment(std::move(appointment))) {
            QMessageBox::warning(this, "Appointment Failed", "Unable to save this appointment.");
            return;
        }

        QString appointmentId = database.getAppointments().back()->getId();
        database.recordAdminAction(QString("Appointment %1 scheduled").arg(appointmentId),
                                   true,
                                   "appointment_scheduled",
                                   appointmentId);

        //--refresh appointment displays
        refreshAppointmentsTable();
        refreshOverviewTables();
        refreshAdminTable();
        refreshAdminStatistics();

        saveApplicationData();

        QMessageBox::information(this,
                                 "Appointment Scheduled",
                                 "Appointment successfully scheduled!\n\n"
                                 "Appointment ID: "
                                     + appointmentId
                                     + "\n"
                                       "Patient: "
                                     + selectedAppointmentPatient->getName());

        clearAppointmentForm();
    } catch (const std::exception &e) {
        QMessageBox::critical(this,
                              "Appointment Error",
                              QString("An error occurred:\n%1").arg(e.what()));
    }
}

void MainWindow::clearAppointmentForm()
{
    selectedAppointmentPatient = nullptr;

    ui->appointmentPatientInput->clear();
    ui->appointmentReasonInput->clear();

    ui->appointmentDateInput->setDate(QDate::currentDate());
    ui->appointmentTimeInput->setTime(QTime::currentTime());

    ui->appointmentReasonInput->clearFocus();
}

void MainWindow::cancelAppointment()
{
    int selectedRow = ui->appointmentsTable->currentRow();

    //--ensure an appointment is selected
    if (selectedRow < 0) {
        QMessageBox::warning(this,
                             "Cancel Appointment",
                             "Please select an appointment from the table first.");
        return;
    }

    //--get appointment ID
    QTableWidgetItem *idItem = ui->appointmentsTable->item(selectedRow, 0);
    if (!idItem) {
        QMessageBox::warning(this,
                             "Cancel Appointment",
                             "Unable to retrieve the selected appointment.");
        return;
    }
    QString appointmentId = idItem->text();

    //--retriebe the actual appointment
    SCAPMS::Appointment *selectedAppointment = nullptr;

    for (const auto &appointment : database.getAppointments()) {
        if (appointment->getId() == appointmentId) {
            selectedAppointment = appointment.get();
            break;
        }
    }

    if (!selectedAppointment) {
        QMessageBox::warning(this,
                             "Appointment Not Found",
                             "The selected appointment could not be found.");
        return;
    }

    //--prevent repeated cancellation
    if (selectedAppointment->getStatus() == "Cancelled") {
        QMessageBox::information(this,
                                 "Appointment Already Cancelled",
                                 "This appointment has already been cancelled.");
        return;
    }

    //--trigger cancellation confirm dialogue
    QMessageBox::StandardButton confirmation = QMessageBox::question(
        this,
        "Confirm Cancellation",
        QString("Are you sure you want to cancel appointment %1?").arg(appointmentId),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (confirmation != QMessageBox::Yes)
        return;

    //--cancel appointment
    if (!selectedAppointment->cancel()) {
        QMessageBox::warning(this, "Cancellation Failed", "Unable to cancel this appointment.");
        return;
    }
    database.recordAdminAction(QString("Appointment %1 cancelled").arg(appointmentId),
                               false,
                               "appointment_cancelled",
                               appointmentId);

    //--refresh tables
    refreshAppointmentsTable();
    refreshOverviewTables();
    refreshAdminTable();
    refreshAdminStatistics();

    saveApplicationData();

    //--update today's appointments count
    int todayCount = 0;
    for (const auto &appointment : database.getAppointments()) {
        if (appointment->getStatus() != "Cancelled" && appointment->getDateTime().isValid()
            && appointment->getDateTime().date() == QDate::currentDate()) {
            todayCount++;
        }
    }
    ui->todayAppointmentsValue->setText(QString::number(todayCount));

    QMessageBox::information(this,
                             "Appointment Cancelled",
                             QString("Appointment %1 has been successfully cancelled.")
                                 .arg(appointmentId));
}

void MainWindow::setupReportsTable()
{
    ui->reportsTable->setColumnCount(1);

    ui->reportsTable->setHorizontalHeaderLabels({"Report Information"});

    ui->reportsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->reportsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->reportsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->reportsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->reportsTable->setAlternatingRowColors(true);
    ui->reportsTable->verticalHeader()->setVisible(false);
    ui->reportsTable->setShowGrid(false);

    ui->reportDescriptionLabel->setText(
        "Select a report and click Generate Report to view the results.");

    ui->reportSummaryLabel->clear();

    QHeaderView *reportHeader = ui->reportsTable->horizontalHeader();

    reportHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    reportHeader->setStretchLastSection(true);
}

void MainWindow::generateReport()
{
    QString reportType = ui->reportTypeCombo->currentData().toString();

    ui->reportsTable->clear();
    ui->reportsTable->setRowCount(0);

    //--helper for configuring table columns
    auto configureTable = [this](const QStringList &headers) {
        ui->reportsTable->setColumnCount(headers.size());
        ui->reportsTable->setHorizontalHeaderLabels(headers);

        ui->reportsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    };

    //--helper for adding a row
    auto addRow = [this](const QStringList &values) {
        int row = ui->reportsTable->rowCount();

        ui->reportsTable->insertRow(row);

        for (int column = 0; column < values.size(); column++) {
            ui->reportsTable->setItem(row, column, new QTableWidgetItem(values[column]));
        }
    };

    //--helper for displaying empty reports
    auto showEmptyMessage = [this](const QString &message) {
        ui->reportsTable->setRowCount(1);
        ui->reportsTable->setSpan(0, 0, 1, ui->reportsTable->columnCount());

        ui->reportsTable->setItem(0, 0, new QTableWidgetItem(message));
    };

    //--REPORT 1: frequent patients
    if (reportType == "frequent_patients") {
        ui->reportDescriptionLabel->setText(
            "Patients ranked according to their number of active appointments.");

        configureTable({"Rank", "Patient ID", "Patient Name", "Appointments"});

        std::vector<std::pair<SCAPMS::PatientRecord *, int>> patientCounts;

        //--count appointments for each patient
        for (const auto &appointment : database.getAppointments()) {
            if (appointment->getStatus() == "Cancelled")
                continue;

            SCAPMS::PatientRecord *patient = appointment->getPatient();

            if (!patient)
                continue;

            auto it = std::find_if(patientCounts.begin(),
                                   patientCounts.end(),
                                   [patient](const auto &entry) {
                                       return entry.first->getId() == patient->getId();
                                   });

            if (it != patientCounts.end()) {
                it->second++;
            } else {
                patientCounts.push_back({patient, 1});
            }
        }

        //--sort by appointment count (descending)
        std::sort(patientCounts.begin(), patientCounts.end(), [](const auto &a, const auto &b) {
            if (a.second != b.second)
                return a.second > b.second;

            return a.first->getName().compare(b.first->getName(), Qt::CaseInsensitive) < 0;
        });

        int rank = 1;

        for (const auto &entry : patientCounts) {
            addRow({QString::number(rank++),
                    entry.first->getId(),
                    entry.first->getName(),
                    QString::number(entry.second)});
        }

        if (patientCounts.empty()) {
            showEmptyMessage("No appointment records available.");
        }

        ui->reportSummaryLabel->setText(
            QString("Total patients with active appointments: %1").arg(patientCounts.size()));
    }

    //--REPORT 2: pending appointments
    else if (reportType == "pending_appointments") {
        ui->reportDescriptionLabel->setText("Displays appointments that are awaiting scheduling or "
                                            "have been scheduled but not cancelled.");

        configureTable({"Appointment ID", "Patient", "Date & Time", "Status"});

        int pendingCount = 0;

        for (const auto &appointment : database.getAppointments()) {
            QString status = appointment->getStatus();

            if (status != "Pending" && status != "Scheduled")
                continue;

            SCAPMS::PatientRecord *patient = appointment->getPatient();

            if (!patient)
                continue;

            QString dateTimeText = appointment->getDateTime().isValid()
                                       ? appointment->getDateTime().toString(
                                             "dd MMM yyyy, hh:mm AP")
                                       : "Not scheduled";

            addRow({appointment->getId(), patient->getName(), dateTimeText, status});

            pendingCount++;
        }

        if (pendingCount == 0) {
            showEmptyMessage("There are no outstanding appointments.");
        }

        ui->reportSummaryLabel->setText(
            QString("Total outstanding appointments: %1").arg(pendingCount));
    }

    //--REPORT 3: patient category distribution
    else if (reportType == "category_distribution") {
        ui->reportDescriptionLabel->setText(
            "Distribution of registered patients across the clinic's "
            "three patient categories.");

        configureTable({"Patient Category", "Patient Count", "Percentage"});

        int generalCount = 0;
        int emergencyCount = 0;
        int followUpCount = 0;

        for (const auto &patient : database.getPatients()) {
            QString category = patient->getPatientType();

            if (category == "General")
                generalCount++;

            else if (category == "Emergency")
                emergencyCount++;

            else if (category == "Follow-up")
                followUpCount++;
        }

        int totalPatients = database.getPatientCount();

        auto calculatePercentage = [totalPatients](int count) {
            if (totalPatients == 0)
                return QString("0.00%");

            double percentage = (static_cast<double>(count) / totalPatients) * 100.0;

            return QString("%1%").arg(percentage, 0, 'f', 2);
        };

        addRow(
            {"General Patients", QString::number(generalCount), calculatePercentage(generalCount)});

        addRow({"Emergency Patients",
                QString::number(emergencyCount),
                calculatePercentage(emergencyCount)});

        addRow({"Follow-up Patients",
                QString::number(followUpCount),
                calculatePercentage(followUpCount)});

        ui->reportSummaryLabel->setText(QString("Total registered patients: %1").arg(totalPatients));
    }

    //--REPORT 4: daily appointment summary
    else if (reportType == "daily_summary") {
        QDate today = QDate::currentDate();

        ui->reportDescriptionLabel->setText(
            QString("Appointment activity for %1.").arg(today.toString("dddd, dd MMMM yyyy")));

        configureTable({"Appointment Metric", "Count", "Description"});

        int totalToday = 0;
        int scheduledToday = 0;
        int pendingToday = 0;
        int cancelledToday = 0;

        for (const auto &appointment : database.getAppointments()) {
            QDateTime dateTime = appointment->getDateTime();

            if (!dateTime.isValid() || dateTime.date() != today)
                continue;

            totalToday++;

            QString status = appointment->getStatus();

            if (status == "Scheduled")
                scheduledToday++;

            else if (status == "Pending")
                pendingToday++;

            else if (status == "Cancelled")
                cancelledToday++;
        }

        addRow({"Total Appointments",
                QString::number(totalToday),
                "All appointments scheduled for today"});

        addRow({"Scheduled Appointments",
                QString::number(scheduledToday),
                "Appointments confirmed for today"});

        addRow({"Pending Appointments",
                QString::number(pendingToday),
                "Appointments awaiting scheduling"});

        addRow({"Cancelled Appointments",
                QString::number(cancelledToday),
                "Appointments cancelled for today"});

        ui->reportSummaryLabel->setText(
            QString("Total appointments recorded for today: %1").arg(totalToday));
    }
}

void MainWindow::applyRolePermissions()
{
    QString userRole = property("userRole").toString();

    int adminTabIndex = ui->mainTabWidget->indexOf(ui->adminTab);

    if (adminTabIndex >= 0) {
        ui->mainTabWidget->setTabVisible(adminTabIndex, userRole == "Admin");
    }
}

void MainWindow::setupAdminTable()
{
    ui->adminHistoryTable->setColumnCount(4);

    ui->adminHistoryTable->setHorizontalHeaderLabels(
        {"#", "Administrative Action", "Date & Time", "Status"});

    ui->adminHistoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->adminHistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->adminHistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->adminHistoryTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->adminHistoryTable->setAlternatingRowColors(true);
    ui->adminHistoryTable->verticalHeader()->setVisible(false);
    ui->adminHistoryTable->setShowGrid(false);
    ui->adminHistoryTable->setWordWrap(false);

    QHeaderView *adminHeader = ui->adminHistoryTable->horizontalHeader();

    adminHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    adminHeader->setSectionResizeMode(1, QHeaderView::Stretch);
}

void MainWindow::refreshAdminTable()
{
    ui->adminHistoryTable->setRowCount(0);

    const auto &history = database.getAdminHistory();

    //--display newest actions first
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        int row = ui->adminHistoryTable->rowCount();

        ui->adminHistoryTable->insertRow(row);

        ui->adminHistoryTable->setItem(row, 0, new QTableWidgetItem(QString::number(it->id)));

        ui->adminHistoryTable->setItem(row, 1, new QTableWidgetItem(it->description));

        ui->adminHistoryTable->setItem(row,
                                       2,
                                       new QTableWidgetItem(
                                           it->timestamp.toString("dd MMM yyyy, hh:mm AP")));

        ui->adminHistoryTable->setItem(row, 3, new QTableWidgetItem(it->status));
    }
}

void MainWindow::refreshAdminStatistics()
{
    ui->totalAdminActionsValue->setText(QString::number(database.getTotalAdminActions()));

    ui->reversibleActionsValue->setText(QString::number(database.getReversibleAdminActions()));

    QString lastAction = database.getLastAdminAction();

    //--truncate last action to keep the card readable
    if (lastAction.length() > 30)
        lastAction = lastAction.left(27) + "...";

    ui->lastActionValue->setText(lastAction);
    ui->undoLastActionButton->setEnabled(database.getReversibleAdminActions() > 0);
}

void MainWindow::undoLastAdminAction()
{
    //--additional role protection
    if (property("userRole").toString() != "Admin") {
        QMessageBox::warning(this,
                             "Access Denied",
                             "Only administrators can perform this operation.");
        return;
    }

    if (database.getReversibleAdminActions() == 0) {
        QMessageBox::information(this,
                                 "Nothing to Undo",
                                 "There are no reversible administrative operations.");
        refreshAdminTable();
        refreshAdminStatistics();
        return;
    }

    QMessageBox::StandardButton confirmation = QMessageBox::question(
        this,
        "Confirm Undo",
        "Are you sure you want to reverse the most recent reversible operation?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (confirmation != QMessageBox::Yes)
        return;

    QString undoneAction;

    if (!database.undoLastAction(undoneAction)) {
        QMessageBox::warning(this, "Undo Failed", "The operation could not be reversed.");

        refreshAdminTable();
        refreshAdminStatistics();
        return;
    }

    //--record the undo operation itself
    database.recordAdminAction(QString("Undo performed: %1").arg(undoneAction), false, "undo", "");

    //--refresh affected displays
    refreshAppointmentsTable();
    refreshOverviewTables();

    //--update today's appointment statistic
    int todayCount = 0;

    for (const auto &appointment : database.getAppointments()) {
        if (appointment->getStatus() != "Cancelled" && appointment->getDateTime().isValid()
            && appointment->getDateTime().date() == QDate::currentDate()) {
            todayCount++;
        }
    }

    ui->todayAppointmentsValue->setText(QString::number(todayCount));

    refreshAdminTable();
    refreshAdminStatistics();
    saveApplicationData();

    QMessageBox::information(this,
                             "Operation Reversed",
                             QString("The following operation was successfully reversed:\n\n%1")
                                 .arg(undoneAction));
}

void MainWindow::clearAdminHistory()
{
    if (property("userRole").toString() != "Admin") {
        QMessageBox::warning(this,
                             "Access Denied",
                             "Only administrators can perform this operation.");
        return;
    }

    if (database.getTotalAdminActions() == 0) {
        QMessageBox::information(this,
                                 "Empty History",
                                 "There are no administrative records to clear.");
        return;
    }

    QMessageBox::StandardButton confirmation
        = QMessageBox::warning(this,
                               "Clear Administrative History",
                               "Are you sure you want to clear all administrative history?\n\n"
                               "This action cannot be undone. Patient and appointment records "
                               "will remain unaffected.",
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No);

    if (confirmation != QMessageBox::Yes)
        return;

    database.clearAdminHistory();

    refreshAdminTable();
    refreshAdminStatistics();
    saveApplicationData();

    QMessageBox::information(this,
                             "History Cleared",
                             "Administrative history has been successfully cleared.");
}

void MainWindow::saveApplicationData()
{
    if (!database.saveDataToJson(dataFilePath)) {
        QMessageBox::warning(this,
                             "Data Saving Error",
                             "Unable to save application data.\n"
                             "Please check the application's data directory.");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveApplicationData();

    event->accept();
}