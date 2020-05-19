#include "sphere.h"


Sphere::Sphere() {}

Sphere::Sphere( glm::vec3 center, float radius ) : center( center ), radius( radius )
{}

Sphere::Sphere( glm::vec3 center, float radius, Material* material ) : center( center ), radius( radius ), material(material)
{}

bool Sphere::Hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const
{
    glm::vec3 oc = ray.Origin() - this->center;
    float a = glm::dot( ray.Direction(), ray.Direction() );
    float b = glm::dot( oc, ray.Direction() );
    float c = glm::dot( oc, oc ) - this->radius*this->radius;
    float discriminant = b * b - a * c;

    if( discriminant > 0 )
    {
        float temp = ( -b - sqrt( discriminant ))/a;
        if( temp < t_max && temp > t_min )
        {
            record.t = temp;
            record.p = ray.PointAtParameter( record.t );
            record.normal = ( record.p - this->center ) / radius;
            record.material = this->material;
            return true;
        }

        temp = ( -b + sqrt( discriminant ))/a;
        if( temp < t_max && temp > t_min )
        {
            record.t = temp;
            record.p = ray.PointAtParameter( record.t );
            record.normal = ( record.p - center ) / radius;
            record.material = this->material;
            return true;
        }
    }
    return false;

}