#ifndef SCENE_CPP
#define SCENE_CPP


#include "Triangle.cpp"

/*Scene contains instances of Triangle. We use one Scene object that
consists of 24 instances of Triangle. Scene objects are closed.
The triangles of the floor and the ceiling should be white. Each of the 6
walls has a different color.
It should have a method that determines which triangle is intersected by
the Ray arg by calling successively the rayIntersection(Ray arg) method
of each Triangle. It then passes references to the triangle and the
intersection point to the Ray arg*/
class Scene
{
public:
    Scene() {};
    void findIntersecRay(Ray arg) {};
private:
    Triangle triangles[24]{};
};

#endif // !SCENE_CPP