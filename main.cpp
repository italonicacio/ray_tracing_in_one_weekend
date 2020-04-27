#include <iostream>
#include <glm/glm.hpp>

#include "ray.h"
#include "buffer.h"
#include "sphere.h"
#include "hitable_list.h"


glm::vec3 Color( const Ray& ray, Hitable *world) 
{
    HitRecord record;
    if( world->Hit( ray, 0.0, MAXFLOAT, record ) )
    {
        return 0.5f*glm::vec3( record.normal.x + 1.0f, record.normal.y + 1.0f, record.normal.z + 1.0f );
    }else{
        glm::vec3 unit_direction = glm::normalize( ray.Direction() );
        float t = 0.5*( unit_direction.y + 1.0f );
        return (1.0f - t) * glm::vec3( 1.0f ) + t * glm::vec3( 0.5f, 0.7f, 1.0f );
    }
        
    
}

int main()
{
    int x_resolution = 200;
    int y_resolution = 100;
    
    glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin( 0.0f );

    Hitable *list[2];
    list[0] = new Sphere( glm::vec3( 0.0f, 0.0f, -1.0f ), 0.5f);
    list[1] = new Sphere( glm::vec3( 0.0f, -100.5f, -1.0f ), 100);
    Hitable *world = new HitableList( list, 2);


    Buffer buffer(x_resolution, y_resolution);

    for(int j = y_resolution-1; j>=0; j--)
    {
        for(int i = 0; i < x_resolution; i++)
        {
            float u = float(i)/float(x_resolution);
            float v = float(j)/float(y_resolution);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);
            
            //glm::vec3 p = ray.PointAtParameter( 2.0f );
            glm::vec3 color = Color( ray, world );
            buffer.buffer_data[i][j] = color;
        }
    }

    std::string image = "output_image.ppm";
    buffer.Save( image );

    return 0;
}