#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Vertex.cpp"
#include "Ray.cpp"
#include "Matrix.cpp"
#include "Pixel.cpp"
#include "Scene.cpp"
#include <vector>
#include <fstream>
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
    Camera()
        : pixelPlane(800, std::vector<Pixel>(800))
	{};

    void setEye()
    {};

	void createImage()
	{

	};

    void render(Scene &s)
    {
		int size = 800;
		double lengthP = 0.0025;
		double hlengthP = lengthP / 2.0;

		std::ofstream out("out.ppm");
		out << "P3\n" << size << ' ' << size << ' ' << "255\n";

		Vertex pixelPoint;

        for (int h = 0; h < size; h++)
        {
            for (int w = 0; w < size; w++)
            {
				double t;


				//pixelPoint = Vertex(0, -1+hlengthP+(w*lengthP), 1-hlengthP-(h*lengthP), 1);
				pixelPoint = Vertex(0.0, w*lengthP -(1-lengthP), h*lengthP - (1 - lengthP), 1.0);
                Ray ray(eye1, pixelPoint);
				for(auto &t2 : s.triangles)
				{
					
					/*t2.printTriangle();
					std::cout << "---------------------" << std::endl;*/

					if (t2.rayIntersection(ray, t)) {
						pixelPlane[h][w].color = t2.color;
					}
				}
				out << pixelPlane[h][w].color;


            }
        }

	};

    int eye; // 1 or 2
    Vertex eye1{ -2.0, 0.0, 0.0, 1.0 };
    Vertex eye2{ -1.0, 0.0, 0.0, 1.0 };
	std::vector<std::vector<Pixel>>pixelPlane;



private:



};

#endif // !CAMERA_CPP