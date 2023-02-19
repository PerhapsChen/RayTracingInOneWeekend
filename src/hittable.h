#pragma once

#include "ray.h"

// record the imformation of hit surface point
struct hit_record{
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray&r, const vec3& outward_normal)
    {
        normal=dot(r.direction(), outward_normal)>0?outward_normal:-outward_normal;
    }

};

class hittable{  // base class
public:
    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const = 0; // 纯虚函数
};