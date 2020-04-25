#include <iostream>
#include <fstream>


#include "buffer.h"


Buffer::Buffer()
{
    this->buffer_data.resize( this->h_resolution, std::vector< glm::vec3 >(this->v_resolution) );

    for( int y = 0; y < this->v_resolution; y++ )
        for( int x = 0; x < this->h_resolution; x++ )
            this->buffer_data[x][y] = glm::vec3( 0.0f );

}

Buffer::Buffer( int h_resolution, int v_resolution) :
                h_resolution( h_resolution ),
                v_resolution( v_resolution )
{
    this->buffer_data.resize( this->h_resolution, std::vector< glm::vec3 >( this->v_resolution ) );

    for( int y = 0; y < this->v_resolution; y++ )
        for( int x = 0; x < this->h_resolution; x++ )
            this->buffer_data[x][y] = glm::vec3( 0.0f );
}

Buffer::~Buffer() {}

void Buffer::Save( const std::string &file_name )
{
    std::clog << "Buffer saving started... ";

    std::ofstream rendering_file;
    rendering_file.open( file_name.c_str() );

    rendering_file  << "P3"
                    << std::endl
                    << this->h_resolution << " " << this->v_resolution << " "
                    << std::endl
                    << 255
                    << std::endl;

    for( int y = this->v_resolution - 1; y >= 0; y-- )
        for( int x = 0; x < this->h_resolution; x++ )
        {
            rendering_file << static_cast< int >( clamp( buffer_data[x][y][0] ) * 255.0f + 0.5f ) << " ";
            rendering_file << static_cast< int >( clamp( buffer_data[x][y][1] ) * 255.0f + 0.5f ) << " ";
            rendering_file << static_cast< int >( clamp( buffer_data[x][y][2] ) * 255.0f + 0.5f ) << " ";
            
        }
    
    rendering_file.close();

    std::clog << "finished!" << std::endl;


}