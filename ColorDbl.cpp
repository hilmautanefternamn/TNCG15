#ifndef COLORDBL_CPP
#define COLORDBL_CPP

#include <iostream>
using namespace std;

/* ColorDbl has three double precision variables that contain the intensities in the
red, green and blue channel.*/

enum surfaceType { reflective, diffuse };


class ColorDbl
{
public:
    // Default constructor
    ColorDbl() 
        :red{ 0.0 }, green{ 0.0 }, blue{ 0.0 } {};

    // constructor to create color given values for red, green and blue channel
    ColorDbl(double R, double G, double B)
        : red{ R }, green{ G }, blue{ B } {};

	ColorDbl operator*(const double d) { return ColorDbl(red*d, green*d, blue*d); };
	ColorDbl operator+(const ColorDbl c) { return ColorDbl(red+c.red, green + c.green, blue + c.blue); };
	ColorDbl operator/(const double d) { return ColorDbl(red/d, green/d, blue/d); };

	double red, green, blue;

private:   
    // print red, green and blue channel
    friend std::ostream& operator<< (std::ostream &os, const ColorDbl &c)
    {
        os << c.red << ", " << c.green << ", " << c.blue << endl;
        return os;
    }
};

#endif // !COLORDBL_CPP