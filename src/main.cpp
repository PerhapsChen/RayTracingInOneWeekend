#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

//- write
void write_color(std::ofstream &fout, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    fout << static_cast<int>(255.999 * pixel_color.x()) << ' '
         << static_cast<int>(255.999 * pixel_color.y()) << ' '
         << static_cast<int>(255.999 * pixel_color.z()) << ' ';                                                         
}

bool hit_sphere(const point3& center, double radius, const ray& r ){
    // (O+tD-C)(O+tD-C) = r^2 =>
    // (D·D)t^2 + 2D(O-C)t + (O-C)(O-C)-r^2 = 0
    auto A = r.direction().length_squared();
    auto B = 2 * dot(r.direction(), r.origin()-center);
    auto C = (r.origin()-center).length_squared() - radius*radius;
    return B*B - 4*A*C > 0;
}

//- 背景，方向从下到上 由白到蓝
color ray_color(const ray& r){
    if(hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t) * color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}


int main() {

    // Image
    const double aspect_ratio = 16.0/9.0;
    const int image_width = 480;
    const int image_height = static_cast<int> (image_width/aspect_ratio);

    //Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_lenght = 1.0; //焦距

    point3 origin(0.0,0.0,0.0);
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_lenght);


    // Render
    const std::string outputFile {"C:/Users/45162.CPHXR9000K/Desktop/RayTracing/output/fig2.ppm"};
    std::ofstream fout(outputFile);
    fout << "P3\n" << image_width << " " << image_height <<"\n255\n";
    
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner+u*horizontal+v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(fout, pixel_color);
        }
    }
    fout.close();

    std::cerr << "\nDone.\n";
}