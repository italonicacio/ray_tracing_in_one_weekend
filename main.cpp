#include <iostream>
#include <glm/glm.hpp>

#include "ray.h"
#include "buffer.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

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
    int sample = 100;
    
    Hitable *list[2];
    list[0] = new Sphere( glm::vec3( 0.0f, 0.0f, -1.0f ), 0.5f);
    list[1] = new Sphere( glm::vec3( 0.0f, -100.5f, -1.0f ), 100);
    Hitable *world = new HitableList( list, 2);

    Buffer buffer(x_resolution, y_resolution);
    Camera camera;

    for(int j = y_resolution-1; j>=0; j--)
    {
        for(int i = 0; i < x_resolution; i++)
        {
            glm::vec3 color( 0.0f );
            for( int s = 0; s < sample; s++)
            {
                float u = float(i + drand48())/float(x_resolution);
                float v = float(j + drand48())/float(y_resolution);
                Ray ray = camera.GetRay(u, v);
                //glm::vec3 p = ray.PointAtParameter( 2.0f );
                color += Color( ray, world ); 
            }
            
            color /= float(sample);
            
            buffer.buffer_data[i][j] = color;
        }
    }

    std::string image = "output_image.ppm";
    buffer.Save( image );

    return 0;
}