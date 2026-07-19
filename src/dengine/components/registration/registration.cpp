#include "registration.h"

void DE_RegisterDefaultComponents(DE_Scene *scene, DE_Error **err) {
  DE_DefaultComponents res;
  res.Camera =
      DE_RegisterComponent(scene, {sizeof(DE_Camera), alignof(DE_Camera)});
  res.Transform = DE_RegisterComponent(
      scene, {sizeof(DE_Transform), alignof(DE_Transform)});
  scene->componentIds = res;
};

DE_Camera * DE_GetCamera(const DE_ObjHandle obj_desc, DE_Error **err) {
  return (DE_Camera *) DE_GetComponent(obj_desc, obj_desc.scene->componentIds.Camera, err);
};

const DE_Camera *DE_SetCamera(const DE_ObjHandle obj_desc, const DE_Camera *v) {
  return (const DE_Camera *)DE_SetComponent(
      obj_desc, obj_desc.scene->componentIds.Camera, (void *)v);
}

DE_Result DE_GetTransform(const DE_ObjHandle obj_desc, DE_Transform **out_v) {
  DE_GetComponent(obj_desc, obj_desc.scene->componentIds.Transform,
                  (void **)out_v);
  return DE_OK;
};

const DE_Transform *DE_SetTransform(const DE_ObjHandle obj_desc,
                                    const DE_Transform **v) {
  return (const DE_Transform *)DE_SetComponent(
      obj_desc, obj_desc.scene->componentIds.Transform, (void **)v);
}
