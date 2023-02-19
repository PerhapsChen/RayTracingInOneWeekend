#pragma once

#include "vec3.h"
#include <iostream>
#include <fstream>

//- write
void write_color(std::ofstream &fout, color pixel_color, int samples_per_pixel) 
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto Scale = 1.0 / samples_per_pixel;
    r *= Scale;
    g *= Scale;
    b *= Scale;

    // Write the translated [0,255] value of each color component.
    fout << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
         << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << ' ';                                                         
}