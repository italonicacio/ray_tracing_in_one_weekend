#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

class Buffer
{
    public:  
        Buffer();       
        Buffer( int h_resolution, int v_resolution);
        ~Buffer();

        void Save( const std::string &file_name );

        int h_resolution = 512;
        int v_resolution = 512;

        std::vector< std::vector< glm::vec3 > > buffer_data;

    private:
        float clamp( float x ) const
        {
            return ( x < 0.0f ) ? 0.0f : ( x > 1.0f ) ? 1.0f : x;
        }


};

#endif //BUFFER_H