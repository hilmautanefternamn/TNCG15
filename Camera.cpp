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
        
        // to the pixel plane
		Vertex pixelPoint;
        double lengthP{ 0.0025 };
        double hlengthP{ lengthP / 2.0 };
		
        // Ray to find intersections
        Vertex Phit;
		ColorDbl color;
		Direction hitNormal;
		Vertex PhitS;
		

        // set color of every pixel in the pixelplane
        for (int h = 0; h < size; h++)          // z
        {
            for (int w = size - 1; w >= 0; w--)   // y
            {
                pixelPoint = Vertex(0.0, hlengthP + (w*lengthP) - 1.0, 1.0 - hlengthP - (h*lengthP), 1.0);

                // find clostest intersecting triangle to the eye
				Direction rayD = pixelPoint - eye1;
                Ray ray(eye1, rayD);
                double t{};		            // distance between camera and intersection point


                // find clostest intersecting triangle to the eye
				s.rayIntersection(ray, t, Phit, color, hitNormal);
				
				
				// check if there are any objects between intersected triangle and light source 
                Direction srayD = pointLight - Phit;
                Ray shadowRay(Phit, srayD);
				double st = 10000.0;	// distance between intersection point and point light
				
				s.shadowrayIntersection(shadowRay, st, PhitS);
                

                // compute angle between surface normal and light direction
                pLightDir = pointLight - Phit;
                double angle{ acos((pLightDir.normalize()).dotProduct(hitNormal)) };


    //--------------------------------------//
                
                Vertex prevHit{ eye1 };
        // if: tetraintersect || sphereintersect
                
				// to go in some recursive function somewhere
                // emitt reflected and refracted ray from Phit with less importance than incoming ray
                Direction I { (Phit - prevHit).normalize() };       // incoming ray
                Direction N { hitNormal };                          // normal of intersected surface
                double N_dot_I = N.dotProduct(I);
                double n1 { 1 };     // air
                double n2 { 1.5 };   // glass
                double n { n1 / n2 };
                // reflected direction
                Direction R { (I - N * 2 * (N_dot_I)).normalize() };  
                Ray dirR{ Phit, R };

                // refracted direction
                Direction T { (I*n + N*( -n*(N_dot_I) - sqrt(1 - n*n*(1 - N_dot_I*N_dot_I ) ) )).normalize() };  
                Ray dirT{ Phit, T };
                
                // shoot rays in direction R/T and keep reflecting/refracting when intersecting
                // until a diffuse surface is hit [wall, roof or floor] 
                // return color of hit diffuse surface to assign to current pixel in pixel plane


        // else: base case: intersection with diffuse surface [wall, roof or floor]
                // return color of surface

    //--------------------------------------//

                
                /*--    3 COLOR CASES   --*/
                
                // surface is not lit by the light source
                if ( abs(angle) > (PI / 2) )
                    pixelPlane[w][h].color = black;
           
                // there's an object bewteen intersected triangle and light source => triangle should be in shadow
                else if ( st < pLightDir.length() )
                    pixelPlane[w][h].color = color * 0.4;

                // surface is lit & there's no object between it and the light source
                else
                    pixelPlane[w][h].color = (color*std::abs(cos(angle)));

                /*------------------------*/

                // write color to output file
				out << pixelPlane[w][h].color;
            }
        }
	};

    Vertex eye1{ -1.0, 0.0, 0.0, 1.0 };
    Vertex eye2{ -1.0, 0.0, 0.0, 1.0 };
	std::vector<std::vector<Pixel>>pixelPlane;

private:

};

#endif // !CAMERA_CPP