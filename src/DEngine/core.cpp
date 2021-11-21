#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>

#include "core.h"
#include "spdlog_helper.h"


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
    switch (rendererType)
    {
        case RendererType::DirectX11 :
            return InitDX11(title, width,height,flags);
            break;
        case RendererType::OpenGl :
            return InitGL(title, width,height,flags); 
            break;
        default:
            break;
    }
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