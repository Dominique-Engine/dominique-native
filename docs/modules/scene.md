# Module: Scene

## What problem does this solve?

The scene module should describe the world state that systems and renderer
modules consume. It is the boundary between authored or runtime objects and the
renderer-facing data extracted from them.

## Why did old engines solve it differently?

Older engines often treated the scene as a tree of objects with transform,
rendering, physics, and scripting behavior mixed together. That model is easy to
visualize, but it can make data extraction and subsystem replacement harder.

## What is the naive implementation?

A naive scene can be a list of entities with transform, mesh, material, camera,
and script components. Systems can iterate those components directly.

## What is the modern implementation?

A modern scene layer separates authoring/runtime state from extracted subsystem
data. The renderer should receive explicit renderable records, handles, and
camera data instead of reaching through arbitrary object graphs.

## How do large engines scale it?

Large engines add scene streaming, prefab or entity templates, editor metadata,
hierarchical transforms, visibility structures, serialization, networking,
world partitioning, and extraction stages for renderer, physics, audio, and
tools.

## What are the trade-offs?

Dominique currently uses the ECS as the scene baseline. That is easy to inspect,
but it means there is not yet a distinct scene module contract.

Current limitations include:

- no scene document or asset format
- no hierarchy or transform propagation
- no scene extraction stage
- no renderer-facing renderable record list
- no scene streaming or serialization
- no editor/tooling metadata

## What future technologies may replace it?

The scene layer may become a world/scene graph, an ECS-backed world, or a hybrid
model with explicit extraction stages. Renderer-facing records should stay
separate enough that the scene implementation can change.

## How is this implemented in Dominique?

There is no separate scene module yet.

Current scene-like behavior lives in:

- `de::ecs::Scene` in `src/dengine/ecs/ecs.hpp`
- component structs under `src/dengine/components/`
- camera and update iteration in `src/dengine/core.cpp`

## How do I replace this implementation?

Define the scene contract before adding more scene behavior. The first stable
contract should explain how scene data is extracted into:

```text
camera data
renderable records
resource handles
update/system inputs
```

If a replacement changes public ECS usage, update `docs/modules/ecs.md` and the
README examples as well.

## Examples and benchmarks

`examples/main.cpp` creates a `de::ecs::Scene`, but there is no dedicated scene
example yet.

There are no scene benchmarks. The first useful validation target is a scene
extraction test that turns transform, mesh, and material components into stable
renderer records.
