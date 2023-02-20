#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable
{
public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m):
        center(cen), radius(r), mat_ptr(m) {}
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{  
    // (O+tD-C)(O+tD-C) = r^2 =>
    // (D·D)t^2 + 2D(O-C)t + (O-C)(O-C)-r^2 = 0
    // return first hit time if hit, -1 for not hit
    auto A = r.direction().length_squared();
    auto B = 2 * dot(r.direction(), r.origin()-center);
    auto C = (r.origin()-center).length_squared() - radius*radius;
    auto discriminant = B*B - 4*A*C;
    if(discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);
    auto root = (-B-sqrtd)/(2.0*A);
    if(root < t_min || root > t_max){
        root = (-B+sqrtd)/(2.0*A);
        if(root < t_min || root > t_max){
            return false;
        }
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p-center) / radius; // normal is a unit vec3
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool sphere::bounding_box(double time0, double time1, aabb& output_box) const
{
    output_box = aabb(center-vec3(radius,radius,radius), center+vec3(radius,radius,radius));
    return true;
}