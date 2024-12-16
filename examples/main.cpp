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
// #include "dengine/spdlog_helper.h"
#include "dengine/utils/uuid.h"
#include "dengine/components/scriptable.hpp"
#include "dengine/components/camera.hpp"
#include "dengine/utils/fileLoader.h"
#include <glm/glm.hpp>

using namespace std;

int main(void) {
  de::DE App;

  de::logSDL2renderersInfo();

  // Scene setup
  de::ecs::Scene scene;

  // Testing camera setup
  de::ecs::EntityID camera = scene.NewEntity();
  scene.Assign<de::components::Camera>(camera);
  auto cameraComponent = scene.Get<de::components::Camera>(camera);

  // getMultiSinkLogger().info("Loading gltf");
  de::utils::LoadGLTF("WaterBottle.gltf");
  de::utils::LoadObj("Prop_Tree_Palm_3.obj");

  de::core::Init(App);
  de::core::Run(App, scene);
  de::core::Clean(App);

  return 0;
}
