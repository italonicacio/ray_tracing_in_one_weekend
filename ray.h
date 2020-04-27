#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{
    public:
        Ray() {}
        Ray( const glm::vec3 &origin, const glm::vec3 &direction ) 
        { 
            this->origin = origin; 
            this->direction = direction;
        }
        inline glm::vec3 Origin() const { return this->origin; }
        inline glm::vec3 Direction() const { return this->direction; }
        inline glm::vec3 PointAtParameter( float t ) const { return this->origin + t*this->direction; }

        glm::vec3 origin;
        glm::vec3 direction;


};

#endif