#ifndef APP_VERSION
# define APP_VERSION "0.0.0"
#endif
//#define SDL_MAIN_HANDLED//not needed in msvc,need to enable this from cmake, now is needed in msvc, wtf
//#define RC_INVOKED//this should't be done

#ifndef APP_VERSION
# define APP_VERSION "0.0.0"
#endif


#include <iostream>
#include <iomanip>
#include <sstream>

#include <SDL2/SDL.h>
#include <glad/glad.h>


#include "DEngine/spdlog_helper.h"
#include "DEngine/core.h"
#include "DEngine/sdl_helpers.h"


using namespace std;


int main(void)
{
    auto logger = getMultiSinkLogger();

    //auto App = DEngine::Core(DEngine::RendererType::OpenGl);
    auto App = DEngine::Core(DEngine::RendererType::DirectX11);
    App.Init("DEngine App",800,600);

    /*
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = 
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };


    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Tell open GL to use this buffer
    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);//not sure if needed twice
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    */

    logSDL2renderersInfo();

    SDL_Event event;
    bool quit = false;
    bool green = false; // Toggle background clearing color between green and blue
    while (!quit) 
    {
        //green ? glClearColor(0.0,0.5,0.1,1.0) : glClearColor(0.0,0.,0.5,1.0);        
        green ^= true;            

        
        //glClear(GL_COLOR_BUFFER_BIT);
        //glDrawArrays(GL_TRIANGLES, 0, 3); // 3: Three vertices. Should draw the triangle?
        

        App.Render();
        
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                quit = true;
            }
        }
    }
    
    return 0;
}
