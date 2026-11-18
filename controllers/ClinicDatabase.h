#ifndef CLINICDATABASE_H
#define CLINICDATABASE_H

#include "../models/Appointment.h"
#include "../models/PatientRecord.h"

#include <QString>
#include <array>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

namespace SCAPMS {

class ClinicDatabase
{
public:
    ClinicDatabase() = default;

    //--patient management
    QString generatePatientId() const;
    bool addPatient(std::unique_ptr<PatientRecord> patient);
    PatientRecord *findPatientById(const QString &id) const;
    const std::vector<std::unique_ptr<PatientRecord>> &getPatients() const;
    int getPatientCount() const;
    void addRecentPatient(PatientRecord *patient);
    std::vector<PatientRecord *> getRecentPatients() const;

    void enqueuePatient(PatientRecord *patient);
    PatientRecord *dequeuePatient();
    int getWaitingCount() const;
    std::vector<PatientRecord *> getWaitingPatients() const;

    //--patient data persistence
    bool savePatientsToJson(const QString &filePath) const;
    bool loadPatientsFromJson(const QString &filePath);

    //--searching algorithms
    std::vector<PatientRecord *> linearSearchPatientById(const QString &id) const;
    std::vector<PatientRecord *> binarySearchPatientByName(const QString &name) const;
    std::vector<PatientRecord *> recursiveSearchPatientByName(const QString &name) const;

    //--sorting algorithms
    void selectionSortPatientByName();
    void insertionSortPatientByAge();

    //--temporary collection sorting
    void selectionSortPatientByName(std::vector<PatientRecord *> &records) const;
    void insertionSortPatientByAge(std::vector<PatientRecord *> &records) const;

    //--appointment management
    QString generateAppointmentId() const;
    bool addAppointment(std::unique_ptr<Appointment> appointment);
    const std::vector<std::unique_ptr<Appointment>> &getAppointments() const;

    //--administrative undo
    void recordAdminAction(const QString &action);
    bool undoLastAction(QString &action);

private:
    //--main patient collection
    std::vector<std::unique_ptr<PatientRecord>> patients;

    //--fixed array for recent patients
    std::array<PatientRecord *, 10> recentPatients{};

    int recentCount = 0;
    int recentIndex = 0;

    //--waiting queue
    std::queue<PatientRecord *> waitingQueue;

    //--appointment collection
    std::vector<std::unique_ptr<Appointment>> appointments;

    //--administrative action history
    std::stack<QString> adminHistory;

    //--recursive search
    void recursiveSearchPatientByNameHelper(const QString &name,
                                            int index,
                                            std::vector<PatientRecord *> &results) const;
};

} // namespace SCAPMS

#endif // CLINICDATABASE_H