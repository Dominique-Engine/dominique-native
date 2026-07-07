# Modern Engine Roadmap

## Main architectural themes

1. Render graphs
2. Bindless-style resource handles
3. Visibility-buffer rendering
4. GPU-driven draw generation
5. Sparse resources / virtual assets
6. Meshlets and clustered geometry
7. Work graphs
8. Neural rendering

These are not isolated tricks. They form an architectural progression, but Dominique should introduce them incrementally through usable modules.

Meshlets are important future research, but they are not part of the initial renderer implementation plan.

## Renderer v1 direction

The first serious renderer direction is:

```text
Bindless-first renderer
+ Visibility buffer
+ GPU-driven draw generation
+ LLM-native module contracts
```

The intent is:

- CPU prepares scene, asset, and resource data.
- GPU decides what is visible.
- Shaders fetch resources through handles.
- Renderer modules are documented as replaceable units.

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

This direction should remain meshlet-ready without becoming meshlet-dependent. Data layouts should leave room for clustered geometry later, but v1 should work with normal meshes and traditional indexed draws.

## Staged renderer milestones

### v0: Inspectable baseline

1. SDL3 window/input
2. SDL_GPU renderer
3. triangle
4. textured mesh
5. glTF loading
6. camera controls
7. CPU scene list
8. simple resource handles
9. visibility buffer with object/material IDs
10. basic material shading pass

### v1: Main rendering path

1. render graph integration
2. GPU frustum culling
3. indirect draw commands
4. bindless-style material and texture lookup
5. PBR material
6. simple lights
7. shadow mapping
8. GPU upload queue
9. hot-reloadable shaders
10. frame profiler

### v2: Scaling path

1. occlusion culling
2. GPU LOD
3. better resource streaming
4. async asset loading
5. material/resource lifetime validation
6. virtual texturing experiments
7. native backend escape hatches where SDL_GPU is too limited

### v3 / future research

1. meshlets
2. mesh shaders / object shaders
3. work graphs
4. more advanced sparse resources
5. ray tracing experiments
6. neural rendering experiments

## Advanced learning modules

1. bindless-style resources
2. visibility buffers
3. GPU frustum culling
4. indirect draws
5. occlusion culling
6. GPU LOD
7. meshlets as future work
8. native backend escape hatches
9. mesh shaders / object shaders
10. work graphs