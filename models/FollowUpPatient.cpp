#include "FollowUpPatient.h"

namespace SCAPMS {

FollowUpPatient::FollowUpPatient(const QString &id,
                                 const QString &name,
                                 int age,
                                 const QString &contact)
    : PatientRecord(id, name, age, contact)
{}

QString FollowUpPatient::getPatientType() const
{
    return "Follow-up";
}

int FollowUpPatient::getPriority() const
{
    return 2;
}

} // namespace SCAPMS
