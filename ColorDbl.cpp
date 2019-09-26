#ifndef COLORDBL_CPP
#define COLORDBL_CPP

#include <iostream>
using namespace std;

/* ColorDbl has three double precision variables that contain the intensities in the
red, green and blue channel.*/
class ColorDbl
{
public:
    ColorDbl() // Default constructor
        :red(0.0), green(0.0), blue(0.0) {};

    ColorDbl(double R, double G, double B)
        : red(R), green(G), blue(B) {};

private:
    double red, green, blue;

    friend std::ostream& operator<< (std::ostream &os, const ColorDbl &c)
    {
        os << c.red << ", " << c.green << ", " << c.blue << endl;

        return os;
    }
};

#endif // !COLORDBL_CPP