#include "transmissiontype.h"

QString TransmissionType::getType() const
{
    return type;
}

void TransmissionType::setType(const QString &value)
{
    type = value;
}

TransmissionType::TransmissionType()
{

}

TransmissionType::TransmissionType(QString type)
{
    this->type = type;
}
