#ifndef APP_VERSION
#define APP_VERSION "0.0.0"
#endif

#ifndef APP_VERSION
#define APP_VERSION "0.0.0"
#endif

#include <iomanip>
#include <iostream>
#include <sstream>

#include "ecs/ecs.hpp"
#include "dengine/core.h"
#include "dengine/utils/uuid.h"
#include "dengine/components/scriptable.hpp"
#include "dengine/components/camera.hpp"
#include "dengine/utils/fileLoader.h"

using namespace std;

int main() {
  DE App;
  DE_Scene scene;
  DE_Init(App);
  DE_Run(App, scene);
  DE_Clean(App);

  return 0;
}
