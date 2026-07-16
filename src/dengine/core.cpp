#include "core.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "sdl_gpu/core.h"

#include <format>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "sdl/sdl_helpers.h"
#include "components/scriptable.hpp"
#include "components/camera.hpp"
#include <functional>

using namespace de::utils::logger;

// This needs to be compiled to allow ecs module to work correctly
int s_componentCounterDEngine = 0;

// This implementations are temporal, need to avoid the overhead of using switch
// to select different implementations, here is not a problem because this
// functions are called only couple of times and are not performance sensitive
// but should be avoided for more frecuent functions
int de::core::Init(DE &engine) {
  int result = 0;

  switch (engine.rendererType) {
    case RendererType::SDL_gpu:
      result = sdl_gpu::Init(engine);
      break;
    default:
      break;
  }

  if (result == 0) {
    SDL_Surface *surface = loadImgFromFile2SDLSurface(
      "icon.png"); // Declare an SDL_Surface to be filled in with pixel data
    // from an image file

    // The icon is attached to the window pointer
    if (surface == nullptr) {
      Logger::warn("Could not load windows icon");
    } else
      SDL_SetWindowIcon(engine.windowHandler, surface);
    // ...and the surface containing the icon pixel data is no longer required.
    SDL_DestroySurface(surface);
  }

  return result;
}

int de::core::Clean(DE &engine) {
  switch (engine.rendererType) {
    case RendererType::SDL_gpu:
      return sdl_gpu::Clean(engine);
      break;
    default:

      break;
  }
}

void de::core::Render(DE &engine) {
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

void de::core::Run(DE &engine, de::ecs::Scene &scene) {
  std::function<void(de::DE &engine,
                     de::ecs::Scene &scene,
                     de::core::RenderTarget &target)>
      renderer;

  switch (engine.rendererType) {
    case RendererType::SDL_gpu:
      renderer = sdl_gpu::SetupRenderer(engine, scene);
      break;
    default:
      break;
  }

  de::core::RenderTarget renderTarget;
  for (de::ecs::EntityID ent :
       de::ecs::SceneView<de::components::Camera>(scene)) {
    auto camera = scene.Get<de::components::Camera>(ent);
    renderTarget.model = glm::rotate(renderTarget.model,
                                     glm::radians(-55.0f),
                                     glm::vec3(1.0f, 0.0f, 0.0f));
    int w, h;
    if (!SDL_GetWindowSize(engine.windowHandler, &w, &h)) {
      Logger::warn(std::format("Could not get window size: %s", SDL_GetError()));
      return;
    }

    renderTarget.view =
        glm::translate(renderTarget.view, glm::vec3(0.0f, 0.0f, -3.0f));
    renderTarget.projection = glm::perspective<float>(
      glm::radians(camera->fov),
      w / h,
      camera->near,
      camera->far);
  }

  SDL_Event event;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    for (de::ecs::EntityID ent :
         de::ecs::SceneView<de::components::UpdateHandler>(scene)) {
      scene.Get<de::components::UpdateHandler>(ent)->handler();
    }

    // Handling camera
    for (de::ecs::EntityID ent :
         de::ecs::SceneView<de::components::Camera>(scene)) {
      auto camera = scene.Get<de::components::Camera>(ent);
      // TODO
    }

    renderer(engine, scene, renderTarget);
  }
}
