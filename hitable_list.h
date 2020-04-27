#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

class HitableList : public Hitable
{
    public:
        HitableList();
        HitableList( Hitable **l, int n );
        virtual bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const;
        
        Hitable **list;
        int list_size;
};


#endif //HITABLE_LIST_H