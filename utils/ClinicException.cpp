#include "ClinicException.h"

namespace SCAPMS {

ClinicException::ClinicException(const QString &message)
    : errorMessage(message.toUtf8())
{}

const char *ClinicException::what() const noexcept
{
    return errorMessage.constData();
}

} // namespace SCAPMS