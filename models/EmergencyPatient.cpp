#include "EmergencyPatient.h"

namespace SCAPMS {

EmergencyPatient::EmergencyPatient(const QString &id,
                                   const QString &name,
                                   int age,
                                   const QString &contact)
    : PatientRecord(id, name, age, contact)
{}

QString EmergencyPatient::getPatientType() const
{
    return "Emergency";
}

int EmergencyPatient::getPriority() const
{
    return 1;
}

} // namespace SCAPMS