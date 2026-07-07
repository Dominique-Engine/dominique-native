# Research: Visibility Buffer

## What it is

A visibility buffer is a render target that stores which surface is visible at each pixel.

Instead of writing full material attributes during the geometry pass, the renderer writes compact identifiers such as:

- object ID
- material ID
- primitive ID or draw ID
- depth

A later material shading pass reads those identifiers, fetches the required mesh and material data, and computes the final shading.

## Difference from a classic G-buffer

A classic deferred G-buffer stores already-expanded surface data, such as normals, albedo, roughness, metallic values, and sometimes motion or emission.

A visibility buffer stores references to the visible surface instead.

```text
Classic G-buffer:
geometry pass writes material attributes

Visibility buffer:
geometry pass writes IDs
material pass fetches attributes later
```

The visibility-buffer approach can reduce the number of large render targets and make material evaluation more flexible.

It also moves more responsibility to shader-side data fetching.

## Why it pairs well with bindless resources

A visibility buffer only stores useful identifiers if shaders can use those identifiers to fetch data.

Bindless-style resource tables provide that path:

```text
pixel -> material ID -> material table -> texture handles -> textures
```

The renderer does not need to bind a unique texture set for every draw during the visibility pass.

The material shading pass can fetch the resources needed for the visible pixels.

## Why it pairs well with GPU-driven rendering

GPU-driven rendering produces visible object lists and indirect draw commands.

The visibility pass can consume those commands and write compact surface IDs.

That gives Dominique a practical progression:

```text
GPU culling
  ↓
indirect draw commands
  ↓
visibility buffer
  ↓
material shading
```

This is a useful bridge between traditional mesh rendering and future meshlet or work-graph experiments.

## Simple implementation path

### v0

1. Build a CPU scene list.
2. Assign each renderable an object ID and material ID.
3. Draw normal indexed meshes.
4. Write depth, object ID, and material ID to visibility targets.
5. Run a full-screen material pass that colors pixels from material data.
6. Add debug views for object IDs, material IDs, and depth.

### v1

1. Upload renderable records to GPU-readable buffers.
2. Run GPU frustum culling.
3. Generate indirect draw commands.
4. Draw the visibility pass from indirect commands.
5. Fetch material and texture data through handles.

### Later

1. Add occlusion culling.
2. Add GPU LOD.
3. Add clustered geometry or meshlet visibility experiments.
4. Replace the visibility producer without replacing the material system.

## Trade-offs and limitations

- Material shading becomes more dependent on GPU-readable resource tables.
- Attribute reconstruction can be more complex than reading a classic G-buffer.
- Transparency still needs a separate path or special handling.
- MSAA and edge cases require careful design.
- Debugging can be less direct because IDs must be resolved to human-readable objects.
- Portable APIs may not expose every feature needed for a fully bindless version.

## Dominique direction

Dominique should use the visibility buffer as a staged renderer direction, not as an all-at-once requirement.

The first version can be simple and inspectable. The important part is that the module boundary is clear:

```text
visibility producer -> visibility buffer -> material resolver
```

That boundary makes the renderer easier to study and easier to replace later.