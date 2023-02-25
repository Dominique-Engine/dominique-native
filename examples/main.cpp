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
#include "dengine/components/scriptable.hpp"

using namespace std;

int main(void) {
  de::DE App;
  App.config.title = "DEngine App";
  App.config.width = 800;
  App.config.height = 600;

  de::logSDL2renderersInfo();

  // Scene setup
  de::ecs::Scene scene;

  // Testing hooking components to update method
  de::ecs::EntityID testUpdate = scene.NewEntity();

  scene.Assign<de::components::UpdateHandler>(testUpdate);
  auto testUpdateHandle = scene.Get<de::components::UpdateHandler>(testUpdate);

  testUpdateHandle->handler = []() {
    getMultiSinkLogger().info("From update handler");
  };

  de::core::Init(App);
  de::core::Run(App, scene);
  de::core::Clean(App);

  return 0;
}
