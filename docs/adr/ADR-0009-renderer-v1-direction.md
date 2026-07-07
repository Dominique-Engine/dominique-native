# ADR-0009: Renderer v1 Direction

## Status

Proposed

## Context

Dominique needs a first serious renderer direction that is modern-first without becoming too speculative for v1.

The renderer should support games, creative coding, interactive visuals, simulations, visualization, tools, and rendering experiments.

It should also remain educational. Users should be able to inspect the renderer as a set of replaceable modules rather than a single opaque implementation.

Existing research directions include render graphs, bindless resources, GPU-driven rendering, meshlets, work graphs, sparse resources, and neural rendering.

The important ordering question is what belongs in the initial renderer path and what should remain future work.

## Decision

Dominique Renderer v1 will target a bindless-first, visibility-buffer-based, GPU-driven draw generation architecture, while intentionally deferring meshlets.

The target flow is:

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

The renderer should use explicit resource handles and GPU-readable data layouts early.

The initial implementation may be staged:

- v0: CPU scene list, simple resource handles, visibility buffer with object/material IDs.
- v1: GPU frustum culling, indirect draws, bindless-style material/texture lookup.
- v2: occlusion culling, GPU LOD, better resource streaming.
- v3/future: meshlets, mesh shaders/object shaders, work graphs.

Meshlets should influence future-ready data layout, but they should not be required for v1.

## Alternatives considered

### Classic forward renderer first

A classic forward renderer is simpler to implement and easier to debug.

It is still useful for a minimal baseline, but it does not strongly exercise the architecture Dominique wants to teach: explicit resources, GPU-readable scene data, and replaceable renderer passes.

### Classic deferred G-buffer first

A G-buffer renderer is familiar and useful, especially for lighting-heavy scenes.

However, it can encourage writing expanded material attributes too early and does not pair as directly with bindless material lookup as a visibility buffer.

### Meshlet-first renderer

A meshlet-first renderer is modern and valuable for research.

It is not the right first implementation path. It would add asset-processing, culling, shader, and backend complexity before the renderer has stable module contracts.

Dominique should remain meshlet-ready, but not meshlet-dependent.

### Backend-native renderer first

A native Vulkan, Metal, or D3D12 renderer could expose advanced GPU features sooner.

SDL_GPU remains the preferred initial backend for portability and focus. Native backends may become escape hatches for advanced experiments later.

## Consequences

The renderer docs and examples need to explain the pipeline as a sequence of modules.

Resource handles become a core public concept.

Renderer data should be shaped so it can be uploaded to GPU-readable buffers.

Capability checks become important because SDL_GPU may not expose every bindless or indirect rendering feature equally across platforms.

Debug views and validation become part of the renderer design, not optional polish.

The engine avoids overcommitting to meshlets before the simpler GPU-driven path exists.

## Future work

- Define stable handle types for meshes, materials, textures, buffers, and samplers.
- Specify the visibility-buffer format for v0 and v1.
- Define renderable records and indirect draw command generation.
- Document the material table layout.
- Add renderer capability checks for bindless-style resources and indirect draws.
- Add debug views for object IDs, material IDs, depth, culling results, and draw counts.
- Write a future ADR for native backend escape hatches.
- Write a future ADR for meshlet integration after the v1 renderer path exists.