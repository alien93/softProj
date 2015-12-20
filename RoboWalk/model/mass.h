#ifndef MASS_H
#define MASS_H


class Mass
{
private:
    double value;
public:
    Mass();
    Mass(double value);

    double getValue() const;
    void setValue(double value);
};

#endif // MASS_H
