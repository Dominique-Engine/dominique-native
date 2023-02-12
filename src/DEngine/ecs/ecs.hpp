#pragma once
#include <bitset>
#include <vector>

// Seems good to use it in here, but not fully tested
int s_componentCounterDEngine = 0;

extern int s_componentCounterDEngine;

namespace dengine {
// This is a namespace for the ecs system
namespace ecs {

// This function will return a unique ID for each component type
template <class T>
int GetId() {
  static int s_componentId = s_componentCounterDEngine++;
  return s_componentId;
}

// Some typedefs to aid in reading
const int MAX_ENTITIES =
    32;  // WARN, TODO when this is too big SDL audio initialization crashes
const int MAX_COMPONENTS = 32;
typedef unsigned long long EntityID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

// Generic component pool, stores a block of memory for each component type
struct ComponentPool {
  ComponentPool(size_t elementsize) {
    // We'll allocate enough memory to hold MAX_ENTITIES, each with element size
    elementSize = elementsize;
    pData = new char[elementSize * MAX_ENTITIES];
  }

  ~ComponentPool() { delete[] pData; }

  inline void* get(size_t index) {
    // looking up the component at the desired index
    return pData + index * elementSize;
  }

  // Not sure why this is needed
  ComponentPool& ComponentPool::operator=(const ComponentPool* a) {
    pData = (*a).pData;
    elementSize = (*a).elementSize;
    return *this;
  }

  char* pData{nullptr};
  size_t elementSize{0};
};

// This is the scene, where we keep all our entities and components
struct Scene {
  // All the information we need about each entity
  struct EntityDesc {
    EntityID id;
    ComponentMask mask;
  };
  std::vector<EntityDesc> entities;
  std::vector<ComponentPool> componentPools;

  // Get a component from an entity
  template <typename T>
  T* Get(EntityID id) {
    int componentId = GetId<T>();
    if (!entities[id].mask.test(componentId)) return nullptr;

    T* pComponent = static_cast<T*>(componentPools[componentId].get(id));
    return pComponent;
  }

  // Create a new entity
  EntityID NewEntity() {
    entities.push_back({entities.size(), ComponentMask()});
    return entities.back().id;
  }

  // Assign a component to an entity
  template <typename T>
  T* Assign(EntityID id) {
    int componentId = GetId<T>();

    if (componentPools.size() <= componentId)  // Not enough component pool
    {
      componentPools.resize(componentId + 1, ComponentPool(sizeof(T)));
    }
    if (componentPools[componentId].pData ==
        nullptr)  // New component, make a new pool
    {
      componentPools[componentId] = new ComponentPool(sizeof(T));
    }

    // Looks up the component in the pool, and initializes it with placement new
    T* pComponent = new (componentPools[componentId].get(id)) T();

    entities[id].mask.set(componentId);
    return pComponent;
  }
};

}  // namespace ecs
}  // namespace dengine
