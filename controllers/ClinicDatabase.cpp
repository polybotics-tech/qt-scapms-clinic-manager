#include "ClinicDatabase.h"
#include "../models/EmergencyPatient.h"
#include "../models/FollowUpPatient.h"
#include "../models/GeneralPatient.h"
#include "../utils/ClinicException.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QSet>

#include <algorithm>

namespace SCAPMS {

//--patient management
QString ClinicDatabase::generatePatientId() const
{
    int number = 1;

    while (true) {
        QString id = QString("P%1").arg(number, 4, 10, QChar('0'));

        if (!findPatientById(id))
            return id;

        number++;
    }
}

bool ClinicDatabase::addPatient(std::unique_ptr<PatientRecord> patient)
{
    if (!patient) {
        throw ClinicException("Invalid patient record.");
    }

    if (patient->getId().trimmed().isEmpty()) {
        throw ClinicException("Patient ID cannot be empty.");
    }

    if (patient->getName().trimmed().isEmpty()) {
        throw ClinicException("Patient name cannot be empty.");
    }

    if (patient->getAge() < 0 || patient->getAge() > 120) {
        throw ClinicException("Patient age must be between 0 and 120.");
    }

    if (patient->getContact().trimmed().isEmpty()) {
        throw ClinicException("Patient contact cannot be empty.");
    }

    if (findPatientById(patient->getId())) {
        throw ClinicException("A patient with this ID already exists.");
    }

    PatientRecord *newPatient = patient.get();

    patients.push_back(std::move(patient));

    addRecentPatient(newPatient);

    return true;
}

PatientRecord *ClinicDatabase::findPatientById(const QString &id) const
{
    for (const auto &patient : patients) {
        if (patient->getId() == id) {
            return patient.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<PatientRecord>> &ClinicDatabase::getPatients() const
{
    return patients;
}

int ClinicDatabase::getPatientCount() const
{
    return static_cast<int>(patients.size());
}

void ClinicDatabase::enqueuePatient(PatientRecord *patient)
{
    if (patient) {
        waitingQueue.push(patient);
    }
}

PatientRecord *ClinicDatabase::dequeuePatient()
{
    if (waitingQueue.empty()) {
        return nullptr;
    }

    PatientRecord *patient = waitingQueue.front();

    waitingQueue.pop();

    return patient;
}

int ClinicDatabase::getWaitingCount() const
{
    return static_cast<int>(waitingQueue.size());
}

std::vector<PatientRecord *> ClinicDatabase::getRecentPatients() const
{
    std::vector<PatientRecord *> result;

    for (int i = 0; i < recentCount; ++i) {
        int index = (recentIndex - recentCount + i + 10) % 10;

        result.push_back(recentPatients[index]);
    }

    return result;
}

void ClinicDatabase::addRecentPatient(PatientRecord *patient)
{
    if (!patient) {
        return;
    }

    recentPatients[recentIndex] = patient;

    recentIndex = (recentIndex + 1) % recentPatients.size();

    if (recentCount < static_cast<int>(recentPatients.size())) {
        recentCount++;
    }
}

std::vector<PatientRecord *> ClinicDatabase::linearSearchPatientById(const QString &id) const
{
    std::vector<PatientRecord *> results;

    QString searchId = id.trimmed();

    if (searchId.isEmpty())
        return results;

    for (const auto &patient : patients) {
        if (QString::compare(patient->getId(), searchId, Qt::CaseInsensitive) == 0) {
            results.push_back(patient.get());
        }
    }

    return results;
}

std::vector<PatientRecord *> ClinicDatabase::binarySearchPatientByName(const QString &name) const
{
    std::vector<PatientRecord *> results;

    QString searchName = name.trimmed();

    if (searchName.isEmpty())
        return results;

    //--create a temporary collection of patient pointers.
    std::vector<PatientRecord *> sortedPatients;

    for (const auto &patient : patients) {
        sortedPatients.push_back(patient.get());
    }

    //--sort the temporary collection alphabetically.
    for (int i = 0; i < static_cast<int>(sortedPatients.size()) - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < static_cast<int>(sortedPatients.size()); ++j) {
            if (QString::compare(sortedPatients[j]->getName(),
                                 sortedPatients[minIndex]->getName(),
                                 Qt::CaseInsensitive)
                < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(sortedPatients[i], sortedPatients[minIndex]);
        }
    }

    //--binary search for the first name beginning with the query.
    int left = 0;
    int right = static_cast<int>(sortedPatients.size()) - 1;
    int firstMatch = -1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        QString patientName = sortedPatients[middle]->getName();

        int comparison = QString::compare(patientName.left(searchName.length()),
                                          searchName,
                                          Qt::CaseInsensitive);

        if (comparison >= 0) {
            if (comparison == 0)
                firstMatch = middle;

            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    if (firstMatch == -1)
        return results;

    //--collect all consecutive matching names.
    for (int i = firstMatch; i < static_cast<int>(sortedPatients.size()); ++i) {
        if (sortedPatients[i]->getName().startsWith(searchName, Qt::CaseInsensitive)) {
            results.push_back(sortedPatients[i]);
        } else {
            break;
        }
    }

    return results;
}

void ClinicDatabase::recursiveSearchPatientByNameHelper(const QString &name,
                                                        int index,
                                                        std::vector<PatientRecord *> &results) const
{
    //--all patients have been checked.
    if (index >= static_cast<int>(patients.size()))
        return;

    //--check whether the current patient's name contains the search text.
    if (patients[index]->getName().contains(name, Qt::CaseInsensitive)) {
        results.push_back(patients[index].get());
    }

    //--recursively check the next patient.
    recursiveSearchPatientByNameHelper(name, index + 1, results);
}

std::vector<PatientRecord *> ClinicDatabase::recursiveSearchPatientByName(const QString &name) const
{
    std::vector<PatientRecord *> results;

    QString searchName = name.trimmed();

    if (searchName.isEmpty())
        return results;

    recursiveSearchPatientByNameHelper(searchName, 0, results);

    return results;
}

void ClinicDatabase::selectionSortPatientByName()
{
    int size = static_cast<int>(patients.size());

    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < size; ++j) {
            if (QString::compare(patients[j]->getName(),
                                 patients[minIndex]->getName(),
                                 Qt::CaseInsensitive)
                < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(patients[i], patients[minIndex]);
        }
    }
}

void ClinicDatabase::selectionSortPatientByName(std::vector<PatientRecord *> &records) const
{
    int size = static_cast<int>(records.size());

    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < size; ++j) {
            if (QString::compare(records[j]->getName(),
                                 records[minIndex]->getName(),
                                 Qt::CaseInsensitive)
                < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(records[i], records[minIndex]);
        }
    }
}

void ClinicDatabase::insertionSortPatientByAge()
{
    int size = static_cast<int>(patients.size());

    for (int i = 1; i < size; ++i) {
        auto key = std::move(patients[i]);

        int j = i - 1;

        while (j >= 0 && patients[j]->getAge() > key->getAge()) {
            patients[j + 1] = std::move(patients[j]);
            --j;
        }

        patients[j + 1] = std::move(key);
    }
}

void ClinicDatabase::insertionSortPatientByAge(std::vector<PatientRecord *> &records) const
{
    int size = static_cast<int>(records.size());

    for (int i = 1; i < size; ++i) {
        PatientRecord *key = records[i];

        int j = i - 1;

        while (j >= 0 && records[j]->getAge() > key->getAge()) {
            records[j + 1] = records[j];
            --j;
        }

        records[j + 1] = key;
    }
}

std::vector<PatientRecord *> ClinicDatabase::getWaitingPatients() const
{
    std::queue<PatientRecord *> copy = waitingQueue;

    std::vector<PatientRecord *> result;

    while (!copy.empty()) {
        result.push_back(copy.front());
        copy.pop();
    }

    return result;
}

bool ClinicDatabase::savePatientsToJson(const QString &filePath) const
{
    QJsonArray patientArray;

    for (const auto &patient : patients) {
        QJsonObject patientObject;

        patientObject["id"] = patient->getId();
        patientObject["name"] = patient->getName();
        patientObject["age"] = patient->getAge();
        patientObject["contact"] = patient->getContact();
        patientObject["type"] = patient->getPatientType();

        patientArray.append(patientObject);
    }

    QJsonObject rootObject;
    rootObject["patients"] = patientArray;

    QJsonDocument document(rootObject);

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    file.write(document.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool ClinicDatabase::loadPatientsFromJson(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QJsonParseError parseError;

    QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);

    file.close();

    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        return false;
    }

    QJsonObject rootObject = document.object();

    if (!rootObject["patients"].isArray()) {
        return false;
    }

    QJsonArray patientArray = rootObject["patients"].toArray();

    std::vector<std::unique_ptr<PatientRecord>> loadedPatients;
    QSet<QString> patientIds;

    //--validate and reconstruct patient records.
    for (const QJsonValue &value : patientArray) {
        if (!value.isObject()) {
            return false;
        }

        QJsonObject object = value.toObject();

        if (!object["id"].isString() || !object["name"].isString() || !object["age"].isDouble()
            || !object["contact"].isString() || !object["type"].isString()) {
            return false;
        }

        QString id = object["id"].toString();
        QString name = object["name"].toString();
        int age = object["age"].toInt(-1);
        QString contact = object["contact"].toString();
        QString type = object["type"].toString();

        if (id.trimmed().isEmpty() || name.trimmed().isEmpty() || age < 0 || age > 120
            || contact.trimmed().isEmpty() || patientIds.contains(id) || findPatientById(id)) {
            return false;
        }

        patientIds.insert(id);

        if (type == "General") {
            loadedPatients.push_back(std::make_unique<GeneralPatient>(id, name, age, contact));

        } else if (type == "Emergency") {
            loadedPatients.push_back(std::make_unique<EmergencyPatient>(id, name, age, contact));

        } else if (type == "Follow-up") {
            loadedPatients.push_back(std::make_unique<FollowUpPatient>(id, name, age, contact));

        } else {
            return false;
        }
    }

    // Add validated records to the database.
    try {
        for (auto &patient : loadedPatients) {
            addPatient(std::move(patient));
        }
    } catch (const ClinicException &) {
        return false;
    }

    return true;
}

//--appointment management
QString SCAPMS::ClinicDatabase::generateAppointmentId() const
{
    int number = 1;

    while (true) {
        QString id = QString("A%1").arg(number, 4, 10, QChar('0'));

        bool exists = false;

        for (const auto &appointment : appointments) {
            if (appointment->getId() == id) {
                exists = true;
                break;
            }
        }

        if (!exists)
            return id;

        number++;
    }
}

bool ClinicDatabase::addAppointment(std::unique_ptr<Appointment> appointment)
{
    if (!appointment || !appointment->getPatient()) {
        return false;
    }

    bool patientExists = false;

    for (const auto &patient : patients) {
        if (patient.get() == appointment->getPatient()) {
            patientExists = true;
            break;
        }
    }

    if (!patientExists) {
        return false;
    }

    appointments.push_back(std::move(appointment));

    return true;
}

const std::vector<std::unique_ptr<Appointment>> &ClinicDatabase::getAppointments() const
{
    return appointments;
}

//--administrative undo

void ClinicDatabase::recordAdminAction(const QString &action)
{
    adminHistory.push(action);
}

bool ClinicDatabase::undoLastAction(QString &action)
{
    if (adminHistory.empty()) {
        return false;
    }

    action = adminHistory.top();

    adminHistory.pop();

    return true;
}

} // namespace SCAPMS