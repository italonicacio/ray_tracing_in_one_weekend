#include "camera.h"

glm::vec3 RandomInUnitDisk()
{
    glm::vec3 p;
    do{
        p = 2.0f * glm::vec3( drand48(), drand48(), 0.0f ) - glm::vec3( 1.0f, 1.0f, 0.0f );
    }while( glm::dot( p, p ) >= 1.0f );
    return p;
}


Camera::Camera( glm::vec3 look_from, glm::vec3 look_at, glm::vec3 vup, float vfov, float aspect, float aperture, float focus_dist )
{
    this->lens_radius = aperture / 2.0f;
    float theta = vfov*M_PI/180;
    float half_height = tan( theta/2.0f );
    float half_width = aspect * half_height;

    this->origin = look_from;

    this->w = glm::normalize( look_from - look_at );
    this->u = glm::normalize( glm::cross( vup, w ) );
    this->v = glm::cross( w, u );

    this->lower_left_corner = glm::vec3( -half_width, -half_height, -1.0f );  
    this->lower_left_corner = this->origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    
    this->horizontal = 2.0f * half_width * focus_dist * u;
    this->vertical = 2.0f * half_height *focus_dist * v;
    
}

Ray Camera::GetRay(float s, float t)
{
    glm::vec3 rd = this->lens_radius*RandomInUnitDisk();
    glm::vec3 offset = u * rd.x + v * rd.y;
    return Ray( this->origin + offset, this->lower_left_corner + s*this->horizontal + t*this->vertical - this->origin - offset);
}