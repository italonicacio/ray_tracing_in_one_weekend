#include <iostream>
#include <glm/glm.hpp>

#include "ray.h"
#include "buffer.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"


glm::vec3 Color( const Ray& ray, Hitable *world, int depth) 
{
    HitRecord record;
    if( world->Hit( ray, 0.001f, MAXFLOAT, record ) )
    {
        
        Ray scattered;
        glm::vec3 attenuation;
        
        if( depth < 50 && record.material->Scatter( ray, record, attenuation, scattered ) )
        {
            return attenuation * Color(scattered, world, depth++);
        }else{
            return glm::vec3(0.0f);
        }

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

    // int x_resolution = 1920;
    // int y_resolution = 1080;

    int sample = 100;
    
    Hitable *list[4];
    list[0] = new Sphere( glm::vec3( 0.0f, 0.0f, -1.0f ), 0.5f, new Lambertian( glm::vec3( 0.8f, 0.3f, 0.3f ) ) );
    list[1] = new Sphere( glm::vec3( 0.0f, -100.5f, -1.0f ), 100.0f, new Lambertian( glm::vec3( 0.8f, 0.8f, 0.0f )));
    list[2] = new Sphere( glm::vec3( 1.0f, 0.0f, -1.0f ), 0.5f, new Metal( glm::vec3( 0.8f, 0.6f, 0.2f ), 0.3f));
    list[3] = new Sphere( glm::vec3( -1.0f, 0.0f, -1.0f ), 0.5f, new Metal( glm::vec3( 0.8f, 0.8f, 0.8f ), 1.0f));
    
    Hitable *world = new HitableList( list, 4);

    Buffer buffer(x_resolution, y_resolution);
    Camera camera;

    for(int j = y_resolution - 1; j >= 0; j--)
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
                color += Color( ray, world, 0 ); 
            }
            
            color /= float(sample);
            
            buffer.buffer_data[i][j] = color;
        }
    }

    std::string image = "output_image.ppm";
    buffer.Save( image );

    return 0;
}