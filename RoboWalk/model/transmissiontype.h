#ifndef TRANSMISSIONTYPE_H
#define TRANSMISSIONTYPE_H

#include <QString>

class TransmissionType
{
private:
    QString type;
public:
    TransmissionType();
    TransmissionType(QString type);


    QString getType() const;
    void setType(const QString &value);
};

#endif // TRANSMISSIONTYPE_H
