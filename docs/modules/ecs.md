# Module: ECS

## What problem does this solve?

The ECS stores entities and components so scene data can be composed without a
deep inheritance hierarchy. It gives Dominique a small data-oriented baseline
for attaching camera, script, transform, mesh, and material data to entities.

## Why did old engines solve it differently?

Older engines often centered the scene around object hierarchies, virtual
methods, and large actor classes. That is easy to understand at first, but it
can make data layout, iteration, serialization, and replacement harder as a
project grows.

## What is the naive implementation?

A naive ECS can store a list of entities and a separate array or map for each
component type. Iteration checks which entities have the requested components
and returns matching entity IDs.

## What is the modern implementation?

A modern implementation usually makes component storage explicit and cache
friendly. Common designs include sparse sets, archetype chunks, structure of
arrays layouts, stable handles with generations, and job-friendly iteration.

## How do large engines scale it?

Large engines usually add reflection or registration metadata, serialization,
editor integration, streaming, parallel iteration, dependency ordering for
systems, deterministic IDs, and tooling for inspecting component storage.

## What are the trade-offs?

The current ECS is small and easy to inspect, which fits the learning goal.
The trade-off is that it is not yet a robust production ECS.

Current limitations include:

- component IDs come from a process-global counter
- `MAX_ENTITIES` and `MAX_COMPONENTS` are fixed constants
- component storage uses raw byte pools and placement new
- removed components are not destructed
- `Get` does not validate the entity UUID before indexing
- there is no serialization, reflection, scheduling, or benchmark suite

## What future technologies may replace it?

The current ECS could be replaced by a sparse-set ECS, an archetype ECS, or a
hybrid scene/entity model. A future renderer may also consume extracted scene
records instead of reading ECS data directly.

## How is this implemented in Dominique?

The ECS is implemented in `src/dengine/ecs/ecs.hpp`.

The main public types are:

- `de::ecs::EntityID`
- `de::ecs::Scene`
- `de::ecs::SceneView`
- `de::ecs::ComponentMask`

`EntityID` stores an index and UUID. `Scene` stores entity descriptions, a free
list, and one component pool per component type. `SceneView` iterates matching
entities for a list of component types.

`s_componentCounterDEngine` must be defined by one translation unit. The engine
defines it in `src/dengine/core.cpp`; tests define it in `tests/test_support.cpp`.

## How do I replace this implementation?

Preserve the current public usage until a deliberate API migration is documented:

```cpp
de::ecs::Scene scene;
auto entity = scene.NewEntity();
scene.Assign<MyComponent>(entity);
auto component = scene.Get<MyComponent>(entity);
for (auto id : de::ecs::SceneView<MyComponent>(scene)) {
}
```

A replacement should update this doc, add an ADR if the public model changes,
and keep the ECS tests passing or replace them with equivalent coverage.

## Examples and benchmarks

Examples exist in the README and in `tests/test_ecs.cpp`.

Current validation:

- `ecs_tests` checks component IDs, entity creation/destruction,
  assign/get/remove, and `SceneView` iteration

Benchmarks do not exist yet. The first useful benchmark would compare iteration
over one component and two-component views at different entity counts.
