#include "scene.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ecs/ecs.hpp"

constexpr auto DEFAULT_POOL_SIZE = 5000;

struct DEI_ComponentPool {
  ComponentId componentId;
  u32 itemSize;
  u32 alignment;
  u32 length{0};
  std::vector<u8> pData;
  // Track deletions
  std::vector<bool> present;

  DEI_ComponentPool(ComponentId componentId, u32 itemSize, u32 alignment) {
    this->itemSize = itemSize;
    this->alignment = alignment;
    this->componentId = componentId;
    pData.reserve(itemSize * DEFAULT_POOL_SIZE);
    present.reserve(DEFAULT_POOL_SIZE);
    std::fill(present.begin(), present.end(), false);
  }

  ~DEI_ComponentPool() {
    // NOOP for now, but needed when switching std vectors for new
    // implementation
  }

  inline void *get(u32 index) {
    // looking up the component at the desired index
    return &pData + index * itemSize;
  }

  // returns componentIndex
  u32 reserve_value() {
    const auto reusable = std::ranges::find(present, false);
    if (reusable != present.end()) {
      *reusable = true;
      return std::distance(present.begin(), reusable);
    }
    length += 1;
    present.push_back(true);
    return length - 1;
  }
};

struct DEI_ObjSlot {
  u32 index;
  // The generation prevents an old handle from accessing a newly reused object
  // slot.
  u32 generation;
  // Index is component id, value is component pool index for object's component
  // data
  std::vector<u32> componentsIndexes;
  std::unordered_set<ComponentId> componentsPresence;
};

struct DEI_SceneImpl {
  std::vector<DEI_ObjSlot> objects;
  std::vector<DEI_ComponentPool> componentPools;
};

DE_Scene *DE_CreateScene() {
  auto scene = new DE_Scene();
  scene->raw_internals = new DEI_SceneImpl();
  return scene;
}

DEI_SceneImpl *GetSceneImpl(const DE_Scene *scene) {
  if (scene == nullptr) return nullptr;
  return static_cast<DEI_SceneImpl *>(scene->raw_internals);
}

void DE_DestroyScene(DE_Scene **scene) {
  if (scene == nullptr) return;
  auto *sceneImpl = GetSceneImpl(*scene);
  if (sceneImpl == nullptr) return;
  delete sceneImpl;
  sceneImpl = nullptr;
  delete *scene;
}

DE_Result DE_RegisterComponent(DE_Scene *scene, DE_ComponentDescriptor desc,
                               ComponentId *out_id) {
  auto sceneImpl = GetSceneImpl(scene);
  if (sceneImpl == nullptr) return DE_ERR;
  *out_id = sceneImpl->componentPools.size();
  sceneImpl->componentPools.emplace_back(
      DEI_ComponentPool({*out_id, desc.size, desc.alignment}));
  return DE_OK;
}

DE_Result DE_CreateObj(DE_Scene *scene, DE_ObjHandle *out_obj) {
  auto sceneImpl = GetSceneImpl(scene);
  if (sceneImpl == nullptr) return DE_ERR;

  const u32 objectIndex = sceneImpl->objects.size();
  sceneImpl->objects.push_back({objectIndex, 0});
  new (out_obj) DE_ObjHandle({
      scene,
      {objectIndex, 0},
  });

  return DE_OK;
}

DE_Result DE_AddComponent(const DE_ObjHandle obj,
                          const ComponentId componentId) {
  auto sceneImpl = GetSceneImpl(obj.scene);
  if (sceneImpl == nullptr) return DE_ERR;

  // on safer impl this could be asert
  if (sceneImpl->componentPools.size() >= componentId) return DE_OUT_OF_BONDS;
  if (sceneImpl->objects.size() >= obj.id.index) return DE_OUT_OF_BONDS;

  if (sceneImpl->objects[obj.id.index].componentsPresence.contains(componentId))
    return DE_OK;
  sceneImpl->objects[obj.id.index].componentsPresence.insert(componentId);

  if (sceneImpl->objects[obj.id.index].componentsIndexes.size() < componentId) {
    sceneImpl->objects[obj.id.index].componentsIndexes.resize(componentId);
  }
  sceneImpl->componentPools[componentId].reserve_value(
      &sceneImpl->objects[obj.id.index].componentsIndexes[componentId]);

  return DE_OK;
};

void *data DE_GetComponent(DE_ObjHandle obj, ComponentId componentId,
                          DE_Error **err) {
  const auto sceneImpl = GetSceneImpl(obj.scene);
  if (sceneImpl == nullptr) {
    **err = DE_ERR;
    return nullptr;
  };

  const auto objSlotItem = sceneImpl->objects[obj.id.index];
  // on safer impl this could be asert
  if (!objSlotItem.componentsPresence.contains(componentId)) return DE_ERR;
  if (objSlotItem.componentsIndexes.size() < componentId)
    return DE_OUT_OF_BONDS;
  *data = sceneImpl->componentPools[componentId].get(
      objSlotItem.componentsIndexes[componentId]);
  return DE_OK;
};

DE_Result DE_SetComponent(DE_ObjHandle obj, ComponentId id, void const *data) {
  if (data == nullptr) return DE_ERR;
  const auto sceneImpl = GetSceneImpl(obj.scene);
  if (sceneImpl == nullptr) return DE_ERR;

  return DE_OK;
};
