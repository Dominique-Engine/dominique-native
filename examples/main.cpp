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
#include "../src/dengine/components/registration/registration.h"
#include "dengine/utils/fileLoader.h"

using namespace std;

int main() {
  DE App;
  auto scene = DE_CreateScene();
  DE_RegisterDefaultComponents(scene);

  DE_ObjHandle camObj;
  DE_CreateObj(scene, &camObj);

  // Template creations
  // const auto obj2Index = DE_CreateObj(scene, CAMERA_TEMPLATE);
  // Adding components/traits
  // const auto t = obj.addTrait(TRANSFORM);
  DE_Camera* cam;
  DE_GetCamera(camObj, &cam);
  cam->eye;
  DE_GetComponent(camObj, scene->componentIds.Transform, nullptr);

  // t2.setTransform(t);
  // no idea yet for supporting custom traits


  DE_Init(App);
  DE_Run(App, scene);
  DE_DestroyScene(&scene);
  DE_Clean(App);

  return 0;
}
