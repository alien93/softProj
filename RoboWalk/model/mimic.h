#ifndef MIMIC_H
#define MIMIC_H
//This tag is used to specify that the defined joint mimics another existing joint.
//The value of this joint can be computed as value = multiplier * other_joint_value + offset.

#include <QString>

class Mimic
{
private:
    QString joint; //This specifies the name of the joint to mimic.
    double multiplier; //Specifies the multiplicative factor in the formula above. Defaults to 1.
    double offset; //Specifies the offset to add in the formula above. Defaults to 0.
public:
    Mimic();
    Mimic(QString joint, double multiplier, double offset);

    QString getJoint() const;
    void setJoint(const QString &value);
    double getMultiplier() const;
    void setMultiplier(double value);
    double getOffset() const;
    void setOffset(double value);

};

#endif // MIMIC_H
