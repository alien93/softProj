#ifndef LINK_H
#define LINK_H

#include <QString>
#include "visual.h"
#include "inertial.h"
#include "collision.h"
#include <iostream>
#include <vector>
#include "model/box.h"
#include "model/cylinder.h"
#include "model/sphere.h"

using namespace std;


class Link
{
private:
    QString name;
    Inertial inertial;
    vector<Visual> visual;
    Collision collision;
public:
    Link();
    Link(QString name, Inertial inertial, vector<Visual> visual, Collision collision);


    QString getName() const;
    void setName(const QString &value);
    Inertial getInertial() const;
    void setInertial(const Inertial &value);
    Collision getCollision() const;
    void setCollision(const Collision &value);
    vector<Visual> getVisual() const;
    void setVisual(const vector<Visual> &value);
    QString toString();
};

#endif // LINK_H
