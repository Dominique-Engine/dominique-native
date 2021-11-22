#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>
#include <d3d11.h>

#include "core.h"
#include "spdlog_helper.h"
#include "dx11/dx11_helpers.h"

int DEngine::Core::InitDX11(const char* title, const int &width, const int &height, const int &flags )
{
    auto logger = getMultiSinkLogger();

    // initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        // clean up SDL
        atexit (SDL_Quit);

        // Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // if succeeded create our window
        windowHandler = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
        );


        if (windowHandler == NULL)
        {
            logger.error("Couldn't set video mode: {}", SDL_GetError());
            return 1;
        }

    }
    else
    {
        logger.error("Couldn't initialize SDL: {}", SDL_GetError());
        return 1; // sdl could not initialize
    }
 

    // if the window creation succeeded create our renderer
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(windowHandler, &wmInfo);
    HWND hwnd = (HWND)wmInfo.info.win.window;

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd, dxContext, false))
    {
        logger.error("Failed to initialize DirectX");
        CleanupDeviceD3D(dxContext);
        return 1;
    }

    DXGI_ADAPTER_DESC tempDescription;
    GetDefaultAdapterDesc(tempDescription);
    
    //Turn this into some useful information
    logger.info("DirectX11 loaded");
    std::wstring_view ws(tempDescription.Description);
    std::string s(ws.begin(), ws.end());
    logger.info("Vendor:   {}, Renderer: {}, Version:  {}", tempDescription.VendorId ,s,dxContext.pd3dDevice->GetFeatureLevel() );


    return 0;
} 


void DEngine::Core::RenderDX11()
{
    dxContext.pd3dDeviceContext->OMSetRenderTargets(1, &dxContext.mainRenderTargetView, NULL);
    dxContext.pd3dDeviceContext->ClearRenderTargetView(dxContext.mainRenderTargetView, config.clearColor);
    dxContext.pSwapChain->Present(1, 0); // Present with vsync
}

int DEngine::Core::CleanDX11()
{
    auto logger = getMultiSinkLogger();

    logger.info("Cleaning engine");

    CleanupDeviceD3D(dxContext);
    SDL_DestroyWindow(windowHandler);
    SDL_Quit();

    return 0;
}