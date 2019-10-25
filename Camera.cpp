#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Vertex.cpp"
#include "Ray.cpp"
#include "Pixel.cpp"
#include "Scene.cpp"
#include <vector>
#include <fstream>
#include <cmath>


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
		
		ColorDbl colorUL;
		ColorDbl colorUR;
		ColorDbl colorLL;
		ColorDbl colorLR;

        // set color of every pixel in the pixelplane
        for (int h = 0; h < size; h++)          // z
        {
			if (h == 200)
				cout << "25%" << endl;
			if (h == 400)
				cout << "50%" << endl;
			if (h == 600)
				cout << "75%" << endl;
			if (h == 799)
				cout << "100%" << endl;

            for (int w = 0; w < size; w++)   // y
            {
				pixelPoint = Vertex(0.0, 1.0 - hlengthP - (w*lengthP), 1.0 - hlengthP - (h*lengthP), 1.0);
				//double randlengthP = ((rand() % 100 + 1) / 100.0)/800.0;     // random double between 0 and 1
				//double randheightP = ((rand() % 100 + 1) / 100.0)/800.0;
				Vertex pixelPointUL = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / 800.0), pixelPoint.z + (((rand() % 100 + 1) / 100.0) / 800.0), 1.0);
				Vertex pixelPointUR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / 800.0), pixelPoint.z + (((rand() % 100 + 1) / 100.0) / 800.0), 1.0);
				Vertex pixelPointLL = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / 800.0), pixelPoint.z - (((rand() % 100 + 1) / 100.0) / 800.0), 1.0);
				Vertex pixelPointLR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / 800.0), pixelPoint.z - (((rand() % 100 + 1) / 100.0) / 800.0), 1.0);

				//cout << "original"; pixelPoint.printVertex();
				//cout << "UL"; pixelPointUL.printVertex();
				//cout << "UR"; pixelPointUR.printVertex();
				//cout << "LL"; pixelPointLL.printVertex();
				//cout << "LR"; pixelPointLR.printVertex();


                // find clostest intersecting triangle to the eye
                Ray ray(eye1, { (pixelPoint - eye1).normalize() });

				Ray rayUL(eye1, { (pixelPointUR - eye1).normalize() });
				Ray rayUR(eye1, { (pixelPointUL - eye1).normalize() });
				Ray rayLL(eye1, { (pixelPointLL - eye1).normalize() });
				Ray rayLR(eye1, { (pixelPointLR - eye1).normalize() });
                double t{};		            // distance between camera and intersection point

                
                // find clostest intersecting triangle to the eye
				double tUL, tUR, tLL, tLR;
				Vertex PhitUL, PhitUR, PhitLL, PhitLR;
				Direction hitNormalUL, hitNormalUR, hitNormalLL, hitNormalLR;

                s.rayIntersection(rayUL, tUL, PhitUL, colorUL, hitNormalUL, 0);
				s.rayIntersection(rayUR, tUR, PhitUR, colorUR, hitNormalUR, 0);
				s.rayIntersection(rayLL, tLL, PhitLL, colorLL, hitNormalLL, 0);
				s.rayIntersection(rayLR, tLR, PhitLR, colorLR, hitNormalLR, 0);
				
				color = (colorUL + colorUR + colorLL + colorLR) / 4.0;
				//cout << color.red << " " << color.green << " " << color.blue << endl;
				color = ColorDbl(floor(color.red), floor(color.green), floor(color.blue));
				//cout << color.red << " " << color.green << " " << color.blue << endl;
				// check if there are any objects between intersected triangle and light source 
                /*Ray shadowRay(Phit, { pointLight - Phit });
				double st = 10000.0;	// distance between intersection point and point light
				
				s.shadowrayIntersection(shadowRay, st, PhitS);
                

                // compute angle between surface normal and light direction
                pLightDir = pointLight - Phit;
                double angle{ acos((pLightDir.normalize()).dotProduct(hitNormal)) };*/

                
                /*--    3 COLOR CASES   --*/
                
              /*  // surface is not lit by the light source
                if (abs(angle) > (PI / 2))
                    pixelPlane[w][h].color = black;

                // there's an object bewteen intersected triangle and light source => triangle should be in shadow
                else if (st < pLightDir.length())
                    pixelPlane[w][h].color = color * 0.4;

                // surface is lit & there's no object between it and the light source
                else
                    pixelPlane[w][h].color = (color*std::abs(cos(angle)));*/
                    //
                /*------------------------*/
				pixelPlane[w][h].color = color;
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