#ifndef URDFPARSER_H
#define URDFPARSER_H

#include <qstring.h>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include "model/robotmodel.h"

class URDFparser
{
private:
    static bool instanceFlag;
    static URDFparser* instance;
    URDFparser();
    void parseChildNodes(QDomElement root, int i);
public:
    RobotModel rm;                          //model ucitanog robota
    static URDFparser* getInstance();
    int parseURDF(QString filename);
    ~URDFparser()
    {
        instanceFlag = false;
    }
};

#endif // URDFPARSER_H
