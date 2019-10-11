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

        Vertex pointLight{ 5.0, 0.0, 4.9, 1.0 };
		Direction pLightDir;

        // create output file
        int size{ 800 };
		std::ofstream out("out.ppm");
		out << "P3\n" << size << ' ' << size << ' ' << "255\n";

		Vertex pixelPoint;
        double lengthP{ 0.0025 };
        double hlengthP{ lengthP / 2.0 };

        Vertex Phit;
        //Vertex minIntrsctPoint;
        //Vertex intrsctShdwPoint;
		ColorDbl color;
		Direction hitNormal;


        // set color of every pixel in the pixelplane
        for (int h = 0; h < size; h++)          // z
        {
            for (int w = size-1; w >= 0; w--)   // y
            {
                pixelPoint = Vertex(0.0, hlengthP + (w*lengthP) - 1.0, 1.0 - hlengthP - (h*lengthP), 1.0);

                // intersection ray: eye => triangle
                Ray ray(eye1, pixelPoint);
                double t = 10000.0;		// distance between camera and intersection point

                // find clostest intersecting triangle to the eye
				s.rayIntersection(ray, t, Phit, color, hitNormal);
				
				// check if there are any objects between intersected triangle and light source 
				Ray shadowRay(Phit, pointLight);
				double st = 10000.0;	// distance between intersection point and point light
				Vertex PhitS;
				ColorDbl colorS;
				Direction hitNormalS;
				s.rayIntersection(shadowRay, st, PhitS, colorS, hitNormalS);
                
             

				// compute angle between surface normal and light direction
				//Phit.printVertex();
                pLightDir = pointLight - Phit;
				//cout << "sr length: " << shadowRay.dir.length() << endl;
                double angle{ acos( (pLightDir.normalize()).dotProduct( hitNormal) ) };

				//cout << "st: " << st << endl;
				//cout << "length: " << pLightDir.length() << endl;

                // surface is not lit by the light source
                if ( abs(angle) > (PI / 2) )
                {
                    pixelPlane[w][h].color = black;
                }

                // there's an object bewteen intersected triangle and light source => triangle should be in shadow
                else if (st < pLightDir.length())
                {                  
                    pixelPlane[w][h].color = color * 0.4;
                }

                // surface is lit & there's no object between it and the light source
                else
                {
                    pixelPlane[w][h].color = (color*std::abs(cos(angle)));
                    //pixelPlane[w][h].color = color;
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