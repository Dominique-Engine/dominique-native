#ifndef APP_VERSION
#define APP_VERSION "0.0.0"
#endif
// #define SDL_MAIN_HANDLED//not needed in msvc,need to enable this from cmake,
// now is needed in msvc, wtf #define RC_INVOKED//this shouldn't be done

#ifndef APP_VERSION
#define APP_VERSION "0.0.0"
#endif

#include <iomanip>
#include <iostream>
#include <sstream>

#include "dengine/ecs/ecs.hpp"
#include "dengine/core.h"
#include "dengine/sdl_helpers.h"
#include "dengine/spdlog_helper.h"
#include "dengine/utils/uuid.h"

using namespace std;

int main(void) {
  auto logger = getMultiSinkLogger();
  logger.info("TEsting");

  // ecs Example use
  struct TransformComponent {
    float position{1.0f};
    float rotation{2.0f};
  };
  struct TagIdComponent {
    int id{2};
  };
  logger.info("TransformComponent ID: {}",
              dengine::ecs::GetId<TransformComponent>());
  logger.info("TagId ID: {}", dengine::ecs::GetId<TagIdComponent>());

  dengine::ecs::Scene scene;
  dengine::ecs::EntityID newEnt = scene.NewEntity();
  scene.Assign<TransformComponent>(newEnt);
  auto t = scene.Get<TransformComponent>(newEnt);
  t->position = 3.0f;
  logger.info("TransformComponent position: {}",
              scene.Get<TransformComponent>(newEnt)->position);

  // UUIDS
  logger.info("UUID: {}", dengine::Utils::uuids::getuuid().to_string());
  logger.info("UUID: {}", generate_hex(13));

  // Graphical App
  dengine::DE App;
  App.rendererType = dengine::RendererType::OpenGl;
  App.config.title = "dengine App";
  App.config.width = 800;
  App.config.height = 600;

  dengine::logSDL2renderersInfo();

  dengine::core::Init(App);
  dengine::core::Run(App);
  dengine::core::Clean(App);

  return 0;
}
