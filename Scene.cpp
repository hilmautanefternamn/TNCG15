#ifndef SCENE_CPP
#define SCENE_CPP

#include "Triangle.cpp"
#include <vector>
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

	void createScene()
	{
		vertices[0] = Vertex(-3.0, 0.0, -5.0, w);
		vertices[1] = Vertex(5.0, 0.0, -5.0, w);
		vertices[2] = Vertex(0.0, 6.0, -5.0, w);
		vertices[3] = Vertex(10.0, 6.0, -5.0, w);
		vertices[4] = Vertex(13.0, 0.0, -5.0, w);
		vertices[5] = Vertex(10.0, -6.0, -5.0, w);
		vertices[6] = Vertex(0.0, -6.0, -5.0, w);

		vertices[7] = Vertex(-3.0, 0.0, 5.0, w);
		vertices[8] = Vertex(5.0, 0.0, 5.0, w);
		vertices[9] = Vertex(0.0, 6.0, 5.0, w);
		vertices[10] = Vertex(10.0, 6.0, 5.0, w);
		vertices[11] = Vertex(13.0, 0.0, 5.0, w);
		vertices[12] = Vertex(10.0, -6.0, 5.0, w);
		vertices[13] = Vertex(0.0, -6.0, 5.0, w);

		normals[0] = Direction(0.0, 0.0, 1.0);                      // floor
		normals[1] = Direction(0.0, 0.0, -1.0);                     // roof
		normals[2] = Direction(2 / sqrt(5), -1 / sqrt(5), 0.0);     // VB
		normals[3] = Direction(0.0, -1.0, 0.0);                     // B
		normals[4] = Direction(-2 / sqrt(5), -1 / sqrt(5), 0.0);    // HB
		normals[5] = Direction(-2 / sqrt(5), 1 / sqrt(5), 0.0);     // HF
		normals[6] = Direction(0.0, 1.0, 0.0);                      // F
		normals[7] = Direction(2 / sqrt(5), 1 / sqrt(5), 0.0);      // VF

		ColorDbl white = ColorDbl(255.0, 255.0, 255.0);
		ColorDbl red = ColorDbl(255.0, 0.0, 0.0);
		ColorDbl blue = ColorDbl(0.0, 0.0, 255.0);
		ColorDbl green = ColorDbl(0.0, 255.0, 0.0);
		ColorDbl orange = ColorDbl(255.0, 165.0, 0.0);
		ColorDbl cyan = ColorDbl(0.0, 255.0, 255.0);
		ColorDbl yellow = ColorDbl(255.0, 255.0, 0.0);
		ColorDbl grey = ColorDbl(100.0, 100.0, 100.0);

		// floor
		triangles.push_back(Triangle(vertices[1], vertices[2], vertices[0], normals[0], white));
		triangles.push_back(Triangle(vertices[1], vertices[3], vertices[2], normals[0], white));
		triangles.push_back(Triangle(vertices[1], vertices[4], vertices[3], normals[0], white));
		triangles.push_back(Triangle(vertices[1], vertices[5], vertices[4], normals[0], white));
		triangles.push_back(Triangle(vertices[1], vertices[6], vertices[5], normals[0], white));
		triangles.push_back(Triangle(vertices[1], vertices[0], vertices[6], normals[0], white));
		// roof
		triangles.push_back(Triangle(vertices[8], vertices[9], vertices[7], normals[1], grey));
		triangles.push_back(Triangle(vertices[8], vertices[10], vertices[9], normals[1], grey));
		triangles.push_back(Triangle(vertices[8], vertices[11], vertices[10], normals[1], grey));
		triangles.push_back(Triangle(vertices[8], vertices[12], vertices[11], normals[1], grey));
		triangles.push_back(Triangle(vertices[8], vertices[13], vertices[12], normals[1], grey));
		triangles.push_back(Triangle(vertices[8], vertices[7], vertices[13], normals[1], grey));
		// VB
		triangles.push_back(Triangle(vertices[2], vertices[7], vertices[0], normals[2], blue));
		triangles.push_back(Triangle(vertices[2], vertices[9], vertices[7], normals[2], blue));
		// B
		triangles.push_back(Triangle(vertices[3], vertices[9], vertices[2], normals[3], green));
		triangles.push_back(Triangle(vertices[3], vertices[10], vertices[9], normals[3], green));
		// HB
		triangles.push_back(Triangle(vertices[4], vertices[10], vertices[3], normals[4], red));
		triangles.push_back(Triangle(vertices[4], vertices[11], vertices[10], normals[4], red));
		// HF
		triangles.push_back(Triangle(vertices[5], vertices[11], vertices[4], normals[5], orange));
		triangles.push_back(Triangle(vertices[5], vertices[12], vertices[11], normals[5], orange));
		// F
		triangles.push_back(Triangle(vertices[6], vertices[12], vertices[5], normals[6], cyan));
		triangles.push_back(Triangle(vertices[6], vertices[13], vertices[12], normals[6], cyan));
		// VF
		triangles.push_back(Triangle(vertices[0], vertices[13], vertices[6], normals[7], yellow));
		triangles.push_back(Triangle(vertices[0], vertices[7], vertices[13], normals[7], yellow));

		// Tetrahedron
		Direction dummy(0.0, 0.0, 0.0);
		ColorDbl pink(255.0, 20.0, 147.0);

		triangles.push_back(Triangle(Vertex(9.3, 2.0, 2.6, 1.0), Vertex(10.6, 0.5, 0.0, 1.0), Vertex(8.0, 2.0, 0.0, 1.0), dummy, pink));    // F
		triangles.push_back(Triangle(Vertex(10.6,3.5,0.0,1.0), Vertex(8.0, 2.0, 0.0, 1.0), Vertex(9.3 ,2.0, 2.6, 1.0), dummy, pink));       // L
		triangles.push_back(Triangle(Vertex(10.6, 3.5, 0.0, 1.0), Vertex(9.3, 2.0, 2.6, 1.0), Vertex(10.6, 0.5, 0.0, 1.0), dummy, pink));   // R
		triangles.push_back(Triangle(Vertex(10.6, 3.5, 0.0, 1.0), Vertex(10.6, 0.5, 0.0, 1.0), Vertex(8.0, 2.0, 0.0, 1.0), dummy, pink));   // B
	};

	std::vector<Triangle> triangles;
	Vertex vertices[14];
	Direction normals[8];

	double w = 1;

private:

};

#endif // !SCENE_CPP