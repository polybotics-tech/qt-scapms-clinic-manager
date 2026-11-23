#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Appointable.h"
#include "PatientRecord.h"

#include <QDateTime>
#include <QString>

namespace SCAPMS {

class Appointment : public Appointable
{
public:
    Appointment(PatientRecord *patient, const QString &reason);

    void setId(const QString &id);
    QString getId() const;

    bool schedule(const QDateTime &dateTime) override;
    bool cancel() override;

    PatientRecord *getPatient() const;
    QString getReason() const;
    QDateTime getDateTime() const;
    QString getStatus() const;

    void restoreState(const QDateTime &dateTime, const QString &status);

private:
    QString id;
    PatientRecord *patient;
    QString reason;
    QDateTime dateTime;
    QString status;
};

} // namespace SCAPMS

#endif // APPOINTMENT_H