#include "child.h"

Child::Child()
{

}

Child::Child(QString link)
{
    this->link = link;
}

QString Child::getLink() const
{
    return link;
}

void Child::setLink(const QString &value)
{
    link = value;
}

