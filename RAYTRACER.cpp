//#include "../raytracer/SDL2/include/SDL.h"
#include "../SDL2/include/SDL.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <array>

#include "Camera.cpp"
#include "Triangle.cpp"


using namespace std;

// MAIN BITCH   
int main(int argc, char* argv[])
{
    // Triangle soup
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
    }

    Camera c;

    //c.createImage();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow
    ("An SDL2 window",  // window's title
        10, 25,         // coordinates on the screen, in pixels, of the window's upper left corner
        640, 480,       // window's length and height in pixels  
        SDL_WINDOW_OPENGL);

    SDL_Delay(3000); // window lasts 3 seconds
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
