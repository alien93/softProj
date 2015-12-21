#include "hardwareinterface.h"

QString HardwareInterface::getHardwareInterface() const
{
    return hardwareInterface;
}

void HardwareInterface::setHardwareInterface(const QString &value)
{
    hardwareInterface = value;
}

HardwareInterface::HardwareInterface()
{

}

HardwareInterface::HardwareInterface(QString hardwareInterface)
{
    this->hardwareInterface = hardwareInterface;
}
