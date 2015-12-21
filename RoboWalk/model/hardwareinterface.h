#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include <QString>

class HardwareInterface
{
private:
    QString hardwareInterface;
public:
    HardwareInterface();
    HardwareInterface(QString hardwareInterface);


    QString getHardwareInterface() const;
    void setHardwareInterface(const QString &value);
};

#endif // HARDWAREINTERFACE_H
