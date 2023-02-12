#include "coreDX11.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>
#include <d3d11.h>
#include <dengine/spdlog_helper.h>

#include "dx11_helpers.h"

DEDirectX11Context _dxContext;

int dengine::core::InitDX11(DE &engine) {
  auto logger = getMultiSinkLogger();

  // initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    logger.error("Couldn't initialize SDL: {}", SDL_GetError());
    return 1;  // sdl could not initialize
  }
  // clean up SDL
  atexit(SDL_Quit);

  // Also request a depth buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // if succeeded create our window
  engine.windowHandler = SDL_CreateWindow(
      engine.config.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      engine.config.width, engine.config.height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  if (engine.windowHandler == NULL) {
    logger.error("Couldn't set video mode: {}", SDL_GetError());
    return 1;
  }

  // if the window creation succeeded create our renderer
  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(engine.windowHandler, &wmInfo);
  HWND hwnd = (HWND)wmInfo.info.win.window;

  // Initialize Direct3D
  if (!CreateDeviceD3D(hwnd, _dxContext, false)) {
    logger.error("Failed to initialize DirectX");
    CleanupDeviceD3D(_dxContext);
    return 1;
  }

  DXGI_ADAPTER_DESC tempDescription;
  GetDefaultAdapterDesc(tempDescription);

  // Turn this into some useful information
  logger.info("DirectX11 loaded");
  std::wstring_view ws(tempDescription.Description);
  std::string s(ws.begin(), ws.end());
  logger.info("Vendor:   {}, Renderer: {}, Version:  {}",
              tempDescription.VendorId, s,
              _dxContext.pd3dDevice->GetFeatureLevel());

  return 0;
}

void dengine::core::RenderDX11(DE &engine) {
  _dxContext.pd3dDeviceContext->OMSetRenderTargets(
      1, &_dxContext.mainRenderTargetView, NULL);
  _dxContext.pd3dDeviceContext->ClearRenderTargetView(
      _dxContext.mainRenderTargetView, engine.config.clearColor);
  _dxContext.pSwapChain->Present(1, 0);  // Present with vsync
}

int dengine::core::CleanDX11(DE &engine) {
  auto logger = getMultiSinkLogger();

  logger.info("Cleaning engine");

  CleanupDeviceD3D(_dxContext);
  SDL_DestroyWindow(engine.windowHandler);
  SDL_Quit();

  return 0;
}