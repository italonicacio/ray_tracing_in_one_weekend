#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "ray.h"
#include "hitable.h"

glm::vec3 Reflect( const glm::vec3& v, const glm::vec3& n )
{
    
    return v - 2.0f * glm::dot(v,n) * n;
}

glm::vec3 RandomInUnitSphere()
{
    glm::vec3 p;
    do{
        p = 2.0f * glm::vec3( drand48(), drand48(), drand48() ) - glm::vec3(1.0f);
    }while( p.x*p.x + p.y*p.y + p.z*p.z >= 1.0f );

    return p;
}

class Material
{
    public:
        virtual bool Scatter( const Ray& ray_in, const HitRecord& record, glm::vec3& attenuation, Ray& scattered ) const = 0;
};

class Lambertian : public Material 
{
    public:
        Lambertian( const glm::vec3& albedo ) : albedo( albedo ) {}
        virtual bool Scatter( const Ray& ray_in, const HitRecord& record, glm::vec3& attenuation, Ray& scattered ) const
        {
            glm::vec3 target = record.p + record.normal + RandomInUnitSphere();
            scattered = Ray( record.p, target - record.p );
            attenuation = albedo;
            return true;
        }


        glm::vec3 albedo;
        
};

class Metal : public Material
{
    public:
        Metal( const glm::vec3& albedo, float fuzz) : albedo(albedo)
        {
            if(fuzz < 1.0f)
                this->fuzz = fuzz;
            else
                fuzz = 1.0f;
        }
        virtual bool Scatter( const Ray& ray_in, const HitRecord& record, glm::vec3& attenuation, Ray& scattered ) const
        {
            
            glm::vec3 reflected = Reflect( glm::normalize( ray_in.Direction() ), record.normal );
            scattered = Ray( record.p, reflected + this->fuzz * RandomInUnitSphere() );
            attenuation = this->albedo;
            return ( glm::dot(scattered.Direction(), record.normal ) > 0.0f );
        }

        glm::vec3 albedo;
        float fuzz;
};


#endif //MATERIAL_H