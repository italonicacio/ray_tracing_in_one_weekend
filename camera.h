#ifndef  CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "ray.h"

class Camera
{
    public:
        Camera();
        Ray GetRay(float u, float v);

        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
};

#endif // CAMERA_H