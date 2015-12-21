#ifndef COLOR_H
#define COLOR_H


class Color
{
private:
    double red;
    double green;
    double blue;
    double alpha;
public:
    Color();
    Color(double red, double green,
          double blue, double alpha);

    double getRed() const;
    void setRed(double value);
    double getGreen() const;
    void setGreen(double value);
    double getBlue() const;
    void setBlue(double value);
    double getAlpha() const;
    void setAlpha(double value);
};

#endif // COLOR_H
