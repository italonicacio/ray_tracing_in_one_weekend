#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "ray.h"
#include "hitable.h"

glm::vec3 Reflect( const glm::vec3& v, const glm::vec3& n )
{
    return v - 2.0f * glm::dot(v,n) * n;
}

bool Refract( const glm::vec3& v, const glm::vec3& n, float ni_ove_nt, glm::vec3& refracted )
{
    glm::vec3 uv = glm::normalize(v);
    float dt = glm::dot(uv,n);
    float discriminant = 1.0f - ni_ove_nt * ni_ove_nt * ( 1.0f - dt*dt );
    if( discriminant > 0.0f )
    {
        refracted = ni_ove_nt * ( uv - n * dt ) - n * glm::sqrt( discriminant );
        return true;
    }else
        return false;
}

float Schlick( float cosine, float ref_idx )
{
    float r0 = ( 1.0f - ref_idx ) / ( 1.0f + ref_idx );
    r0 = r0*r0;
    return r0 + ( 1.0f - r0 ) * glm::pow( ( 1.0f - cosine ), 5.0f );
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

class Dieletric : public Material
{
    public:
        Dieletric( float ri ) : ref_idx(ri) {}
       
        virtual bool Scatter( const Ray& ray_in, const HitRecord& record, glm::vec3& attenuation, Ray& scattered ) const
        {
            glm::vec3 outward_normal;
            glm::vec3 reflected = Reflect( ray_in.Direction(), record.normal );
            float ni_over_nt;
            attenuation = glm::vec3( 1.0f );
            glm::vec3 refracted;
            float reflect_prob;
            float cosine;
            if( glm::dot( ray_in.Direction(), record.normal ) > 0.0f )
            {
                outward_normal = -record.normal;
                ni_over_nt = this->ref_idx;
                cosine = this->ref_idx * glm::dot( ray_in.Direction(), record.normal ) / glm::length( ray_in.Direction() );
            }else{
                outward_normal = record.normal;
                ni_over_nt = 1.0f / this->ref_idx;
                cosine = -glm::dot( ray_in.Direction(), record.normal ) / glm::length( ray_in.Direction() );
            }
            
            if( Refract( ray_in.Direction(), outward_normal, ni_over_nt, refracted ) )
            {
                reflect_prob = Schlick( cosine, this->ref_idx );
            }else{
                reflect_prob = 1.0f;
            }

            if( drand48() < reflect_prob )
            {
                scattered = Ray( record.p, reflected );
            }else{
                scattered = Ray( record.p, refracted );
            }

            return true;

        }

        float ref_idx;
};



#endif //MATERIAL_H