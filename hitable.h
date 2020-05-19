#ifndef HITABLE_H
#define HITABLE_H

#include <glm/glm.hpp>

#include "ray.h"

class Material;

struct HitRecord
{
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    Material* material;
};

class Hitable
{
    public:
        virtual bool Hit( const Ray& ray, float t_min, float t_max, HitRecord& record ) const = 0;
};


#endif //HITABLE_H