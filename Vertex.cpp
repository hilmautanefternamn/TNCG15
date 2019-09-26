#ifndef VERTEX_CPP
#define VERTEX_CPP

#include "Direction.cpp"

// Vertex has three spatial coordinates x, y, z and w (for homogeneous coordinates)
class Vertex
{
public:
    Vertex() { x = y = z = 0; w = 1; };  // Default constructor

    Vertex(double inX, double inY, double inZ, double inW)
        : x(inX), y(inY), z(inZ), w(inW) {};

    Direction operator-(const Vertex &v) const { return Direction(x - v.x, y - v.y, z - v.z); };

    void printVertex()
    {
        std::cout << x << " " << y << " " << z << " " << w << std::endl;
    };

    double x, y, z, w;

private:

};

#endif // !VERTEX_CPP