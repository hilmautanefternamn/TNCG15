﻿#ifndef RAY_CPP
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
    Ray() {};

    Ray(const Vertex &s, const Vertex &e)
        : start(s), end(e) {};


    Vertex start, end;
    ColorDbl color;
private:
    //Triangle triEnd;

};

#endif // !RAY_CPP