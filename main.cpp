#include <iostream>
#include <glm/glm.hpp>

#include "buffer.h"

int main()
{
    int x_resolution = 200;
    int y_resolution = 100;

    Buffer buffer(x_resolution, y_resolution);

    for(int j = y_resolution-1; j>=0; j--)
    {
        for(int i = 0; i < x_resolution; i++)
        {
            
            glm::vec3 color(    float(i)/float(x_resolution),
                                float(j)/float(y_resolution),
                                0.2f );
            buffer.buffer_data[i][j] = color;
        }
    }

    buffer.Save( "output_image.ppm" );

    return 0;
}