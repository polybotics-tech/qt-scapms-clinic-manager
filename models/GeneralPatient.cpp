#include "GeneralPatient.h"

namespace SCAPMS {

GeneralPatient::GeneralPatient(const QString &id,
                               const QString &name,
                               int age,
                               const QString &contact)
    : PatientRecord(id, name, age, contact)
{}

QString GeneralPatient::getPatientType() const
{
    return "General";
}

int GeneralPatient::getPriority() const
{
    return 3;
}

} // namespace SCAPMS