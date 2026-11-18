#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controllers/ClinicDatabase.h"

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    SCAPMS::ClinicDatabase database;

    void setupOverviewTables();
    void refreshOverviewTables();

    std::vector<SCAPMS::PatientRecord *> displayedPatients;
    void setupPatientsTable();
    void refreshPatientsTable();
    void registerPatient();
    void clearPatientForm();
    void searchPatients();
    void sortPatients();
    void applyPatientFiltersAndSort();
    void addSelectedPatientToQueue();

    SCAPMS::PatientRecord *selectedAppointmentPatient = nullptr;
    void setupAppointmentsTable();
    void refreshAppointmentsTable();
    void preparePatientAppointment();
    void scheduleAppointment();
    void clearAppointmentForm();
    void cancelAppointment();
};
#endif // MAINWINDOW_H
