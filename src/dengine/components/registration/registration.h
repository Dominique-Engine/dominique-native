#pragma once


#include "../camera.hpp"
#include "../transform.hpp"
#include "dengine/error/error.h"
#include "dengine/scene/scene.h"

DE_Result DE_RegisterDefaultComponents(DE_Scene *scene);

DE_Result DE_GetCamera(DE_ObjHandle obj_desc, DE_Camera **v);

DE_Result DE_SetCamera(DE_ObjHandle obj_desc, DE_Camera **v);

DE_Result DE_GetTransform(DE_ObjHandle obj_desc, DE_Transform **v);

DE_Result DE_SetCamera(DE_ObjHandle obj_desc, DE_Transform **v);
