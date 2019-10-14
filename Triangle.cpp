﻿#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "Vertex.cpp"
#include "Ray.cpp"
#include "ColorDbl.cpp"

const double EPS = 1e-3;

/*The triangle is defined by three objects of the class Vertex.
The Triangle has a color, which we represent by an instance of ColorDbl.
The triangle�s normal direction is stored in an instance of Direction.
It has a method rayIntersection(Ray arg) that computes the intersection
between a Ray and the Triangle with the Möller-Trumbore algorithm.*/

class Triangle
{
public:
    // default constructor
    Triangle() {};

    // constructor to create triangle from 3 vertices and a color
    Triangle(Vertex inv0, Vertex inv1, Vertex inv2, ColorDbl c, surfaceType sType)
        :v0{ inv0 }, v1{ inv1 }, v2{ inv2 }, color{ c }, sType(sType)
    {
        normal = { this->getNormal() };
        normal.printDirection();
    };

    //computes the intersection between a Ray and the Triangle with the Möller - Trumbore algorithm
    bool rayIntersection(const Ray &ray, double &t, Vertex &Phit)
    {
        Direction T{ ray.start - v0 };
        Direction E1{ v1 - v0 };
        Direction E2{ v2 - v0 };
        Direction D = ray.dir;
        D.normalize();
        Direction P{ D.crossProduct(E2) };
        Direction Q{ T.crossProduct(E1) };

        double a{ E1.dotProduct(P) };

		if (a > -EPS && a < EPS) 
			return false;
	
        double u{}, v{};
        u = { P.dotProduct(T) / a };   if (u < 0.0 || u > 1.0) return false;
        v = { Q.dotProduct(D) / a };   if (v < 0.0 || u + v > 1.0) return false;
		
        t = { Q.dotProduct(E2) / a };
		
			if (t > EPS && t < 1000000.0)
			{
				Phit = { ray.start + Vertex(t*D.x, t*D.y, t*D.z, 1.0) };
				return true;
			}
		
		return false;
    };

	void printTriangle()
	{
		std::cout << v0.x << " " << v0.y << " " << v0.z << std::endl;
		std::cout << v1.x << " " << v1.y << " " << v1.z << std::endl;
		std::cout << v2.x << " " << v2.y << " " << v2.z << std::endl;
	};
	
    // normalized normal of triangle
	Direction getNormal()
	{
        Direction d0{ v1 - v0 };
        Direction d1{ v2 - v0 };
        Direction normal{ d0.crossProduct(d1) };
	
		return Direction(normal.normalize());
	}

	Vertex v0, v1, v2;
	Direction normal;
	ColorDbl color;
	surfaceType sType;

private:
  

};

#endif // !TRIANGLE_CPP