# Research: GPU-driven Rendering

## Problem

CPU draw submission does not scale well with many objects, materials, and visibility decisions.

A CPU-driven renderer must repeatedly decide what is visible, sort or group draw calls, bind resources, and submit commands.

That path is easy to understand at first, but it becomes a bottleneck as scenes grow.

## Idea

Move visibility, LOD, and draw generation toward the GPU.

Typical path:

```text
compute shader
  ↓
visible object list
  ↓
indirect draw commands
  ↓
graphics pipeline
```

Dominique's proposed renderer path makes this more concrete:

```text
GPU culling
  ↓
indirect draw commands
  ↓
visibility buffer
  ↓
material shading
```

## Why it matters

GPU-driven rendering is the bridge between a traditional renderer and future rendering research.

It supports the v1 direction:

- bindless-style resources
- visibility-buffer rendering
- indirect draw command generation
- explicit renderer submodules

It also leaves room for future work:

- occlusion culling
- GPU LOD
- meshlets
- mesh shaders / object shaders
- work graphs

Meshlets are future work. They should not be required for the first GPU-driven renderer path.

## Implementation path

### v0

1. Extract a CPU scene list.
2. Assign stable object and material IDs.
3. Draw indexed meshes normally.
4. Write a visibility buffer.
5. Keep the data layout close to what the GPU path will need later.

### v1

1. Upload renderable records to GPU-readable buffers.
2. Run GPU frustum culling.
3. Write visible draw records.
4. Generate indirect draw commands.
5. Execute a visibility pass from indirect commands.
6. Shade through material and texture handles.

### v2

1. Add occlusion culling.
2. Add GPU LOD.
3. Improve resource streaming.
4. Add better debug counters and validation.

### Future

1. Add meshlet or clustered geometry experiments.
2. Explore mesh shaders or object shaders where available.
3. Explore work graphs on APIs and hardware that support them.

## Relationship to bindless resources

GPU-generated draws need a way to identify resources without CPU binding for every draw.

Resource handles and GPU-readable tables provide that contract.

The GPU can produce or consume records such as:

```cpp
struct RenderableRecord {
    uint32_t meshIndex;
    uint32_t materialIndex;
    uint32_t transformIndex;
};
```

The renderer can then resolve those indices during the visibility and material passes.

## Relationship to visibility buffers

A visibility buffer is a good first consumer of GPU-generated draw commands.

The culling pass decides what may be visible.

The indirect draw pass writes per-pixel visibility IDs.

The material pass resolves those IDs into shading data.

This keeps visibility, draw generation, and material shading separate enough to inspect and replace.

## Trade-offs

- Debugging moves from CPU draw lists to GPU buffers and counters.
- Synchronization and resource lifetime become more important.
- Portable APIs may expose different levels of indirect drawing support.
- The renderer needs strong validation tools to avoid opaque failures.
- Simple scenes may not benefit immediately, so examples should show both clarity and scale.

## Learning path

1. CPU culling
2. GPU-readable renderable records
3. compute frustum culling
4. indirect draws
5. visibility-buffer integration
6. GPU LOD
7. occlusion culling
8. meshlet visibility as future work
9. work graph experiments as future work