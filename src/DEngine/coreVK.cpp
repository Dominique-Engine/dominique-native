#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>

#include "core.h"
#include "spdlog_helper.h"



int DEngine::Core::InitVK(const char* title, const int &width, const int &height, const int &flags )
{
    auto logger = getMultiSinkLogger();

    // initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        // clean up SDL
        atexit (SDL_Quit);

        // Request an OpenGL 4.3 context (should be core)
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        // Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // if succeeded create our window
        _windowHandler = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
        );


        if (_windowHandler == NULL)
        {
            logger.error("Couldn't set video mode: {}", SDL_GetError());
            return 1;
        }

        // if the window creation succeeded create our renderer
        _glContext = SDL_GL_CreateContext(_windowHandler);

    }
    else
    {
        logger.error("Couldn't initialize SDL: {}", SDL_GetError());
        return 1; // sdl could not initialize
    }
 

    // Check OpenGL properties
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress) )
    {
        logger.error( "Failed to initialize OpenGL context" );
        return 1;
    }
    logger.info("OpenGL loaded");
    logger.info("Vendor:   {}, Renderer: {}, Version:  {}", glGetString(GL_VENDOR),glGetString(GL_RENDERER),glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(_windowHandler, &w, &h);
    glViewport(0, 0, w, h);
    
    //base clear color
    glClearColor(config.clearColor[0],config.clearColor[1],config.clearColor[2],config.clearColor[3]);

    return 0;
} 


void DEngine::Core::RenderVK()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(_windowHandler);
}

int DEngine::Core::CleanVK()
{
    auto logger = getMultiSinkLogger();

    logger.info("Cleaning engine");

    SDL_GL_DeleteContext(_glContext);
    SDL_DestroyWindow(_windowHandler);
    SDL_Quit();

    return 0;
}