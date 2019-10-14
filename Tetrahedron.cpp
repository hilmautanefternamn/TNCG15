#ifndef TETRAHEDRON_CPP
#define TETRAHEDORN_CPP

#include "Triangle.cpp"
#include "Vertex.cpp"
#include <vector>

class Tetrahedron
{
public:
    // default constructor
    Tetrahedron() {};

    // constructor to create tetrahedron from four vertices
    Tetrahedron(Vertex _v0, Vertex _v1, Vertex _v2, Vertex _v3, ColorDbl c, surfaceType sT)
        :v0{ _v0 }, v1{ _v1 }, v2{ _v2 }, v3{ _v3 }, color{ c }, sType(sT)
	{
        trianglesTetra.push_back({ v0, v1, v3,  color, sType });       // RS
        trianglesTetra.push_back({ v0, v3, v2,  color, sType });       // LS
        trianglesTetra.push_back({ v2, v3, v1, color, sType });        // back
        trianglesTetra.push_back({ v0, v2, v1,  color, sType });       // bottom
	};

    // compute intersection between a Ray and Triangle in tetrahedron 
    //with the M�ller - Trumbore algorithm
    // arg t = distance from ray.start to intersection point
    // arg Phit = intersection point (vertex)
    bool rayIntersection(Ray &ray, double &t, Vertex &Phit, Direction &normal)
    {
		Vertex tetraHit;
		double tMin = 10000.0;
        bool isHit = false;
        for (auto &tri : trianglesTetra)
        {
			if (tri.rayIntersection(ray, t, tetraHit) && t < tMin) 
			{
				tMin = t;
				isHit = true;
				normal = tri.getNormal();
                Phit = tetraHit;
			}
        }
        return isHit;
    }

	Vertex v0, v1, v2, v3;
    std::vector<Triangle> trianglesTetra;
    ColorDbl color;
	surfaceType sType;
	private:
};

#endif