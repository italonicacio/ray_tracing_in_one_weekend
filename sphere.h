#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

#include "hitable.h"

class Sphere : public Hitable
{
    public:
        Sphere();
        Sphere( glm::vec3 center, float radius );
        Sphere( glm::vec3 center, float radius, Material* material );
        virtual bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const;
        
        glm::vec3 center;
        float radius;
        Material* material;

};


#endif //SPHERE_H