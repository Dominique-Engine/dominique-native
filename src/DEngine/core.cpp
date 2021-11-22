#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>

#include "core.h"
#include "spdlog_helper.h"
#include "sdl_helpers.h"


DEngine::Core::Core(const RendererType &rendererTypeValue): rendererType(rendererTypeValue)
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

DEngine::DEDirectX11Context DEngine::Core::getDX11Context()
{
    return dxContext;
}



// This implementations are temporal, need to avoid the overhead of using switch to select different implementations, 
// here is not a problem because this functions are called only couple of times and are not performance sensitive
// but should be avoided for more frecuent functions 
int DEngine::Core::Init(const char* title, const int &width, const int &height, const int &flags )
{
    int result;
    auto logger = getMultiSinkLogger();

    switch (rendererType)
    {
        case RendererType::DirectX11 :
            result = InitDX11(title, width,height,flags);
            break;
        case RendererType::OpenGl :
            result = InitGL(title, width,height,flags); 
            break;
        default:
            break;
    }

    if(result == 0)
    {
        SDL_Surface *surface = loadImgFromFile2SDLSurface("icon.png");     // Declare an SDL_Surface to be filled in with pixel data from an image file

        // The icon is attached to the window pointer
        if (surface == nullptr) logger.warn("Could not load windows icon");
        else SDL_SetWindowIcon(windowHandler, surface);
        // ...and the surface containing the icon pixel data is no longer required.
        SDL_FreeSurface(surface);
    }

    return result;
}


int DEngine::Core::Clean()
{
    switch (rendererType)
    {
        case RendererType::DirectX11 :
            return CleanDX11();
            break;
        case RendererType::OpenGl :
            return CleanGL(); 
            break;
        default:
            break;
    }
}

// TODO this definetively need to be changed
void DEngine::Core::Render()
{
    switch (rendererType)
    {
        case RendererType::DirectX11 :
            return RenderDX11();
            break;
        case RendererType::OpenGl :
            return RenderGL(); 
            break;
        default:
            break;
    }
}