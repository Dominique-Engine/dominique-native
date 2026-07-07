# Architecture Principles

## Stable public API, replaceable implementations

The public API should change slowly.

Implementations should be replaceable.

Example:

```text
Renderer API
  ├── SDL_GPU Renderer
  ├── Native Vulkan Renderer
  ├── Native Metal Renderer
  ├── Native D3D12 Renderer
  └── Software Renderer
```

## Design for future techniques without depending on them too early

Architecture should leave room for future techniques such as meshlets, mesh shaders, work graphs, ray tracing, and neural rendering.

The first implementation should not depend on those techniques unless they are required for the current milestone.

Example:

```text
Mesh data layout
  ├── works with indexed draws today
  └── can be converted to clustered geometry later
```

## Capabilities over APIs

Code should ask:

```cpp
if (capabilities.bindlessResources) { ... }
```

not:

```cpp
if (backend == Vulkan) { ... }
```

## Resource handles over direct binding

Renderer-facing data should prefer explicit handles, indices, or descriptors over direct per-draw binding.

This keeps the public model closer to modern rendering:

```cpp
struct MaterialHandle {
    uint32_t index;
};
```

The handle can point to a simple CPU table in an early implementation and a GPU-visible resource table later.

## GPU-readable data layouts early

Data that will eventually be consumed by compute shaders, indirect draws, or material shaders should be designed with GPU readability in mind.

This does not require moving every decision to the GPU immediately.

It means avoiding layouts that are convenient only for CPU-side object graphs and hard to upload, validate, or inspect.

## Explicit contracts, not hidden shared state

Modules should communicate through explicit inputs, outputs, handles, events, and capability declarations.

Avoid hidden shared state between modules.

Example:

```text
Scene extraction
  → renderable list
  → resource handles
  → render graph pass data
```

This makes modules easier to replace, document, benchmark, and modify with coding agents.

## Modern-first, not legacy-first

Avoid building around old OpenGL-style state-machine design.

Start from modern explicit rendering concepts:

- command buffers
- pipelines
- resources
- descriptors
- render passes
- compute
- synchronization
- render graphs

## Small modules

A module should solve one clear problem.

Each module should have:

- overview
- public API
- implementation notes
- examples
- tests
- known limitations

## Examples as tests

Every major feature should have a runnable example.

Examples should be treated as documentation and regression tests.