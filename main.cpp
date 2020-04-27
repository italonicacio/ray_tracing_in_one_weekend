#include <iostream>
#include <glm/glm.hpp>

#include "ray.h"
#include "buffer.h"

bool HitSphere( const glm::vec3& center, float radius, const Ray& ray)
{
    glm::vec3 oc = ray.Origin() - center;
    float a = glm::dot( ray.Direction(), ray.Direction() );
    float b = 2.0 * glm::dot( oc, ray.Direction() );
    float c = glm::dot( oc, oc ) - radius*radius;
    float discriminant = b*b - 4 * a * c;
    return (discriminant > 0);


}

glm::vec3 Color( const Ray& ray) 
{
    if( HitSphere( glm::vec3( 0.0f, 0.0f, -1.0f), 0.5f, ray ) )
        return glm::vec3( 1.0f, 0.0f, 0.0f );
    glm::vec3 unit_direction = glm::normalize( ray.Direction() );
    float t = 0.5*( unit_direction.y + 1.0f );
    return (1.0f - t) * glm::vec3( 1.0f ) + t * glm::vec3( 0.5f, 0.7f, 1.0f );
}

int main()
{
    int x_resolution = 200;
    int y_resolution = 100;
    
    glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin( 0.0f );


    Buffer buffer(x_resolution, y_resolution);

    for(int j = y_resolution-1; j>=0; j--)
    {
        for(int i = 0; i < x_resolution; i++)
        {
            float u = float(i)/float(x_resolution);
            float v = float(j)/float(y_resolution);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);
            
            glm::vec3 color = Color( ray );
            buffer.buffer_data[i][j] = color;
        }
    }

    buffer.Save( "output_image.ppm" );

    return 0;
}