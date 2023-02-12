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
  // Graphical App
  dengine::DE App;
  App.rendererType = dengine::RendererType::OpenGl;
  App.config.title = "DEngine App";
  App.config.width = 800;
  App.config.height = 600;

  dengine::logSDL2renderersInfo();

  dengine::core::Init(App);
  dengine::core::Run(App);
  dengine::core::Clean(App);

  return 0;
}
