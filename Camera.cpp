﻿#ifndef CAMERA_CPP
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
const double PI = 3.14159265359;
class Camera
{
public:
    Camera()
        : pixelPlane(800, std::vector<Pixel>(800))
	{};

    void setEye()
    {};

    void render(Scene &s)
    {
		int size = 800;
		double lengthP = 0.0025;
		double hlengthP = lengthP / 2.0;
		ColorDbl black = ColorDbl(255.0, 255.0, 255.0);

		Vertex pointLight = Vertex(5.0, 0.0, 5.0, 1.0);
		Direction pointLightDirection;

		std::ofstream out("out.ppm");
		out << "P3\n" << size << ' ' << size << ' ' << "255\n";

		Vertex pixelPoint;

        for (int h = 0; h < size; h++)
        {
            for (int w = size-1; w >= 0; w--)
            {
				double t;

				pixelPoint = Vertex(0.0, hlengthP+(w*lengthP)-1.0, 1.0-hlengthP-(h*lengthP), 1.0);
                Ray ray(eye1, pixelPoint);
				
				for(auto &t2 : s.triangles)
				{
					if (t2.rayIntersection(ray, t))
					{
						pointLightDirection = pointLight - t2.Phit;
						pointLightDirection = pointLightDirection.normalize();
						//t2.getNormal();
						double angle = acos(pointLightDirection.dotProduct(t2.getNormal()));
						if (angle > PI/2)
						{
							pixelPlane[w][h].color = black;
						}
						pixelPlane[w][h].color = (t2.color*std::abs(cos(angle)));
						//pixelPlane[w][h].color = t2.color;
					}
				}
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