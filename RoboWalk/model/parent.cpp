#include "parent.h"

Parent::Parent()
{

}

Parent::Parent(QString link)
{
    this->link = link;
}


QString Parent::getLink() const
{
    return link;
}

void Parent::setLink(const QString &value)
{
    link = value;
}


