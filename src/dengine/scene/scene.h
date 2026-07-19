#pragma once

#include "dengine/components/types.hpp"
#include "dengine/components/registration/default_components.h"
#include "dengine/error/error.h"

typedef u32 ComponentId;

typedef struct ObjectId {
  u32 index;
  u32 generation;
} ObjectId;

typedef struct DE_Scene {
  DE_DefaultComponents componentIds;
  void *raw_internals;
} DE_Scene;

typedef struct DE_ComponentDescriptor {
  u32 size;
  u32 alignment;
} DE_ComponentDescriptor;

typedef struct DE_ObjHandle {
  DE_Scene const *const scene = nullptr;
  ObjectId id = {0, 0};
} DE_ObjHandle;

DE_Scene *DE_CreateScene();

// pointer to a pointer to modify callers pointer and avoid double free UB
void DE_DestroyScene(DE_Scene **scene);

ComponentId DE_RegisterComponent(DE_Scene *scene, DE_ComponentDescriptor desc,
                                 DE_Error **err = nullptr);

DE_ObjHandle DE_CreateObj(DE_Scene *scene, DE_Error **err);

void DE_AddComponent(DE_ObjHandle obj, ComponentId componentId);

DE_Result DE_GetComponent(DE_ObjHandle obj, ComponentId componentId,
                          void **data);

DE_Result DE_SetComponent(DE_ObjHandle obj, ComponentId id, void const *data);
