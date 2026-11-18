#ifndef GENERALPATIENT_H
#define GENERALPATIENT_H

#include "PatientRecord.h"

namespace SCAPMS {

class GeneralPatient : public PatientRecord
{
public:
    GeneralPatient(const QString &id, const QString &name, int age, const QString &contact);

    QString getPatientType() const override;
    int getPriority() const override;
};

} // namespace SCAPMS

#endif // GENERALPATIENT_H