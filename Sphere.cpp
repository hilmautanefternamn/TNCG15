#include "Ray.cpp"
#include <cmath>

class Sphere
{
public:
    // default constructor
    Sphere() {};
    
    // constructor to create sphere from center point, radius and color
    Sphere(Vertex c, double r, ColorDbl co, surfaceType sType)
        :center{ c }, radius{ r }, color{ co },sType(sType) {};
    
    bool sphereIntersect(const Ray &ray, double &t, Vertex &Phit) 
    { 
        Vertex o = ray.start;   // origin
        Direction l = ray.dir;
		l = l.normalize();
        double a = l.dotProduct(l);
        double b = (l * 2).dotProduct(o - center);
        double c = (o - center).dotProduct(o - center) - (radius * radius);

        double d = (b / 2)*(b / 2) - (a*c);

        if (d < 0) return false;

        double d1 = -(b / 2) + sqrt(d);
        double d2 = -(b / 2) - sqrt(d);

		if (abs(d1) < 0.01 || abs(d2) < 0.01) return false;

        t = (d1 < d2) ? d1 : d2;
        Phit = o + Vertex(l.x, l.y, l.z, 1.0)*t;

        return true; 
    }

    Direction getSphereNormal(Vertex &Phit)
    {
        return Direction( ((Phit-center)/radius).normalize() );
    }

    Vertex center;
    double radius;
    ColorDbl color;
	surfaceType sType;

};
