# Research: Bindless Resources

## Problem

Traditional rendering binds resources per draw or per material, creating CPU overhead and limiting GPU-driven rendering.

If the CPU must bind every texture and buffer before every draw, the renderer becomes harder to scale and harder to move toward GPU-side visibility decisions.

## Idea

Instead of binding a texture before each draw, resources live in large tables.

Materials store indices or handles.

Shaders fetch resources dynamically.

```cpp
struct Material {
    uint32_t baseColorTexture;
    uint32_t normalTexture;
    uint32_t roughnessTexture;
};
```

This can be fully bindless on APIs that support it, or bindless-style on portable APIs that expose a more limited resource model.

## Bindless-first renderer direction

Dominique's proposed renderer direction is bindless-first.

That means renderer-facing data should use handles even before the backend has a perfect bindless implementation.

The first implementation can map handles to simple CPU tables or fixed-size GPU arrays.

Later implementations can map the same handles to descriptor indexing, bindless textures, or native backend-specific resource tables.

The public concept should stay stable:

```text
MaterialHandle -> material record -> texture handles -> texture table
```

## Resource handles as a core concept

Resource handles should be explicit values, not hidden pointers to backend state.

Examples:

- `MeshHandle`
- `MaterialHandle`
- `TextureHandle`
- `BufferHandle`
- `SamplerHandle`

Handles make lifetime, validation, serialization, debugging, and shader table generation easier to document.

A handle should be cheap to copy and should not imply ownership by itself.

## Relationship to visibility buffers

Visibility buffers store compact IDs for visible pixels.

Those IDs become useful when the material pass can resolve them into resource handles:

```text
visibility pixel
  -> object ID
  -> material ID
  -> material table entry
  -> texture handles
  -> texture table entries
```

This lets the visibility pass focus on coverage and the material pass focus on shading.

## Relationship to GPU-driven rendering

Bindless resources fit naturally with GPU-driven rendering.

If the GPU decides what to draw, the GPU also needs enough data to describe what it is drawing.

A practical flow is:

```text
GPU culling
  ↓
visible object list
  ↓
indirect draw commands
  ↓
visibility buffer
  ↓
material lookup through handles
```

Without handle-based resource access, GPU-driven draw generation often falls back into CPU-side binding decisions.

## Portable API limitations

SDL_GPU is the preferred initial rendering backend, but portable APIs may not expose every feature needed for a fully bindless renderer.

Possible limitations include:

- fixed resource binding counts
- limited descriptor indexing
- limited runtime-sized resource arrays
- restrictions on non-uniform texture indexing
- backend-specific shader language constraints
- limited introspection for validation and debugging

Dominique should document these limits as capabilities, not as hard-coded backend branches.

Example:

```cpp
if (capabilities.bindlessTextures) {
    // native bindless or descriptor indexing path
} else {
    // table, array, or explicit bind fallback
}
```

## Native backend escape hatches

Dominique may eventually need native Vulkan, Metal, or D3D12 paths for advanced experiments.

Those paths should be escape hatches, not the default reason to abandon portability.

A native backend can expose stronger versions of the same contracts:

- larger resource tables
- descriptor indexing
- bindless texture access
- richer GPU validation
- backend-specific debugging tools

The renderer API should keep handles and module boundaries stable across those implementations.

## Learning path

1. classic binding
2. texture arrays
3. explicit resource handles
4. bindless-style material table
5. visibility-buffer material lookup
6. GPU-driven material selection
7. native bindless backend experiments

## Open questions

- What level of bindless support does SDL_GPU expose in practice?
- What is the first stable handle representation?
- How should handles encode generation or lifetime validation?
- How should shader-visible tables be versioned?
- When is a native backend escape hatch justified?