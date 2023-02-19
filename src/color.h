#pragma once

#include "vec3.h"
#include <iostream>
#include <fstream>

//- write
void write_color(std::ofstream &fout, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    fout << static_cast<int>(255.999 * pixel_color.x()) << ' '
         << static_cast<int>(255.999 * pixel_color.y()) << ' '
         << static_cast<int>(255.999 * pixel_color.z()) << ' ';                                                         
}