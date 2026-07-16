#pragma once

#include "config/config.h"
#include "scene/scene.h"

int DE_Init(DE &engine);

int DE_Clean(DE &engine);

void DE_Render(DE &engine, DE_Scene &scene);

void DE_Run(DE &engine, DE_Scene &scene);
