#ifndef DIRECTION_CPP
#define DIRECTION_CPP

#include <iostream>
#include <math.h>

using namespace std;

/* Direction  has the three components of a direction vector x, y, z */

class Direction
{
public:
    // Default constructor
    Direction() { x = y = z = 0; };  

    // constructor to create direction vector from three coordinates
    Direction(double inX, double inY, double inZ)
        : x{ inX }, y{ inY }, z{ inZ } {};

    //Direction operator*(const Direction &v) const { return Direction(this * v.x, this * v.y, this * v.z); }
    
    // vector math operations
    double dotProduct(const Direction &d) const { return (x * d.x + y * d.y + z * d.z); };
    Direction crossProduct(const Direction &d) const { return Direction(y*d.z - z*d.y, -1.0*(x*d.z - z*d.x), x*d.y - y*d.x); };
    Direction normalize() { return Direction(x / sqrt(x*x + y*y + z*z), y / sqrt(x*x + y*y + z*z), z / sqrt(x*x + y*y + z*z)); };
	Direction operator*(const double d) const { return Direction(x*d, y*d, z*d); };
    Direction operator-(const Direction &d) const { return Direction(x - d.x, y - d.y, z - d.z); };
    Direction operator+(const Direction &d) const { return Direction(x + d.x, y + d.y, z + d.z); };
	double length() { return( sqrt( pow(x, 2) + pow(y, 2) + pow(z, 2) ) ); };
    Direction operator/(const double &d) const { return Direction(x / d, y / d, z / d); }

    // print coordinates of direction vector
    void printDirection()
    {
        std::cout << x << " " << y << " " << z << std::endl;
    };

	double x, y, z;

private:
 
};

#endif // !DIRECTION_CPP