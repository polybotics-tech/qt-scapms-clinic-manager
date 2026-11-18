#ifndef FOLLOWUPPATIENT_H
#define FOLLOWUPPATIENT_H

#include "PatientRecord.h"

namespace SCAPMS {

class FollowUpPatient : public PatientRecord
{
public:
    FollowUpPatient(const QString &id, const QString &name, int age, const QString &contact);

    QString getPatientType() const override;
    int getPriority() const override;
};

} // namespace SCAPMS

#endif // FOLLOWUPPATIENT_H