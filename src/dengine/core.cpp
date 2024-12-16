#include "core.h"

#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// #include "dx11/coreDX11.h"
#include "openGL/coreGL.h"
#include "sdl_helpers.h"
// #include "spdlog_helper.h"
#include "components/scriptable.hpp"
#include "components/camera.hpp"

// This needs to be compiled to allow ecs module to work correctly
int s_componentCounterDEngine = 0;

// This implementations are temporal, need to avoid the overhead of using switch
// to select different implementations, here is not a problem because this
// functions are called only couple of times and are not performance sensitive
// but should be avoided for more frecuent functions
int de::core::Init(DE &engine) {
  int result;
  // auto logger = getMultiSinkLogger();

  switch (engine.rendererType) {
    // case RendererType::DirectX11:
    //   result = InitDX11(engine);
    //   break;
    case RendererType::OpenGl:
      result = InitGL(engine);
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
    {
      // logger.warn("Could not load windows icon");
    }
    else
      SDL_SetWindowIcon(engine.windowHandler, surface);
    // ...and the surface containing the icon pixel data is no longer required.
    SDL_FreeSurface(surface);
  }

  return result;
}

int de::core::Clean(DE &engine) {
  switch (engine.rendererType) {
    // case RendererType::DirectX11:
    //   return CleanDX11(engine);
    //   break;
    case RendererType::OpenGl:
      return CleanGL(engine);
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
  std::function<void(de::DE & engine, de::ecs::Scene & scene,
                     de::core::RenderTargetGL & target)>
      renderer;

  switch (engine.rendererType) {
    // case RendererType::DirectX11:
    //   renderer = SetupRendererDX11(engine);
    //   break;
    case RendererType::OpenGl:
      renderer = SetupRendererGL(engine, scene);
      break;
    default:
      break;
  }

  de::core::RenderTargetGL renderTarget;
  for (de::ecs::EntityID ent :
       de::ecs::SceneView<de::components::Camera>(scene)) {
    auto camera = scene.Get<de::components::Camera>(ent);
    renderTarget.model = glm::rotate(renderTarget.model, glm::radians(-55.0f),
                                     glm::vec3(1.0f, 0.0f, 0.0f));
    int w, h;
    SDL_GetWindowSize(engine.windowHandler, &w, &h);
    renderTarget.view =
        glm::translate(renderTarget.view, glm::vec3(0.0f, 0.0f, -3.0f));
    renderTarget.projection = glm::perspective<float>(
        glm::radians(camera->fov), w / h, camera->near, camera->far);
  }

  SDL_Event event;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
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