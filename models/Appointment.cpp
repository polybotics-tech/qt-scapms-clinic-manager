#include "Appointment.h"

namespace SCAPMS {

Appointment::Appointment(PatientRecord *patient, const QString &reason)
    : patient(patient)
    , reason(reason)
    , status("Pending")
{}

void SCAPMS::Appointment::setId(const QString &id)
{
    this->id = id;
}

QString SCAPMS::Appointment::getId() const
{
    return id;
}

bool Appointment::schedule(const QDateTime &dateTime)
{
    if (!dateTime.isValid() || dateTime <= QDateTime::currentDateTime()) {
        return false;
    }

    this->dateTime = dateTime;
    status = "Scheduled";

    return true;
}

bool Appointment::cancel()
{
    if (status == "Cancelled") {
        return false;
    }

    status = "Cancelled";

    return true;
}

PatientRecord *Appointment::getPatient() const
{
    return patient;
}

QString Appointment::getReason() const
{
    return reason;
}

QDateTime Appointment::getDateTime() const
{
    return dateTime;
}

QString Appointment::getStatus() const
{
    return status;
}

void Appointment::restoreState(const QDateTime &dateTime, const QString &status)
{
    this->dateTime = dateTime;
    this->status = status;
}

} // namespace SCAPMS