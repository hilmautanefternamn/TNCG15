#ifndef SCENE_CPP
#define SCENE_CPP

#include "Tetrahedron.cpp"
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

    // Triangle soup
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
        ColorDbl red{ 120, 20, 20 };
        ColorDbl blue{ 20, 25, 110 };
        ColorDbl orange{ 255.0, 165.0, 0.0 };
        ColorDbl cyan{ 0.0, 255.0, 255.0 };
        ColorDbl pink{ 255.0, 20.0, 147.0 };
        
        // wall colors
        ColorDbl purple{ 130, 120, 145 };
        ColorDbl green{ 23, 61, 42 };
        ColorDbl yellow{ 200, 145, 70 };
        ColorDbl grey{ 180, 165, 145 };
        ColorDbl brown{ 95, 70, 20 };
        ColorDbl granite{ 100, 115, 90 };

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
        triangles.push_back({ vertices[2], vertices[7], vertices[0], granite });
        triangles.push_back({ vertices[2], vertices[9], vertices[7], granite });
        // B
        triangles.push_back({ vertices[2], vertices[10], vertices[9], yellow });
        triangles.push_back({ vertices[2], vertices[3], vertices[10], yellow });
        // HB
        triangles.push_back({ vertices[4], vertices[10], vertices[3], purple });
        triangles.push_back({ vertices[4], vertices[11], vertices[10], green });
        // HF
        triangles.push_back({ vertices[4], vertices[12], vertices[11], green });
        triangles.push_back({ vertices[4], vertices[5], vertices[12], grey });
        // F
        triangles.push_back({ vertices[5], vertices[13], vertices[12], brown });
        triangles.push_back({ vertices[5], vertices[6], vertices[13], brown });
        // VF
        triangles.push_back({ vertices[0], vertices[13], vertices[6], red });
        triangles.push_back({ vertices[0], vertices[7], vertices[13], red });

        // Tetrahedron
        Vertex v0{ 8.0, 2.0, 0.0, w };
        Vertex v1{ 10.6, 0.5, 0.0, w };
        Vertex v2 { 10.6, 3.5, 0.0, w };
        Vertex v3 { 9.3, 2.0, 2.6, w };

        tetra = { v0, v1, v2, v3, red };

        // Sphere
        sph = { Vertex{ 7.0, -2.0, 0.0, 1.0 }, w, blue };
	};

    // find intersections between importance ray from eye and triangles, tetrahedrons and speheres 
	void rayIntersection(Ray &ray, double &t, Vertex &Phit, ColorDbl &color, Direction &normal)
	{
        // find intersections with scene walls, roof and floor
		double tTri;
		Vertex PhitTri;

		for (auto &tri : triangles)
		{
			if (tri.rayIntersection(ray, tTri, PhitTri))
			{
					color = tri.color;
					normal = tri.getNormal();
					t = tTri;
					Phit = PhitTri;
			}
		}

        // find intersections with tetrahedron
		double tTetra;
		Vertex PhitTetra;
		Direction normalTetra;

		if(tetra.rayIntersection(ray, tTetra, PhitTetra, normalTetra))
		{
			if (tTetra < t)
            {
				color = tetra.color;
				normal = normalTetra;
				Phit = PhitTetra;
				t = tTetra;
			}
		}

        // find intersections with sphere
		double sphere_t;
		Vertex sphereHit;
		if (sph.sphereIntersect(ray, sphere_t, sphereHit))
		{
			if (sphere_t < t)
			{
				color = sph.color;
				normal = sph.getSphereNormal(sphereHit);
				Phit = sphereHit;
				t = sphere_t;
			}
		}
	};

    // find wheather or not the intersected point is in shadow 
    bool shadowRayIntersection(Ray &ray, double &t)
    {
        // find intersections with tetrahedron
        double tTetra;
        Vertex PhitTetra;
        Direction normalTetra;

        if (tetra.rayIntersection(ray, tTetra, PhitTetra, normalTetra) && tTetra < t)
            return true;
            
        // find intersections with sphere
        double sphere_t;
        Vertex sphereHit;
        if (sph.sphereIntersect(ray, sphere_t, sphereHit) && sphere_t < t)
            return true;


        return false;
    };


	std::vector<Triangle> triangles;
	Vertex vertices[14];

    Sphere sph;
    Tetrahedron tetra;

private:
    double w{ 1.0 };
};

#endif // !SCENE_CPP