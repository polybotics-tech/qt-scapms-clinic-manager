#include "MainWindow.h"
#include "gui/ui_MainWindow.h"

#include "models/EmergencyPatient.h"
#include "models/FollowUpPatient.h"
#include "models/GeneralPatient.h"

#include <QAbstractItemView>
#include <QHeaderView>
#include <QIcon>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QTimer>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Miva SCAPMS | Dashboard");

    //--setup and populate the overview tables
    setupOverviewTables();
    refreshOverviewTables();

    //--setup and populate the patients table
    setupPatientsTable();
    refreshPatientsTable();

    //--setup and populate the appointments table
    setupAppointmentsTable();
    refreshAppointmentsTable();

    //--populate patient search options
    ui->patientsSearchMethodCombo->addItem("Recursive Search (Patient Name)", "recursive_name");
    ui->patientsSearchMethodCombo->addItem("Linear Search (Patient ID)", "linear_id");
    ui->patientsSearchMethodCombo->addItem("Binary Search (Patient Name)", "binary_name");

    //--populate patient sorting options
    ui->patientsSortMethodCombo->addItem("Patient Name (A - Z)", "name");
    ui->patientsSortMethodCombo->addItem("Patient Age (Ascending)", "age");

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
            QLabel#appointmentsTabTitleLabel {
                font-size: 20px;
                color: #121736;
                font-weight: bold;
            }

            QLabel#overviewSubtitleLabel,
            QLabel#patientsTabSubtitleLabel,
            QLabel#appointmentsTabSubtitleLabel {
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
            QWidget#appointmentsFormContainer {
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupOverviewTables()
{
    // Waiting Queue Table
    ui->waitingQueueTable->setColumnCount(4);

    ui->waitingQueueTable->setHorizontalHeaderLabels(
        {"Patient ID", "Patient Name", "Category", "Priority"});

    ui->waitingQueueTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->waitingQueueTable->verticalHeader()->setVisible(false);
    ui->waitingQueueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->waitingQueueTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->waitingQueueTable->setAlternatingRowColors(true);

    // Upcoming Appointments Table
    ui->upcomingAppointmentsTable->setColumnCount(4);

    ui->upcomingAppointmentsTable->setHorizontalHeaderLabels(
        {"Patient", "Reason", "Date & Time", "Status"});

    ui->upcomingAppointmentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->upcomingAppointmentsTable->verticalHeader()->setVisible(false);
    ui->upcomingAppointmentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->upcomingAppointmentsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->upcomingAppointmentsTable->setAlternatingRowColors(true);
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
    ui->upcomingAppointmentsTable->setRowCount(0);

    for (const auto &appointment : database.getAppointments()) {
        //--ignore cancelled appointments
        if (appointment->getStatus() == "Cancelled")
            continue;

        SCAPMS::PatientRecord *patient = appointment->getPatient();

        if (!patient)
            continue;

        int row = ui->upcomingAppointmentsTable->rowCount();

        ui->upcomingAppointmentsTable->insertRow(row);

        QString dateTimeText = appointment->getDateTime().isValid()
                                   ? appointment->getDateTime().toString("dd MMM yyyy, hh:mm AP")
                                   : "Not scheduled";

        ui->upcomingAppointmentsTable->setItem(row, 0, new QTableWidgetItem(patient->getName()));

        ui->upcomingAppointmentsTable->setItem(row,
                                               1,
                                               new QTableWidgetItem(appointment->getReason()));

        ui->upcomingAppointmentsTable->setItem(row, 2, new QTableWidgetItem(dateTimeText));

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

        //--refresh the interface
        applyPatientFiltersAndSort();
        refreshOverviewTables();

        clearPatientForm();

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

        //--refresh appointment displays
        refreshAppointmentsTable();
        refreshOverviewTables();

        QString appointmentId = database.getAppointments().back()->getId();

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

    //--refresh tables
    refreshAppointmentsTable();
    refreshOverviewTables();

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