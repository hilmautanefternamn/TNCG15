#ifndef SCENE_CPP
#define SCENE_CPP

#include "Tetrahedron.cpp"
#include "Sphere.cpp"
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

const double PI = 3.14159265359;

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
        triangles.push_back({ vertices[1], vertices[2], vertices[0], white, diffuse });
        triangles.push_back({ vertices[1], vertices[3], vertices[2], white, diffuse });
        triangles.push_back({ vertices[1], vertices[4], vertices[3], white, diffuse });
        triangles.push_back({ vertices[1], vertices[5], vertices[4], white, diffuse });
        triangles.push_back({ vertices[1], vertices[6], vertices[5], white, diffuse });
        triangles.push_back({ vertices[1], vertices[0], vertices[6], white, diffuse });
        // roof
        triangles.push_back({ vertices[8], vertices[7], vertices[9], white, diffuse });
        triangles.push_back({ vertices[8], vertices[9], vertices[10], white, diffuse });
        triangles.push_back({ vertices[8], vertices[10], vertices[11], white, diffuse });
        triangles.push_back({ vertices[8], vertices[11], vertices[12], white, diffuse });
        triangles.push_back({ vertices[8], vertices[12], vertices[13], white, diffuse });
        triangles.push_back({ vertices[8], vertices[13], vertices[7], white, diffuse });
        // VB
        triangles.push_back({ vertices[2], vertices[7], vertices[0], granite, diffuse });
        triangles.push_back({ vertices[2], vertices[9], vertices[7], granite, diffuse });
        // B
        triangles.push_back({ vertices[2], vertices[10], vertices[9], yellow, diffuse });
        triangles.push_back({ vertices[2], vertices[3], vertices[10], yellow, diffuse });
        // HB
        triangles.push_back({ vertices[4], vertices[10], vertices[3], purple, diffuse });
        triangles.push_back({ vertices[4], vertices[11], vertices[10], green, diffuse });
        // HF
        triangles.push_back({ vertices[4], vertices[12], vertices[11], green, diffuse });
        triangles.push_back({ vertices[4], vertices[5], vertices[12], grey, diffuse });
        // F
        triangles.push_back({ vertices[5], vertices[13], vertices[12], brown, diffuse });
        triangles.push_back({ vertices[5], vertices[6], vertices[13], brown, diffuse });
        // VF
        triangles.push_back({ vertices[0], vertices[13], vertices[6], red, diffuse });
        triangles.push_back({ vertices[0], vertices[7], vertices[13], red, diffuse });

        // Tetrahedron
        Vertex v0 { 5.0, 2.0, 0.0, w };
        Vertex v1 { 7.6, 0.5, 0.0, w };
        Vertex v2 { 7.6, 3.5, 0.0, w };
        Vertex v3 { 6.3, 2.0, 2.6, w };

        tetra = { v0, v1, v2, v3, red, reflective};

        // Sphere
        sph = { Vertex{ 5.0, -2.0, 0.0, 1.0 }, w, blue, reflective };
		sph2 = { Vertex{ 3, 0, -2.0, 1.0 }, 0.5, red, diffuse };
	};

    // find intersections between importance ray from eye and triangles, tetrahedrons and speheres 
	ColorDbl rayIntersection(Ray &ray, double &t, Vertex &Phit, ColorDbl &color, Direction &normal, int depth)
	{
		int maxDepth = 3;
		bool diffuseHit = false;

		Vertex pointLight{ 5.0, 0.0, 4.9, 1.0 };
        surfaceType sType = diffuse;
        
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
					sType = tri.sType;

					diffuseHit = true;
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
				sType = tetra.sType;

				diffuseHit = false;

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
				sType = sph.sType;

				diffuseHit = false;

			}
		}
		double sphere_t2;
		Vertex sphereHit2;
		if (sph2.sphereIntersect(ray, sphere_t2, sphereHit2))
		{
			if (sphere_t2 < t)
			{
				color = sph2.color;
				normal = sph2.getSphereNormal(sphereHit2);
				Phit = sphereHit2;
				t = sphere_t2;
				sType = sph2.sType;

				diffuseHit = false;

			}
		}

		Ray shadowRay(Phit, { pointLight - Phit });
		double st = 10000.0;	// distance between intersection point and point light
		Vertex PhitS;
		shadowrayIntersection(shadowRay, st, PhitS);
		Direction pLightDir = pointLight - Phit;

		// compute angle between surface normal and light direction
		
		

        // Perfect reflections for reflective surfaces
        if (sType == reflective)
		{
			// emitt reflected and refracted ray from Phit with less importance than incoming ray
			Direction I{ ray.dir.normalize() };            // incoming ray
			Direction N{ normal };                                  // normal of intersected surface
			double N_dot_I = N.dotProduct(I);
				
            // reflected direction
			Direction R{ ( I - N*(2 * (N_dot_I)) ).normalize() };
			Ray reflectedRay{ Phit, R };


			color = rayIntersection(reflectedRay, t, Phit, color, normal, depth);
			
            // refracted direction
            /*double n1{ 1 };     // air
            double n2{ 1.5 };   // glass
            double n{ n1 / n2 };
			Direction T{ (I*n + N*(-n*(N_dot_I)-sqrt(1 - n*n*(1 - N_dot_I*N_dot_I)))).normalize() };
			Ray refractedRay{ Phit, T };*/
		}

        // Monte Carlo for diffuse surfaces
        else
        {
			pLightDir = pointLight - Phit;
			double angle{ acos((pLightDir.normalize()).dotProduct(normal)) };
			if (abs(angle) > (PI / 2))
			{
				color = ColorDbl(0.0, 0.0, 0.0);
			}
			else
			{
				color = (color*std::abs(cos(angle)));
			}

			if (st < pLightDir.length())
			{
				color = color * 0.8;
			}
			
			Ray ray1 = ray;
			double t1 = t;
			Vertex Phit1 = Phit;
			ColorDbl color1 = color;
			Direction normal1 = normal;
		

			//color1 = color / 255.0;

			// shoot ray to get color of close area
			
			if (depth < maxDepth)
			{
				depth++;


				Ray diffuseRay = diffuseReflector(ray, Phit, normal, diffuseHit);
				color = color + rayIntersection(diffuseRay, t1, Phit1, color1, normal1, depth);
				//rayIntersection(out, t, Phit, color, normal, depth);
				//color = rayIntersection(diffuseRay, t, Phit, color, normal, depth);
			}

		
			//color = color*255.0;
			// surface is not lit by the light source
        }

		/*--    3 COLOR CASES   --*/

	
		// there's an object bewteen intersected triangle and light source => triangle should be in shadow
		
		// surface is lit & there's no object between it and the light source
		

		//cout << color.red << " " << color.green << " " << color.blue << endl;

		return color;

	};

    // danne deleted my comment
	void shadowrayIntersection(Ray &ray, double &t, Vertex &Phit)
	{
		double tTetra;
		Vertex PhitTetra;
		Direction normalTetra;

		if (tetra.rayIntersection(ray, tTetra, PhitTetra, normalTetra))
		{
			if (tTetra < t)
			{
				Phit = PhitTetra;
				t = tTetra;
			}
		}

		double sphere_t;
		Vertex sphereHit;
		if (sph.sphereIntersect(ray, sphere_t, sphereHit))
		{
			if (sphere_t < t)
			{
				Phit = sphereHit;
				t = sphere_t;
			}
		}
		double sphere_t2;
		Vertex sphereHit2;
		if (sph2.sphereIntersect(ray, sphere_t2, sphereHit2))
		{
			if (sphere_t2 < t)
			{
				Phit = sphereHit2;
				t = sphere_t2;
			}
		}
	};

	Ray diffuseReflector(Ray &ray, Vertex &Phit, Direction &normal, bool &wallHit)
	{
		// create local coordinate system around intersection point Phit
		Direction i{ ray.dir.normalize() };                         // incoming ray in Global Coordinates
		Direction z{ normal };                                      // Z = normal of Phit                                          
		Direction x{ (i - (z * (i.dotProduct(z)))).normalize() };     // X = part of incoming ray orthogonal to Z
		Direction y{ (((z)).crossProduct(x*-1)).normalize() };          // Y = X.crossProduct(Z); transform to local system
		
																		// transfer coordinate system to glm vectors
		glm::vec3 I(i.x, i.y, i.z);                           // incoming in global coords
		glm::vec3 X(x.x, x.y, x.z);                                 // X-axis
		glm::vec3 Y(y.x, y.y, y.z);                                 // Y-axis
		glm::vec3 Z(z.x, z.y, z.z);									// Z-axis
		
		glm::vec3 vecPhit(Phit.x, Phit.y, Phit.z);
																	// generate random azimuth and inclination angle
		double _x = (rand() % 100 + 1) / 100.0;     // random double between 0 and 1
		double _y = (rand() % 100 + 1) / 100.0;     // random double between 0 and 1

		double theta{ asin(sqrt(_y)) };
		double phi{ 2.0 * PI *_x };

		glm::vec3 dir1 = -I;
		
		// rotate incoming direction with random angles to get outgoing direction
	
		dir1 = glm::normalize(glm::rotate(dir1, (float)phi, Z));
		dir1 = glm::normalize(glm::rotate(dir1, (float)theta, Y));


		dir1 = glm::vec3(vecPhit + dir1);

		Direction outDir{ dir1.x, dir1.y, dir1.z };

		if (wallHit == true)
		{
			outDir = outDir*-1;
		}

		Ray out{ Phit,  outDir };

		return out;
	};


	std::vector<Triangle> triangles;
	Vertex vertices[14];

    Sphere sph;
	Sphere sph2;
    Tetrahedron tetra;

private:
    double w{ 1.0 };
};

#endif // !SCENE_CPP