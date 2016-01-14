#ifndef URDFPARSER_H
#define URDFPARSER_H

#include <qstring.h>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include "model/robotmodel.h"
#include "model/box.h"
#include "model/cylinder.h"
#include "model/sphere.h"

class URDFparser
{
private:
    static bool instanceFlag;
    static URDFparser* instance;
    static bool fileParsed;
    URDFparser();
    void parseChildNodes(QDomElement root, int i);
    void addInertialElementChildren(int i, QDomElement inertialElement, Inertial* inertial);
    map<QString, Link> usedLinks; //iscrtani linkovi za myglwidget

public:
    RobotModel rm;                          //model ucitanog robota
    static URDFparser* getInstance();
    int parseURDF(QString filename);
    ~URDFparser()
    {
        instanceFlag = false;
    }
    static bool getFileParsed();
    static void setFileParsed(bool value);
    map<QString, Link> getUsedLinks() const;
    void setUsedLinks(const map<QString, Link> &value);
};

#endif // URDFPARSER_H
