#include "hitable_list.h"


HitableList::HitableList() {}

HitableList::HitableList( Hitable **l, int n ) : list( l ), list_size( n )
{}

bool HitableList::Hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const
{
    HitRecord temp_record;
    bool hit_anything = false;
    double closet_so_far = t_max;
    for( int i = 0; i < this->list_size; i++)
    {
        if( this->list[i]->Hit( ray, t_min, closet_so_far, temp_record ) )
        {
            hit_anything = true;
            closet_so_far = temp_record.t;
            record = temp_record;
        }
    }
    return hit_anything;
}
        