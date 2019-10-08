#ifndef SCENE_CPP
#define SCENE_CPP

#include "Triangle.cpp"
#include "Sphere.cpp"
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
    // default constructor
    Scene() {};

    //void findIntersecRay(Ray arg) {};

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

        ColorDbl white{ 255.0, 255.0, 255.0 };
        ColorDbl red{ 255.0, 0.0, 0.0 };
        ColorDbl blue{ 0.0, 0.0, 255.0 };
        ColorDbl green{ 0.0, 255.0, 0.0 };
        ColorDbl orange{ 255.0, 165.0, 0.0 };
        ColorDbl cyan{ 0.0, 255.0, 255.0 };
        ColorDbl yellow{ 255.0, 255.0, 0.0 };
        ColorDbl grey{ 100.0, 100.0, 100.0 };
        ColorDbl pink{ 255.0, 20.0, 147.0 };

        // floor
        triangles.push_back({ vertices[1], vertices[2], vertices[0], white });
        triangles.push_back({ vertices[1], vertices[3], vertices[2], white });
        triangles.push_back({ vertices[1], vertices[4], vertices[3], white });
        triangles.push_back({ vertices[1], vertices[5], vertices[4], white });
        triangles.push_back({ vertices[1], vertices[6], vertices[5], white });
        triangles.push_back({ vertices[1], vertices[0], vertices[6], white });
        // roof
        triangles.push_back({ vertices[8], vertices[7], vertices[9], white });
        triangles.push_back({ vertices[8], vertices[9], vertices[10], white });
        triangles.push_back({ vertices[8], vertices[10], vertices[11], white });
        triangles.push_back({ vertices[8], vertices[11], vertices[12], white });
        triangles.push_back({ vertices[8], vertices[12], vertices[13], white });
        triangles.push_back({ vertices[8], vertices[13], vertices[7], white });
        // VB
        triangles.push_back({ vertices[2], vertices[7], vertices[0], blue });
        triangles.push_back({ vertices[2], vertices[9], vertices[7], blue });
        // B
        triangles.push_back({ vertices[3], vertices[9], vertices[2], green });
        triangles.push_back({ vertices[3], vertices[10], vertices[9], green });
        // HB
        triangles.push_back({ vertices[4], vertices[10], vertices[3], red });
        triangles.push_back({ vertices[4], vertices[11], vertices[10], blue });
        // HF
        triangles.push_back({ vertices[5], vertices[11], vertices[4], green });
        triangles.push_back({ vertices[5], vertices[12], vertices[11], orange });
        // F
        triangles.push_back({ vertices[6], vertices[12], vertices[5], cyan });
        triangles.push_back({ vertices[6], vertices[13], vertices[12], cyan });
        // VF
        triangles.push_back({ vertices[0], vertices[13], vertices[6], yellow });
        triangles.push_back({ vertices[0], vertices[7], vertices[13], yellow });

        // Tetrahedron
        Vertex v0{ 8.0, 2.0, 0.0, w };
        Vertex v1{ 10.6, 0.5, 0.0, w };
        Vertex v2 { 10.6, 3.5, 0.0, w };
        Vertex v3 { 9.3, 2.0, 2.6, w };

        triangles.push_back({ v0, v1, v3,  pink });     // RS
        triangles.push_back({ v0, v3, v2,  orange });   // LS
        triangles.push_back({v2, v3, v1, green });      // back
        triangles.push_back({ v0, v2, v1,  cyan });     // bottom

        // Sphere
        sph = { Vertex{ 7.0, -2.0, 0.0, 1.0 }, 1.0, blue };
	};

	std::vector<Triangle> triangles;
	Vertex vertices[14];
	Direction normals[8];
    Sphere sph;

    double w{ 1.0 };

private:

};

#endif // !SCENE_CPP