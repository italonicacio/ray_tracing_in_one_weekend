#include <iostream>
#include <sstream>
#include <iomanip>
#include <glm/glm.hpp>

#include "ray.h"
#include "buffer.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"


Hitable *RandomScene()
{
    int n = 500;
    Hitable **list = new Hitable*[n+1];
    list[0] = new Sphere( glm::vec3( 0.0f, -1000.0f, 0.0f ), 1000, new Lambertian( glm::vec3( 0.5f ) ) );
    int i = 1;
    for( int a = -11; a < 11; a++ )
    {
        for( int b = -11; b < 11; b++ )
        {
            float choose_mat = drand48();
            glm::vec3 center( a+0.9*drand48(), 0.2, b+0.9*drand48() );
            if( glm::length( center-glm::vec3( 4.0f, 0.2f, 0.0f )) > 0.9f )
            {
                if( choose_mat < 0.8f )
                {
                    list[i++] = new Sphere( center, 0.2f, new Lambertian( glm::vec3( drand48()*drand48(), drand48()*drand48(), drand48()*drand48() ) ) );
                }else if( choose_mat < 0.95f ) {
                    list[i++] = new Sphere( center, 0.2f, 
                        new Metal( glm::vec3( 0.5f * ( 1.0f + drand48() ), 0.5f * ( 1.0f + drand48() ), 0.5f * ( 1.0f + drand48() ) ), 0.5f * ( 1.0f + drand48() ) ) );
                }else{
                    list[i++] = new Sphere( center, 0.2f, new Dieletric( 1.5f ) );

                }
            }
        }
    }

    list[i++] = new Sphere( glm::vec3( 0.0f, 1.0f, 0.0f ), 1.0f, new Dieletric( 1.5f ) );
    list[i++] = new Sphere( glm::vec3( -4.0f, 1.0f, 0.0f ), 1.0f, new Lambertian( glm::vec3( 0.4f, 0.2f, 0.1f ) ) );
    list[i++] = new Sphere( glm::vec3( 4.0f, 1.0f, 0.0f ), 1.0f, new Metal( glm::vec3( 0.7f, 0.6f, 0.5f ), 0.0f ) );

   

    return new HitableList( list, i );
    
}



glm::vec3 Color( const Ray& ray, Hitable *world, int depth) 
{
    HitRecord record;
    if( world->Hit( ray, 0.001f, MAXFLOAT, record ) )
    {
        
        Ray scattered;
        glm::vec3 attenuation;
        
        if( depth < 50 && record.material->Scatter( ray, record, attenuation, scattered ) )
        {
            return attenuation * Color(scattered, world, depth+1);
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
    // int x_resolution = 200;
    // int y_resolution = 100;

    // int x_resolution = 800;
    // int y_resolution = 600;

    int x_resolution = 1920;
    int y_resolution = 1080;

    int sample = 100;
    
// #define SIZE 5

//     Hitable *list[SIZE];
//     // float R = cos( M_PI/4.0f );
//     // list[0] = new Sphere( glm::vec3( -R, 0.0f, -1.0f ), R, new Lambertian( glm::vec3( 0.0f, 0.0f, 1.0f ) ) );
//     // list[1] = new Sphere( glm::vec3( R, 0.0f, -1.0f ), R, new Lambertian( glm::vec3( 1.0f, 0.0f, 0.0f )));


//     list[0] = new Sphere( glm::vec3( 0.0f, 0.0f, -1.0f ), 0.5f, new Lambertian( glm::vec3( 0.1f, 0.2f, 0.5f ) ) );
//     list[1] = new Sphere( glm::vec3( 0.0f, -100.5f, -1.0f ), 100.0f, new Lambertian( glm::vec3( 0.8f, 0.8f, 0.0f )));
//     list[2] = new Sphere( glm::vec3( 1.0f, 0.0f, -1.0f ), 0.5f, new Metal( glm::vec3( 0.8f, 0.6f, 0.2f ), 1.0f));
//     list[3] = new Sphere( glm::vec3( -1.0f, 0.0f, -1.0f ), 0.5f, new Dieletric( 1.5f ) );
//     list[4] = new Sphere( glm::vec3( -1.0f, 0.0f, -1.0f ), -0.45f, new Dieletric( 1.5f ) );

    
    // Hitable *world = new HitableList( list, SIZE);
    Hitable *world = RandomScene();

    Buffer buffer(x_resolution, y_resolution);

    glm::vec3 look_from( 13.0f, 3.0f, 5.0f );
    glm::vec3 look_at( 0.0f, 0.0f, 0.0f );
    float dist_to_focus = 10.0f;//glm::length(look_from - look_at);
    float aperture = 0.1f;
    Camera camera(  look_from, look_at, glm::vec3( 0.0f, 1.0f, 0.0f ), 25.0f, float(x_resolution)/float(y_resolution), aperture, dist_to_focus );

#pragma omp parallel for schedule(dynamic, 1) 
    for(int j = y_resolution - 1; j >= 0; j--)
    {

        std::stringstream progress_stream;
        progress_stream << "\r progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * (y_resolution - j) / ( buffer.v_resolution)
                        << "%";

        std::clog << progress_stream.str();

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
    std::clog << std::endl;

    std::string image = "output_image.ppm";
    buffer.Save( image );

    return 0;
}