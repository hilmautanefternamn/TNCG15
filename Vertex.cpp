#ifndef VERTEX_CPP
#define VERTEX_CPP

#include "Direction.cpp"

// Vertex has three spatial coordinates x, y, z and w (for homogeneous coordinates)
class Vertex
{
public:
    // Default constructor
    Vertex() { x = y = z = 0; w = 1; };  

    //  constructor to create vertex from double coordinates
    Vertex(double inX, double inY, double inZ, double inW)
        : x{ inX }, y{ inY }, z{ inZ }, w{ inW } {};

    // math operations
    Direction operator-(const Vertex &v) const { return Direction(x - v.x, y - v.y, z - v.z); };
	Vertex operator+(const Vertex &v) const { return Vertex(x + v.x, y + v.y, z + v.z, 1.0); };
	Vertex operator*(const double d) const { return Vertex(x*d, y*d, z*d, 1); };
	bool operator==(const Vertex &v)const { return (x == v.x && y == v.y && z == v.z); };

    // print coordinates of vertex
    void printVertex() { std::cout << x << " " << y << " " << z << " " << w << std::endl; };

    double x, y, z, w;

private:

};

#endif // !VERTEX_CPP