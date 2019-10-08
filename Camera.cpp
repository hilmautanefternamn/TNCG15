#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Vertex.cpp"
#include "Ray.cpp"
#include "Pixel.cpp"
#include "Scene.cpp"
#include <vector>
#include <fstream>
#include <cmath>

const double PI = 3.14159265359;

/* Camera contains two instances of Vertex (the eye points) and a variable that
allows you to switch between both eye points.
It contains a 2D array of size 800 � 800. Each element is a Pixel.
Its method render() launches a ray through each pixel one at a time.
The ray is followed through the scene and the radiance we give to the
pixel is computed according to what we learnt in lectures 4 and 5.
Initially and to test your code you follow the ray until it hits the first
triangle and assign the triangle color to the ray. */

class Camera
{
public:
    // default constructor
    Camera()
        : pixelPlane{ 800, std::vector<Pixel>(800) } {};

    void setEye()
    {};

    void render(Scene &s)
    {
        ColorDbl black{ 0.0, 0.0, 0.0 };

        Vertex pointLight{ 5.0, 0.0, 5.0, 1.0 };
		Direction pLightDir;

        // create output file
        int size{ 800 };
		std::ofstream out("out.ppm");
		out << "P3\n" << size << ' ' << size << ' ' << "255\n";

		Vertex pixelPoint;
        double lengthP{ 0.0025 };
        double hlengthP{ lengthP / 2.0 };

        Triangle intersectTri;
        Vertex intrsctPoint;
        Vertex minIntrsctPoint;
        Vertex intrsctShdwPoint;


        // set color of every pixel in the pixelplane
        for (int h = 0; h < size; h++)          // z
        {
            for (int w = size-1; w >= 0; w--)   // y
            {
                pixelPoint = Vertex(0.0, hlengthP + (w*lengthP) - 1.0, 1.0 - hlengthP - (h*lengthP), 1.0);

                // intersection ray eye => triangle
                Ray ray(eye1, pixelPoint);
                double t{ 10000.0 };                // distance between camera and intersection point
                double tMin{ 10000.0 };

                // intersection ray triangle => light
                double st{ 10000.0 };               // distance between light source and intersection point
                double stMin{ 10000.0 };       
			
                // find clostest intersecting triangle to the eye
				for (auto &tri : s.triangles)
				{
					if (tri.rayIntersection(ray, t, intrsctPoint))
					{
						    if (t < tMin)
						    {
                                tMin = t;
                                intersectTri = tri;
                                minIntrsctPoint = intrsctPoint;
						    }
					}
				}

                // check if there are any objects between intersected triangle and light source 
                Ray shadowRay(minIntrsctPoint, pointLight);
				for (auto &tri : s.triangles)
				{
					if (tri.rayIntersection(shadowRay, st, intrsctShdwPoint))
					{
                        // check if t2 is in object (tetra or sphere)
                        // in some cool way..
    
						if (intrsctShdwPoint.z < 4.9 && (intrsctShdwPoint.z - minIntrsctPoint.z) > EPS &&  st < stMin)
						{
                            stMin = st;
						}
					}
				}

				// compute angle between surface normal and light direction
                pLightDir = pointLight - minIntrsctPoint;
                double angle{ acos( (pLightDir.normalize()).dotProduct( intersectTri.getNormal() ) ) };

                // surface is not lit by the light source
                if ( abs(angle) > (PI / 2) )
                {
                    pixelPlane[w][h].color = black;
                }

                // there's an object bewteen intersected triangle and light source => triangle shourld be in shadow
                else if (stMin < pLightDir.length() )
                {                  
                    pixelPlane[w][h].color = intersectTri.color * 0.4;
                }

                // surface is lit & there's no object between it and the light source
                else
                {
                    double spht;
                    Vertex temp;
                    if (s.sph.sphereIntersect(shadowRay, spht, temp))
                    {
                        pixelPlane[w][h].color = intersectTri.color * 0.4;
                    }
                    else
                        pixelPlane[w][h].color = (intersectTri.color*std::abs(cos(angle)));
                }
                    //pixelPlane[w][h].color = intersectTri.color;
                    


                // sphere intersection
                double sphere_t;
                Vertex sphereHit;
                if(s.sph.sphereIntersect(ray, sphere_t, sphereHit))
                {
                    if (sphere_t < tMin)
                    {
                        pLightDir = pointLight - sphereHit;
                        double angle{ acos((pLightDir.normalize()).dotProduct(s.sph.getSphereNormal(sphereHit))) };
                        if (abs(angle) > (PI / 2)) pixelPlane[w][h].color = black;

                        else
                            pixelPlane[w][h].color = s.sph.color*std::abs(cos(angle));
                    }

                    // shadow rays from sphere intersection
                /*    Ray sphereShadow(sphereHit, pointLight);
                    double sphere_st;
                    Vertex sphereShadowHit;
                    if (s.sph.sphereIntersect(sphereShadow, sphere_st, sphereShadowHit))
                    {
                        if(sphere_st < pLightDir.length())
                            pixelPlane[w][h].color = s.sph.color* 0.4;
                    }*/
                }
   
                // write color to output file
				out << pixelPlane[w][h].color;
            }
        }
	};

    int eye; // 1 or 2
    Vertex eye1{ -1.0, 0.0, 0.0, 1.0 };
    Vertex eye2{ -1.0, 0.0, 0.0, 1.0 };
	std::vector<std::vector<Pixel>>pixelPlane;

private:

};

#endif // !CAMERA_CPP