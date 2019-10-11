#ifndef PIXEL_CPP
#define PIXEL_CPP

#include "ColorDbl.cpp"

/*Pixel contains one instance of ColorDbl that holds the color and intensity
for this pixel with a high dynamic range.
Pixel has references to the rays that go through it. We use for now one
The scene image is stored in the ColorDbl attribute of the Pixels.*/

class Pixel
{
public:
    // default constructor
    Pixel()
        : color{ ColorDbl(0.0, 0.0, 0.0) } {};

    // constructor to create pixel given a color
    Pixel(ColorDbl c)
        : color{ c } {};

	ColorDbl color;

private:

};

#endif // !PIXEL_CPP