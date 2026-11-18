#ifndef CLINICEXCEPTION_H
#define CLINICEXCEPTION_H

#include <QString>
#include <exception>

namespace SCAPMS {

class ClinicException : public std::exception
{
public:
    explicit ClinicException(const QString &message);

    const char *what() const noexcept override;

private:
    QByteArray errorMessage;
};

} // namespace SCAPMS

#endif // CLINICEXCEPTION_H