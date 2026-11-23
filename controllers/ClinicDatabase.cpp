#include "ClinicDatabase.h"
#include "../models/EmergencyPatient.h"
#include "../models/FollowUpPatient.h"
#include "../models/GeneralPatient.h"
#include "../utils/ClinicException.h"

#include <QFile>
#include <QHash>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QSaveFile>
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
void SCAPMS::ClinicDatabase::recordAdminAction(const QString &action,
                                               bool reversible,
                                               const QString &actionType,
                                               const QString &targetId)
{
    AdminAction newAction;

    newAction.id = nextAdminActionId++;
    newAction.description = action;
    newAction.timestamp = QDateTime::currentDateTime();
    newAction.status = "Completed";
    newAction.reversible = reversible;
    newAction.actionType = actionType;
    newAction.targetId = targetId;

    adminActionHistory.push_back(newAction);

    if (reversible)
        adminUndoStack.push(newAction.id);
}

bool SCAPMS::ClinicDatabase::undoLastAction(QString &action)
{
    if (adminUndoStack.empty())
        return false;

    int actionId = adminUndoStack.top();

    //--find the corresponding history record
    auto it = std::find_if(adminActionHistory.begin(),
                           adminActionHistory.end(),
                           [actionId](const AdminAction &item) { return item.id == actionId; });

    if (it == adminActionHistory.end()) {
        adminUndoStack.pop();
        return false;
    }

    if (it->status != "Completed" || !it->reversible) {
        adminUndoStack.pop();
        return false;
    }

    //--reverse the actual operation
    if (it->actionType == "appointment_scheduled") {
        Appointment *appointment = nullptr;

        for (const auto &item : appointments) {
            if (item->getId() == it->targetId) {
                appointment = item.get();
                break;
            }
        }

        if (!appointment || appointment->getStatus() != "Scheduled")
            return false;

        if (!appointment->cancel())
            return false;
    } else {
        return false;
    }

    action = it->description;

    it->status = "Undone";
    adminUndoStack.pop();

    return true;
}

const std::vector<SCAPMS::AdminAction> &SCAPMS::ClinicDatabase::getAdminHistory() const
{
    return adminActionHistory;
}

int SCAPMS::ClinicDatabase::getTotalAdminActions() const
{
    return static_cast<int>(adminActionHistory.size());
}

int SCAPMS::ClinicDatabase::getReversibleAdminActions() const
{
    int count = 0;

    for (const auto &action : adminActionHistory) {
        if (action.reversible && action.status == "Completed")
            count++;
    }

    return count;
}

QString SCAPMS::ClinicDatabase::getLastAdminAction() const
{
    if (adminActionHistory.empty())
        return "No activity";

    return adminActionHistory.back().description;
}

void SCAPMS::ClinicDatabase::clearAdminHistory()
{
    adminActionHistory.clear();

    while (!adminUndoStack.empty())
        adminUndoStack.pop();

    while (!adminHistory.empty())
        adminHistory.pop();

    nextAdminActionId = 1;
}

//--data persistence
bool ClinicDatabase::saveDataToJson(const QString &filePath) const
{
    QJsonObject rootObject;

    //--patients
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

    rootObject["patients"] = patientArray;

    //--appointments
    QJsonArray appointmentArray;

    for (const auto &appointment : appointments) {
        QJsonObject appointmentObject;

        appointmentObject["id"] = appointment->getId();

        appointmentObject["patientId"] = appointment->getPatient()->getId();

        appointmentObject["reason"] = appointment->getReason();

        appointmentObject["dateTime"] = appointment->getDateTime().isValid()
                                            ? appointment->getDateTime().toString(Qt::ISODateWithMs)
                                            : QString();

        appointmentObject["status"] = appointment->getStatus();

        appointmentArray.append(appointmentObject);
    }

    rootObject["appointments"] = appointmentArray;

    //--waiting queue
    QJsonArray waitingQueueArray;

    //--copy the queue to avoid modifying the original.
    std::queue<PatientRecord *> queueCopy = waitingQueue;

    while (!queueCopy.empty()) {
        PatientRecord *patient = queueCopy.front();

        if (patient) {
            waitingQueueArray.append(patient->getId());
        }

        queueCopy.pop();
    }

    rootObject["waitingQueue"] = waitingQueueArray;

    //--admin action history
    QJsonArray adminHistoryArray;

    for (const AdminAction &action : adminActionHistory) {
        QJsonObject actionObject;

        actionObject["id"] = action.id;
        actionObject["description"] = action.description;
        actionObject["timestamp"] = action.timestamp.toString(Qt::ISODateWithMs);
        actionObject["status"] = action.status;
        actionObject["reversible"] = action.reversible;
        actionObject["actionType"] = action.actionType;
        actionObject["targetId"] = action.targetId;

        adminHistoryArray.append(actionObject);
    }

    rootObject["adminHistory"] = adminHistoryArray;

    //--admin action undo history
    QJsonArray undoHistoryArray;

    // Preserve the stack's original top-to-bottom order.
    std::stack<int> undoStackCopy = adminUndoStack;

    while (!undoStackCopy.empty()) {
        undoHistoryArray.append(undoStackCopy.top());
        undoStackCopy.pop();
    }

    rootObject["undoHistory"] = undoHistoryArray;

    //--additional database metadata
    rootObject["version"] = 1;
    rootObject["nextAdminActionId"] = nextAdminActionId;

    //--write as JSON in file
    QJsonDocument document(rootObject);

    QSaveFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QByteArray jsonData = document.toJson(QJsonDocument::Indented);

    if (file.write(jsonData) != jsonData.size()) {
        file.cancelWriting();
        return false;
    }

    return file.commit();
}

bool ClinicDatabase::loadDataFromJson(const QString &filePath)
{
    //--read and validate JSON file
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

    if (rootObject["version"].toInt() != 1 || !rootObject["patients"].isArray()
        || !rootObject["appointments"].isArray() || !rootObject["waitingQueue"].isArray()
        || !rootObject["adminHistory"].isArray() || !rootObject["undoHistory"].isArray()
        || !rootObject["nextAdminActionId"].isDouble()) {
        return false;
    }

    //--temporary database storage
    std::vector<std::unique_ptr<PatientRecord>> loadedPatients;
    std::vector<std::unique_ptr<Appointment>> loadedAppointments;

    std::queue<PatientRecord *> loadedWaitingQueue;

    std::vector<AdminAction> loadedAdminHistory;
    std::stack<int> loadedUndoStack;

    QHash<QString, PatientRecord *> patientLookup;

    QSet<QString> patientIds;
    QSet<QString> appointmentIds;
    QSet<int> adminActionIds;
    QSet<int> undoActionIds;

    //--restore patients
    QJsonArray patientArray = rootObject["patients"].toArray();

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
            || contact.trimmed().isEmpty() || patientIds.contains(id)) {
            return false;
        }

        std::unique_ptr<PatientRecord> patient;

        if (type == "General") {
            patient = std::make_unique<GeneralPatient>(id, name, age, contact);

        } else if (type == "Emergency") {
            patient = std::make_unique<EmergencyPatient>(id, name, age, contact);

        } else if (type == "Follow-up") {
            patient = std::make_unique<FollowUpPatient>(id, name, age, contact);

        } else {
            return false;
        }

        patientIds.insert(id);

        patientLookup.insert(id, patient.get());

        loadedPatients.push_back(std::move(patient));
    }

    //--restore appointments
    QJsonArray appointmentArray = rootObject["appointments"].toArray();

    for (const QJsonValue &value : appointmentArray) {
        if (!value.isObject()) {
            return false;
        }

        QJsonObject object = value.toObject();

        if (!object["id"].isString() || !object["patientId"].isString()
            || !object["reason"].isString() || !object["dateTime"].isString()
            || !object["status"].isString()) {
            return false;
        }

        QString id = object["id"].toString();
        QString patientId = object["patientId"].toString();
        QString reason = object["reason"].toString();
        QString dateTimeString = object["dateTime"].toString();
        QString status = object["status"].toString();

        if (id.trimmed().isEmpty() || reason.trimmed().isEmpty() || appointmentIds.contains(id)
            || !patientLookup.contains(patientId)) {
            return false;
        }

        if (status != "Pending" && status != "Scheduled" && status != "Cancelled") {
            return false;
        }

        QDateTime dateTime;

        if (!dateTimeString.isEmpty()) {
            dateTime = QDateTime::fromString(dateTimeString, Qt::ISODateWithMs);

            if (!dateTime.isValid()) {
                dateTime = QDateTime::fromString(dateTimeString, Qt::ISODate);
            }

            if (!dateTime.isValid()) {
                return false;
            }
        }

        if (status == "Scheduled" && !dateTime.isValid()) {
            return false;
        }

        PatientRecord *patient = patientLookup.value(patientId);

        auto appointment = std::make_unique<Appointment>(patient, reason);

        appointment->setId(id);

        appointment->restoreState(dateTime, status);

        appointmentIds.insert(id);

        loadedAppointments.push_back(std::move(appointment));
    }

    //--restore waiting queue
    QJsonArray waitingQueueArray = rootObject["waitingQueue"].toArray();

    QSet<QString> queuedPatientIds;

    for (const QJsonValue &value : waitingQueueArray) {
        if (!value.isString()) {
            return false;
        }

        QString patientId = value.toString();

        if (!patientLookup.contains(patientId) || queuedPatientIds.contains(patientId)) {
            return false;
        }

        queuedPatientIds.insert(patientId);

        loadedWaitingQueue.push(patientLookup.value(patientId));
    }

    //--restore admin action history
    QJsonArray adminHistoryArray = rootObject["adminHistory"].toArray();

    int maximumActionId = 0;

    for (const QJsonValue &value : adminHistoryArray) {
        if (!value.isObject()) {
            return false;
        }

        QJsonObject object = value.toObject();

        if (!object["id"].isDouble() || !object["description"].isString()
            || !object["timestamp"].isString() || !object["status"].isString()
            || !object["reversible"].isBool() || !object["actionType"].isString()
            || !object["targetId"].isString()) {
            return false;
        }

        AdminAction action;

        action.id = object["id"].toInt();
        action.description = object["description"].toString();

        action.timestamp = QDateTime::fromString(object["timestamp"].toString(), Qt::ISODateWithMs);

        action.status = object["status"].toString();
        action.reversible = object["reversible"].toBool();
        action.actionType = object["actionType"].toString();
        action.targetId = object["targetId"].toString();

        if (action.id <= 0 || action.description.trimmed().isEmpty() || !action.timestamp.isValid()
            || action.status.trimmed().isEmpty() || adminActionIds.contains(action.id)) {
            return false;
        }

        adminActionIds.insert(action.id);

        maximumActionId = std::max(maximumActionId, action.id);

        loadedAdminHistory.push_back(action);
    }

    //--restore admin action undo
    QJsonArray undoHistoryArray = rootObject["undoHistory"].toArray();

    for (int i = undoHistoryArray.size() - 1; i >= 0; --i) {
        QJsonValue value = undoHistoryArray[i];

        if (!value.isDouble()) {
            return false;
        }

        int actionId = value.toInt(-1);

        if (!adminActionIds.contains(actionId) || undoActionIds.contains(actionId)) {
            return false;
        }

        undoActionIds.insert(actionId);

        loadedUndoStack.push(actionId);
    }

    //--
    int loadedNextActionId = rootObject["nextAdminActionId"].toInt(-1);

    if (loadedNextActionId <= maximumActionId || loadedNextActionId <= 0) {
        return false;
    }

    //--replace existing database contents after every section passed validation.

    patients = std::move(loadedPatients);
    appointments = std::move(loadedAppointments);
    waitingQueue = std::move(loadedWaitingQueue);
    adminActionHistory = std::move(loadedAdminHistory);
    adminUndoStack = std::move(loadedUndoStack);
    nextAdminActionId = loadedNextActionId;

    //--reset legacy administrative history.
    adminHistory = std::stack<QString>();

    //--rebuild recent patient list
    recentPatients.fill(nullptr);

    recentCount = 0;
    recentIndex = 0;

    for (const auto &patient : patients) {
        addRecentPatient(patient.get());
    }

    return true;
}

} // namespace SCAPMS