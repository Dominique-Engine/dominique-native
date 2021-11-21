#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>

#include "core.h"
#include "spdlog_helper.h"


DEngine::Core::Core(/* args */)
{
}

DEngine::Core::~Core()
{
    Clean();
}  


SDL_Window* DEngine::Core::getSDLwinHandler()
{
    return windowHandler;
}

SDL_GLContext DEngine::Core::getSDLglContext()
{
    return glContext;
}


int DEngine::Core::Init(const char* title, const int &width, const int &height, const int &flags )
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
        windowHandler = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );


        if (windowHandler == NULL)
        {
            logger.error("Couldn't set video mode: {}", SDL_GetError());
            return 1;
        }

        // if the window creation succeeded create our renderer
        glContext = SDL_GL_CreateContext(windowHandler);

    }
    else
    {
        logger.error("Couldn't initialize SD: {}", SDL_GetError());
        return 1; // sdl could not initialize
    }
 

    // Check OpenGL properties
    logger.info("OpenGL loaded");
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress) )
    {
        logger.error( "Failed to initialize OpenGL context" );
        return 1;
    }
    logger.info("Vendor:   {}", glGetString(GL_VENDOR));
    logger.info("Renderer: {}", glGetString(GL_RENDERER));
    logger.info("Version:  {}", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(windowHandler, &w, &h);
    glViewport(0, 0, w, h);
    
    //base clear color
    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);

    return 0;
} 


void DEngine::Core::Render()
{

}

int DEngine::Core::Clean()
{
    auto logger = getMultiSinkLogger();

    logger.info("Cleaning engine");

    SDL_DestroyWindow(windowHandler);
    SDL_Quit();

    return 0;
}