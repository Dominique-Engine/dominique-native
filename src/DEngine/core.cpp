#include "core.h"

#include <SDL2/SDL.h>

#include "dx11/coreDX11.h"
#include "openGl/coreGL.h"
#include "sdl_helpers.h"
#include "spdlog_helper.h"

// This implementations are temporal, need to avoid the overhead of using switch
// to select different implementations, here is not a problem because this
// functions are called only couple of times and are not performance sensitive
// but should be avoided for more frecuent functions
int dengine::core::Init(DE &engine) {
  int result;
  auto logger = getMultiSinkLogger();

  switch (engine.rendererType) {
    case RendererType::DirectX11:
      result = InitDX11(engine);
      break;
    case RendererType::OpenGl:
      result = InitGL(engine);
      break;
    case RendererType::Vulkan:
      // result = InitVK(engine);
      break;
    default:
      break;
  }

  if (result == 0) {
    SDL_Surface *surface = loadImgFromFile2SDLSurface(
        "icon.png");  // Declare an SDL_Surface to be filled in with pixel data
                      // from an image file

    // The icon is attached to the window pointer
    if (surface == nullptr)
      logger.warn("Could not load windows icon");
    else
      SDL_SetWindowIcon(engine.windowHandler, surface);
    // ...and the surface containing the icon pixel data is no longer required.
    SDL_FreeSurface(surface);
  }

  return result;
}

int dengine::core::Clean(DE &engine) {
  switch (engine.rendererType) {
    case RendererType::DirectX11:
      return CleanDX11(engine);
      break;
    case RendererType::OpenGl:
      return CleanGL(engine);
      break;
    case RendererType::Vulkan:
      // return CleanVK();
      break;
    default:
      break;
  }
}

void dengine::core::Render(DE &engine) {
  // switch (engine.rendererType)
  // {
  //     case RendererType::DirectX11 :
  //         return RenderDX11(engine);
  //         break;
  //     case RendererType::OpenGl :
  //         return RenderGL(engine);
  //         break;
  //     case RendererType::Vulkan :
  //         // return RenderVK();
  //         break;
  //     default:
  //         break;
  // }
}

void dengine::core::Run(DE &engine) {
  auto renderer = RenderDX11;

  switch (engine.rendererType) {
    case RendererType::DirectX11:
      break;
    case RendererType::OpenGl:
      renderer = RenderGL;
      break;
    case RendererType::Vulkan:
      // renderer = RenderVK;
      break;
    default:
      break;
  }

  SDL_Event event;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
    renderer(engine);
  }
}