#include "camera.h"

Camera::Camera()
{
    this->origin = glm::vec3( 0.0f, 0.0f, 0.0f );
    this->lower_left_corner = glm::vec3( -2.0f, -1.0f, -1.0f );
    this->horizontal = glm::vec3( 4.0f, 0.0f, 0.0f );
    this->vertical = glm::vec3( 0.0f, 2.0f, 0.0f );
    
}

Ray Camera::GetRay(float u, float v)
{
    return Ray( this->origin, this->lower_left_corner + u*this->horizontal + v*this->vertical - this->origin );
}