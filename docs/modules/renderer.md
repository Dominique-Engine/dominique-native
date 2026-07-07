# Module: Renderer

## Purpose

The renderer turns extracted scene data into images.

It should be production-usable, but also easy to inspect, replace, benchmark, and document.

The renderer is not a single monolithic system. It should be a set of cooperating modules with explicit contracts:

- asset data enters as meshes, materials, and textures
- resources are exposed through handles
- scene extraction produces renderer-readable data
- render passes are scheduled through the render graph
- backend-specific details stay behind capability checks

## Current implementation status

The current implementation is a clear-pass SDL_GPU baseline, not Renderer v1.

Implemented today:

- SDL initialization
- window creation
- SDL_GPU device creation
- swapchain texture acquisition
- one clear render pass
- command buffer submission

Not implemented yet:

- renderer resource handles
- render graph passes
- mesh draw submission
- visibility buffer
- material shading pass
- GPU culling
- indirect draw generation
- bindless-style material or texture lookup

## Renderer v1 direction

The proposed v1 direction is:

```text
Bindless-first renderer
+ Visibility buffer
+ GPU-driven draw generation
+ LLM-native module contracts
```

This does not mean Dominique needs every advanced GPU feature on day one.

It means the renderer should be shaped around these ideas from the start:

- CPU prepares data.
- GPU decides what is visible.
- Shaders fetch resources through handles.
- Renderer internals are documented as replaceable units.

Meshlets are intentionally deferred. The renderer should be meshlet-ready, but v1 should not require meshlets, mesh shaders, or clustered geometry.

## Pipeline overview

Target flow:

```text
Asset Pipeline
  ↓
Meshes / Materials / Textures
  ↓
GPU Resource Tables
  ↓
Scene Extraction
  ↓
GPU Culling
  ↓
Indirect Draw Commands
  ↓
Visibility Buffer
  ↓
Material Shading Pass
  ↓
Lighting / Postprocess
```

A v0 implementation can use CPU scene lists and simple handles while still writing a visibility buffer with object and material IDs.

A v1 implementation can move frustum culling and draw command generation to the GPU, then use bindless-style lookup for material and texture access.

## Submodules

### Resource table / bindless handles

The resource table maps stable renderer handles to GPU resources.

Examples:

- `MeshHandle`
- `MaterialHandle`
- `TextureHandle`
- `SamplerHandle`

Early implementations can back these handles with CPU arrays and explicit binds.

Later implementations can expose GPU-visible tables, descriptor arrays, or native bindless resources when the backend supports them.

The public contract should be handle-based either way.

### Visibility buffer

The visibility buffer stores compact visibility information instead of full material attributes.

A simple starting point is:

- depth
- object ID
- material ID
- primitive or draw ID when available

The material shading pass then reads those IDs, fetches mesh/material data, and computes final surface values.

This keeps geometry visibility separate from material evaluation.

### GPU culling

GPU culling evaluates which renderables should be drawn.

v1 should start with frustum culling over normal mesh instances.

Later versions can add:

- occlusion culling
- GPU LOD
- clustered geometry
- meshlet visibility

### Indirect draw generation

Indirect draw generation converts visible objects into draw commands consumed by the graphics pipeline.

This is the bridge between a CPU scene list and a more GPU-driven renderer.

The first implementation can keep the command format simple and focused on indexed mesh draws.

### Material system

Materials should reference resources by handle, not by hidden direct binding.

A material record should be compact enough to upload and read from shaders.

The system should support a small PBR material first, then grow through documented extensions.

### Render graph integration

The render graph should describe pass dependencies and resource lifetimes.

The renderer should express major passes explicitly:

- scene extraction upload
- culling
- indirect command generation
- visibility pass
- material shading pass
- lighting
- postprocess

The render graph should make these passes visible to debugging and documentation tools.

## Out of scope for v1

The following are future work, not v1 requirements:

- meshlets
- mesh shaders
- object shaders
- work graphs
- ray tracing
- neural rendering

These topics can still have research docs and experiments, but they should not be required by the main renderer path.

## Future-ready design

The v1 design keeps the door open by using:

- handles instead of direct binding
- GPU-readable material and instance data
- explicit pass boundaries
- capability checks instead of backend checks
- indirect draw command generation
- module docs that describe inputs, outputs, and limitations

A later meshlet renderer should be able to replace the culling and draw-generation submodules without changing the whole engine identity.

## Examples

Initial examples should show:

1. textured mesh through resource handles
2. visibility buffer debug view
3. GPU frustum culling debug counters
4. material lookup through handle tables
5. render graph view of renderer passes

## Open questions

- How much bindless-style lookup can be expressed through SDL_GPU portably?
- What is the first stable handle format?
- How should resource lifetime validation report errors?
- How should shader hot reload interact with material table layouts?
- Which visibility-buffer debug views should exist by default?
