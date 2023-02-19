#include <iostream>
#include <fstream>
#include "vec3.h"

void write_color(std::ofstream &fout, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    fout << static_cast<int>(255.999 * pixel_color.x()) << ' '
         << static_cast<int>(255.999 * pixel_color.y()) << ' '
         << static_cast<int>(255.999 * pixel_color.z()) << ' ';
}

int main() {

    // Image
    const int image_width = 256;
    const int image_height = 256;

    // save framebuffer to file
    const std::string outputFile {"C:/Users/45162.CPHXR9000K/Desktop/RayTracing/output/fig2.ppm"};
    std::ofstream fout(outputFile);
    fout << "P3\n" << image_width << " " << image_height <<"\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(double(i)/(image_width-1),
                              double(j)/(image_height-1), 0.25);
            write_color(fout, pixel_color);
        }
    }
    fout.close();

    std::cerr << "\nDone.\n";
}