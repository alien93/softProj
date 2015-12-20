#ifndef PARENT_H
#define PARENT_H

#include <QString>

class Parent
{
private:
    QString link; // The name of the link that is the parent of this link in the robot tree structure.
public:
    Parent();
    Parent(QString link);

    QString getLink() const;
    void setLink(const QString &value);
};

#endif // PARENT_H
