#ifndef RAY_CPP
#define RAY_CPP

#include "Vertex.cpp"
#include "ColorDbl.cpp"
/*Ray has two instances of Vertex, which are the ray�s starting point and end
point. You can put the vertices into a vertex list and use references to
these points in Ray. Ray contains a reference to the triangle on which
the end point is located. The ray color is a ColorDbl.*/

class Ray
{
public:
    // default constructor
    Ray() {};

    // constructor to create ray from start- and end vertex
    Ray(const Vertex &s, const Direction &d)
        : start{ s }, dir{ d }/*, dir{ s - e }*/{};
    
    Vertex start;
    ColorDbl color;
	Direction dir;

private:
  
};

#endif // !RAY_CPP