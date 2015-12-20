#include "mass.h"


Mass::Mass()
{

}

Mass::Mass(double value)
{
    this->value = value;
}

double Mass::getValue() const
{
    return value;
}

void Mass::setValue(double value)
{
    value = value;
}
