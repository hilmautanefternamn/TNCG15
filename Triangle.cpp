#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "Vertex.cpp"
#include "Ray.cpp"
#include "ColorDbl.cpp"

const double EPS = 1e-4;

/*The triangle is defined by three objects of the class Vertex.
The Triangle has a color, which we represent by an instance of ColorDbl.
The triangle�s normal direction is stored in an instance of Direction.
It has a method rayIntersection(Ray arg) that computes the intersection
between a Ray and the Triangle with the Möller-Trumbore algorithm.
*/
class Triangle
{
public:
    Triangle() {};

    Triangle(Vertex inv0, Vertex inv1, Vertex inv2, Direction n, ColorDbl c)
		:v0(inv0), v1(inv1), normal(n), v2(inv2), color(c) {
		normal = this->getNormal();
		//std::cout << normal.x << "," << normal.y <<"," << normal.z << endl;
	};

    //computes the intersection between a Ray and the Triangle with the M�ller - Trumbore algorithm
    bool rayIntersection(const Ray &ray, double &t, Vertex &Phit)
    {
        Direction T = ray.start - v0;
        Direction E1 = v1 - v0;
        Direction E2 = v2 - v0;
        Direction D = ray.end - ray.start;
        Direction P = D.crossProduct(E2);
        Direction Q = T.crossProduct(E1);

		double a = E1.dotProduct(P);

		if (a > -EPS && a < EPS) 
			return false;
	
		double u, v;
		u = P.dotProduct(T) / a; if (u < 0.0 || u > 1.0) return false;
		v = Q.dotProduct(D) / a; if (v < 0.0 || u+v > 1.0) return false;

        t = Q.dotProduct(E2) / P.dotProduct(E1);

		if (t > EPS) {
			Phit = ray.start + Vertex(t*D.x,t*D.y,t*D.z, 1.0);
			//PhitT = ray.start + Vertex(t*D.x, t*D.y, t*D.z, 1.0);

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
	
	Direction getNormal()
	{
		Direction v0d = v1 - v0;
		Direction v1d = v2 - v0;
		Direction normal = v0d.crossProduct(v1d);
		

		return(normal.normalize());
	}
	Vertex PhitT;
	Vertex v0, v1, v2;
	Direction normal;
	ColorDbl color;

private:
  

};

#endif // !TRIANGLE_CPP