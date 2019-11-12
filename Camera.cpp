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

        Vertex pointLight{ 5.0, 0.0, 5.0, 1.0 };
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
			if (h == size*0.25)
				cout << "25%" << endl;
			if (h == size*0.5)
				cout << "50%" << endl;
			if (h == size*0.75)
				cout << "75%" << endl;
			if (h == size-1)
				cout << "100%" << endl;

            for (int w = 0; w < size; w++)   // y
            {
				pixelPoint = Vertex(0.0, 1.0 - hlengthP - (w*lengthP), 1.0 - hlengthP - (h*lengthP), 1.0);
				//double randlengthP = ((rand() % 100 + 1) / 100.0)/800.0;     // random double between 0 and 1
				//double randheightP = ((rand() % 100 + 1) / 100.0)/800.0;
				//4 rays per pixel
				double sizefactor = 800.0;
				
				Vertex pixelPointUL = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / sizefactor), pixelPoint.z + (((rand() % 100 + 1) / 100.0) / sizefactor), 1.0);
				Vertex pixelPointUR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / sizefactor), pixelPoint.z + (((rand() % 100 + 1) / 100.0) / sizefactor), 1.0);
				Vertex pixelPointLL = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / sizefactor), pixelPoint.z - (((rand() % 100 + 1) / 100.0) / sizefactor), 1.0);
				Vertex pixelPointLR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / sizefactor), pixelPoint.z - (((rand() % 100 + 1) / 100.0) / sizefactor), 1.0);
				 Ray ray(eye1, { (pixelPoint - eye1).normalize() });

				Ray rayUL(eye1, { (pixelPointUL - eye1).normalize() });
				Ray rayUR(eye1, { (pixelPointUR - eye1).normalize() });
				Ray rayLL(eye1, { (pixelPointLL - eye1).normalize() });
				Ray rayLR(eye1, { (pixelPointLR - eye1).normalize() });
                double t{};		            // distance between camera and intersection point

                
                // find clostest intersecting triangle to the eye
				double tUL, tUR, tLL, tLR;
				Vertex PhitUL, PhitUR, PhitLL, PhitLR;
				Direction hitNormalUL, hitNormalUR, hitNormalLL, hitNormalLR;
				ColorDbl colorUL, colorUR, colorLL, colorLR;

				colorUL = s.rayIntersection(rayUL, tUL, PhitUL, colorUL, hitNormalUL, 0);
				colorUR = s.rayIntersection(rayUR, tUR, PhitUR, colorUR, hitNormalUR, 0);
				colorLL = s.rayIntersection(rayLL, tLL, PhitLL, colorLL, hitNormalLL, 0);
				colorLR = s.rayIntersection(rayLR, tLR, PhitLR, colorLR, hitNormalLR, 0);
				
				color = (colorUL + colorUR + colorLL + colorLR);
				//cout << color.red << "  " << color.green << "  " << color.blue << endl;
				color = ColorDbl(floor(color.red), floor(color.green), floor(color.blue));
				

				//9 rays per pixel
				/*Vertex pixelPointUL = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / 800.0)+hlengthP, pixelPoint.z + (((rand() % 100 + 1) / 100.0) / 800.0)+hlengthP, 1.0);
				Vertex pixelPointUM = Vertex(0.0, 1.0 - hlengthP - (w*lengthP), pixelPoint.z + (((rand() % 100 + 1) / 100.0) / 800.0)+hlengthP, 1.0);
				Vertex pixelPointUR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / 800.0)-hlengthP, pixelPoint.z + (((rand() % 100 + 1) / 100.0) / 800.0)+hlengthP, 1.0);

				Vertex pixelPointML = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / 800.0)+hlengthP, 1.0 - hlengthP - (h*lengthP), 1.0);
				Vertex pixelPointMM = Vertex(0.0, 1.0 - hlengthP - (w*lengthP), 1.0 - hlengthP - (h*lengthP), 1.0);
				Vertex pixelPointMR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / 800.0)-hlengthP, 1.0 - hlengthP - (h*lengthP), 1.0);

				Vertex pixelPointLL = Vertex(0.0, pixelPoint.y + (((rand() % 100 + 1) / 100.0) / 800.0)+hlengthP, pixelPoint.z - (((rand() % 100 + 1) / 100.0) / 800.0)-hlengthP, 1.0);
				Vertex pixelPointLM = Vertex(0.0, 1.0 - hlengthP - (w*lengthP), pixelPoint.z - (((rand() % 100 + 1) / 100.0) / 800.0)-hlengthP, 1.0);
				Vertex pixelPointLR = Vertex(0.0, pixelPoint.y - (((rand() % 100 + 1) / 100.0) / 800.0)-hlengthP, pixelPoint.z - (((rand() % 100 + 1) / 100.0) / 800.0)-hlengthP, 1.0);
				//cout << "original"; pixelPoint.printVertex();
				//cout << "UL"; pixelPointUL.printVertex();
				//cout << "UR"; pixelPointUR.printVertex();
				//cout << "LL"; pixelPointLL.printVertex();
				//cout << "LR"; pixelPointLR.printVertex();


                // find clostest intersecting triangle to the eye
                Ray ray(eye1, { (pixelPoint - eye1).normalize() });

				Ray rayUL(eye1, { (pixelPointUL - eye1).normalize() });
				Ray rayUM(eye1, { (pixelPointUM - eye1).normalize() });
				Ray rayUR(eye1, { (pixelPointUR - eye1).normalize() });

				Ray rayML(eye1, { (pixelPointML - eye1).normalize() });
				Ray rayMM(eye1, { (pixelPointMM - eye1).normalize() });
				Ray rayMR(eye1, { (pixelPointMR - eye1).normalize() });

				Ray rayLL(eye1, { (pixelPointLL - eye1).normalize() });
				Ray rayLM(eye1, { (pixelPointLM - eye1).normalize() });
				Ray rayLR(eye1, { (pixelPointLR - eye1).normalize() });
	
                double t{};		            // distance between camera and intersection point

                
                // find clostest intersecting triangle to the eye
				double tUL, tUM, tUR, tML,tMM,tMR,tLL,tLM,tLR;
				Vertex PhitUL, PhitUM, PhitUR, PhitML, PhitMM, PhitMR, PhitLL, PhitLM, PhitLR;
				Direction hitNormalUL, hitNormalUM, hitNormalUR, hitNormalML, hitNormalMM, hitNormalMR, hitNormalLL, hitNormalLM, hitNormalLR;
				ColorDbl colorUL, colorUM, colorUR, colorML, colorMM, colorMR, colorLL, colorLM, colorLR;

                s.rayIntersection(rayUL, tUL, PhitUL, colorUL, hitNormalUL, 0);
				s.rayIntersection(rayUM, tUM, PhitUM, colorUM, hitNormalUM, 0);
				s.rayIntersection(rayUR, tUR, PhitUR, colorUR, hitNormalUR, 0);

				s.rayIntersection(rayML, tML, PhitML, colorML, hitNormalML, 0);
				s.rayIntersection(rayMM, tMM, PhitMM, colorMM, hitNormalMM, 0);
				s.rayIntersection(rayMR, tMR, PhitMR, colorMR, hitNormalMR, 0);

				s.rayIntersection(rayLL, tLL, PhitLL, colorLL, hitNormalLL, 0);
				s.rayIntersection(rayLM, tLM, PhitLM, colorLM, hitNormalLM, 0);
				s.rayIntersection(rayLR, tLR, PhitLR, colorLR, hitNormalLR, 0);
			
				
				color = (colorUL + colorUM + colorUR + colorML+ colorMM + colorMR + colorLL + colorLM + colorLR) / 9.0;
		
				color = ColorDbl(floor(color.red), floor(color.green), floor(color.blue));*/
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