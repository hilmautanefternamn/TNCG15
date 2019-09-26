#ifndef TETRAHEDRON_CPP
#define TETRAHEDORN_CPP

#include "Triangle.cpp"
#include "Vertex.cpp"
#include <vector>

class Tetrahedron
{
	public:
		Tetrahedron() {};

		Tetrahedron(Vertex v0, Vertex v1, Vertex v2, Vertex v3)
			:v0(v0), v1(v1), v2(v2), v3(v3)
		{
		};

		Vertex v0, v1, v2, v3;
		Triangle trianglesTetra[4];
		
	private:
};

#endif