#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

#include "hitable.h"

class Sphere : public Hitable
{
    public:
        Sphere();
        Sphere( glm::vec3 center, float radius );
        virtual bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const;
        
        glm::vec3 center;
        float radius;

};


#endif //SPHERE_H