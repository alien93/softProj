#ifndef URDFPARSER_H
#define URDFPARSER_H

#include <qstring.h>
#include <QtCore>
#include <QtXml>
#include <QDebug>


class URDFparser
{
private:

    void parseChildNodes(QDomElement root, int i);

public:
    URDFparser();
    int parseURDF(QString filename);
};

#endif // URDFPARSER_H
