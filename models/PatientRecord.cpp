#include "PatientRecord.h"

namespace SCAPMS {

PatientRecord::PatientRecord(const QString &id, const QString &name, int age, const QString &contact)
    : id(id)
    , name(name)
    , age(age)
    , contact(contact)
{}

QString PatientRecord::getId() const
{
    return id;
}

QString PatientRecord::getName() const
{
    return name;
}

int PatientRecord::getAge() const
{
    return age;
}

QString PatientRecord::getContact() const
{
    return contact;
}

} // namespace SCAPMS