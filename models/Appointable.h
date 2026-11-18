#ifndef APPOINTABLE_H
#define APPOINTABLE_H

#include <QDateTime>

namespace SCAPMS {

class Appointable
{
public:
    virtual ~Appointable() = default;

    virtual bool schedule(const QDateTime &dateTime) = 0;
    virtual bool cancel() = 0;
};

} // namespace SCAPMS

#endif // APPOINTABLE_H