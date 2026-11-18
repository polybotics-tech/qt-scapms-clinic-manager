#ifndef EMERGENCYPATIENT_H
#define EMERGENCYPATIENT_H

#include "PatientRecord.h"

namespace SCAPMS {

class EmergencyPatient : public PatientRecord
{
public:
    EmergencyPatient(const QString &id, const QString &name, int age, const QString &contact);

    QString getPatientType() const override;
    int getPriority() const override;
};

} // namespace SCAPMS

#endif // EMERGENCYPATIENT_H