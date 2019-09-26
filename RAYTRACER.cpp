//#include "../raytracer/SDL2/include/SDL.h"
//#include "../SDL2/include/SDL.h"
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
int main()
{
    Camera c;
	Scene s;

	s.createScene();
	c.render(s);


    return 0;
}
