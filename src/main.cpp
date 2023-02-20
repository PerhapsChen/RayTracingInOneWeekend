#include <iostream>
#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

color ray_color(const ray& r, const hittable& world, int depth){
    hit_record rec;

    // too much bounce, no energy to eye.
    if(depth <= 0){
        return color(0,0,0);
    }

    if(world.hit(r,0.001,infinity,rec)){ //! recur
        // point3 target = rec.p + rec.normal + random_in_unit_sphere();
        // point3 target = rec.p + rec.normal + random_unit_vector();
        //point3 target = rec.p + random_in_hemisphere(rec.normal);
        //return 0.5 * ray_color(ray(rec.p, target-rec.p), world, depth-1);
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    // else -> still background.
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t) * color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}


int main() {

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int> (image_width/aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    //World
    auto R = cos(pi/4);

    hittable_list world;

    auto material_left  = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));

    world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));

    camera cam(90, aspect_ratio);

    // Render
    const std::string outputFile {"C:/Users/45162.CPHXR9000K/Desktop/RayTracing/output/fig2.ppm"};
    std::ofstream fout(outputFile);
    fout << "P3\n" << image_width << " " << image_height <<"\n255\n";
    
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for(int s = 0; s < samples_per_pixel; ++s){
                auto u = (i+random_double())/(image_width-1);
                auto v = (j+random_double())/(image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r,world, max_depth);
            }
            write_color(fout, pixel_color , samples_per_pixel);
        }
    }
    fout.close();

    std::cerr << "\nDone.\n";
}