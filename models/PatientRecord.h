#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include <QString>

namespace SCAPMS {

class PatientRecord
{
public:
    PatientRecord(const QString &id, const QString &name, int age, const QString &contact);

    virtual ~PatientRecord() = default;

    // Getters
    QString getId() const;
    QString getName() const;
    int getAge() const;
    QString getContact() const;

    // Every patient category must implement these.
    virtual QString getPatientType() const = 0;
    virtual int getPriority() const = 0;

protected:
    QString id;
    QString name;
    int age;
    QString contact;
};

} // namespace SCAPMS

#endif // PATIENTRECORD_H