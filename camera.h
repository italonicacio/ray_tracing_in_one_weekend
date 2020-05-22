#ifndef  CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "ray.h"

class Camera
{
    public:
        Camera( glm::vec3 look_from, glm::vec3 look_at, glm::vec3 vup, float vfov, float aspect, float aperture, float focus_dist );
        Ray GetRay(float u, float v);

        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
        glm::vec3 u, v, w;
        float lens_radius;
};

#endif // CAMERA_H