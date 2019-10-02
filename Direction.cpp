#ifndef DIRECTION_CPP
#define DIRECTION_CPP

#include <iostream>
#include <math.h>
using namespace std;

/* Direction  has the three components of a direction vector x, y, z */
class Direction
{
public:
    Direction() { x = y = z = 0; };  // Default constructor

    Direction(double inX, double inY, double inZ)
        : x(inX), y(inY), z(inZ) {};

    //Direction operator*(const Direction &v) const { return Direction(this * v.x, this * v.y, this * v.z); }
    //Vertex operator/(const Vertex &v) const { return Vertex(x / v.x, y / v.y, z / v.z, 1); }

    double dotProduct(const Direction &v) const { return ((x * v.x + y * v.y + z * v.z)); };

    Direction crossProduct(const Direction &v) const { return Direction(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x); };

    Direction normalize() { return Direction(x / sqrt(x*x + y * y + z * z), y / sqrt(x*x + y * y + z * z), z / sqrt(x*x + y * y + z * z)); };

	double length() { return(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))); };

    void printDirection()
    {
        std::cout << x << " " << y << " " << z << std::endl;
    };

	double x, y, z;
private:
 
};

#endif // !DIRECTION_CPP