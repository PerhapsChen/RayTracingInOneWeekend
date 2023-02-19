#include <iostream>
#include <fstream>

inline float clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }


int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render



    // save framebuffer to file
    const std::string outputFile {"C:/Users/45162.CPHXR9000K/Desktop/RayTracing/output/fig.ppm"};
    std::ofstream fout(outputFile);
    fout << "P3\n" << image_width << " " << image_height <<"\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            auto ir = static_cast<int>(255.999 * r);
            auto ig = static_cast<int>(255.999 * g);
            auto ib = static_cast<int>(255.999 * b);

            fout << ir << ' ' << ig << ' ' << ib << ' ';
        }
    }
    fout.close();
}