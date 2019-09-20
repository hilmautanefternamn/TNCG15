#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Vertex.cpp"
#include "Ray.cpp"
#include "Matrix.cpp"
#include "Pixel.cpp"
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
        : eye1{ -2.0, 0.0, 0.0, 1.0 }, pixelPlane(800, std::vector<Pixel>(800)){};

    void setEye()
    {};

    void render()
    {
		std::ofstream out("out.ppm");
		out << "P3\n" << 800 << ' ' << 800 << ' ' << "255\n";

        for (int x = 0; x < 800; x++)
        {
            for (int y = 0; y < 800; y++)
            {
				//std::cout << pixelPlane[x][y].getColor() << std::endl;
				pixelPlane[x][y] = ColorDbl(0.0, 120.0, 0.0);
                Ray ray(eye1, Vertex(x, y, 0, 1));
				//std::cout << pixelPlane[x][y].getColor() << std::endl;
				out << pixelPlane[x][y].getColor();
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