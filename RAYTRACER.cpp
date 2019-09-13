#include "bitmap_image.hpp"
#include <iostream>
#include <math.h>


using namespace std;

// Vertex has three spatial coordinates x, y, z and w (for homogeneous coordinates)
class Vertex
{
public:
    Vertex() {};  // Default constructor

    Vertex(double inX, double inY, double inZ, double inW)
        : x(inX), y(inY), z(inZ), w(inW) {};

    void printVertex()
    {
        std::cout << x << " " << y << " " << z << " " << w << std::endl;
    };

private:
    double x, y, z, w;
};

/* Direction  has the three components of a direction vector x, y, z */
class Direction
{
public:
    Direction() {};  // Default constructor

    Direction(double inX, double inY, double inZ)
        : x(inX), y(inY), z(inZ) {};

    void printDirection()
    {
        std::cout << x << " " << y << " " << z << std::endl;
    };

private:
    double x, y, z;
};

/* ColorDbl has three double precision variables that contain the intensities in the
red, green and blue channel.*/
class ColorDbl
{
public:
    ColorDbl() {};  // Default constructor

    ColorDbl(double R, double G, double B)
        : red(R), green(G), blue(B) {};
private:
    double red, green, blue;
};


/*Ray has two instances of Vertex, which are the ray’s starting point and end
point. You can put the vertices into a vertex list and use references to
these points in Ray. Ray contains a reference to the triangle on which
the end point is located. The ray color is a ColorDbl.*/
class Ray {};

/*The triangle is defined by three objects of the class Vertex.
The Triangle has a color, which we represent by an instance of ColorDbl.
The triangle’s normal direction is stored in an instance of Direction.
It has a method rayIntersection(Ray arg) that computes the intersection
between a Ray and the Triangle with the M¨oller-Trumbore algorithm.
*/
class Triangle
{
public:
    Triangle() {};

    Triangle(Vertex inV1, Vertex inV2, Vertex inV3, Direction n, ColorDbl c)
        :v1(inV1), v2(inV2), v3(inV3), normal(n), color(c) {};

    void rayIntersection(Ray arg) {};

private:
    Vertex v1, v2, v3;
    Direction normal;
    ColorDbl color;

};

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
    void findIntersecRay(Ray arg) {};
private:
    Triangle triangles[24]{};
};



// MAIN BITCH   
int main()
{
    double w = 1.0;
    std::cout << "Hello World!\n";

    Vertex vertices[14];
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

    /*for(int i = 0; i < 14; ++i )
        vertices[i].printVertex();*/

    Direction normals[8];
    normals[0] = Direction(0.0, 0.0, 1.0);                  // floor
    normals[1] = Direction(0.0, 0.0, -1.0);                 // roof
    normals[2] = Direction(2 / sqrt(5), -1 / sqrt(5), 0.0);     // VB
    normals[3] = Direction(0.0, -1.0, 0.0);                 // B
    normals[4] = Direction(-2 / sqrt(5), -1 / sqrt(5), 0.0);    // HB
    normals[5] = Direction(-2 / sqrt(5), 1 / sqrt(5), 0.0);     // HF
    normals[6] = Direction(0.0, 1.0, 0.0);                  // F
    normals[7] = Direction(2 / sqrt(5), 1 / sqrt(5), 0.0);      // VF

    /*for (int i = 0; i < 8; ++i)
        normals[i].printDirection(); */
    ColorDbl temp;

    Triangle triangles[24];
    // floor
    triangles[0] = Triangle(vertices[1], vertices[2], vertices[0], normals[0], temp);
    triangles[1] = Triangle(vertices[1], vertices[3], vertices[2], normals[0], temp);
    triangles[2] = Triangle(vertices[1], vertices[4], vertices[3], normals[0], temp);
    triangles[3] = Triangle(vertices[1], vertices[5], vertices[4], normals[0], temp);
    triangles[4] = Triangle(vertices[1], vertices[6], vertices[5], normals[0], temp);
    triangles[5] = Triangle(vertices[1], vertices[0], vertices[6], normals[0], temp);
    // roof
    triangles[6] = Triangle(vertices[8], vertices[9], vertices[7], normals[1], temp);
    triangles[7] = Triangle(vertices[8], vertices[10], vertices[9], normals[1], temp);
    triangles[8] = Triangle(vertices[8], vertices[11], vertices[10], normals[1], temp);
    triangles[9] = Triangle(vertices[8], vertices[12], vertices[11], normals[1], temp);
    triangles[10] = Triangle(vertices[8], vertices[13], vertices[12], normals[1], temp);
    triangles[11] = Triangle(vertices[8], vertices[7], vertices[13], normals[1], temp);
    // VB
    triangles[12] = Triangle(vertices[2], vertices[7], vertices[0], normals[2], temp);
    triangles[13] = Triangle(vertices[2], vertices[9], vertices[7], normals[2], temp);
    // B
    triangles[14] = Triangle(vertices[3], vertices[9], vertices[2], normals[3], temp);
    triangles[15] = Triangle(vertices[3], vertices[10], vertices[9], normals[3], temp);
    // HB
    triangles[16] = Triangle(vertices[4], vertices[10], vertices[3], normals[4], temp);
    triangles[17] = Triangle(vertices[4], vertices[11], vertices[10], normals[4], temp);
    // HF
    triangles[18] = Triangle(vertices[5], vertices[11], vertices[4], normals[5], temp);
    triangles[19] = Triangle(vertices[5], vertices[12], vertices[11], normals[5], temp);
    // F
    triangles[20] = Triangle(vertices[6], vertices[12], vertices[5], normals[6], temp);
    triangles[21] = Triangle(vertices[6], vertices[13], vertices[12], normals[6], temp);
    // VF
    triangles[22] = Triangle(vertices[0], vertices[13], vertices[6], normals[7], temp);
    triangles[23] = Triangle(vertices[0], vertices[7], vertices[13], normals[7], temp);


    bitmap_image image(200, 200);

    // set background to orange
    image.set_all_channels(255, 150, 50);

    image_drawer draw(image);

    draw.pen_width(3);
    draw.pen_color(255, 0, 0);
    draw.circle(image.width() / 2, image.height() / 2, 50);

    draw.pen_width(1);
    draw.pen_color(0, 0, 255);
    draw.rectangle(50, 50, 150, 150);

    image.save_image("output.bmp");

}