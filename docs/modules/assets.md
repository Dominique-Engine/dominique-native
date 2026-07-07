# Module: Assets

## What problem does this solve?

The assets module loads external data such as files, meshes, images, materials,
and shaders into engine-readable data. It is the future source of meshes,
materials, textures, and resource handles for the renderer.

## Why did old engines solve it differently?

Older or smaller engines often load files directly where they are needed and
bind renderer resources immediately. That is simple, but it mixes parsing,
resource lifetime, GPU upload, caching, and error reporting.

## What is the naive implementation?

A naive asset layer reads files from disk and parses each format on demand. Mesh
or texture data can then be handed directly to renderer setup code.

## What is the modern implementation?

A modern asset system separates source files, imported CPU data, runtime asset
records, GPU resources, and handles. It supports caching, validation, streaming,
hot reload, stable IDs, and clear ownership of uploaded resources.

## How do large engines scale it?

Large engines usually have offline importers, asset databases, dependency
tracking, cooked platform formats, background loading, streaming budgets,
versioning, and editor tooling.

## What are the trade-offs?

The current implementation is intentionally small and useful for experiments.
The trade-off is that it does not yet produce typed asset records or renderer
handles.

Current limitations include:

- `LoadGLTF` only parses a file with `cgltf` and frees it
- `LoadObj` is a stub that returns true
- there is no texture loader contract beyond SDL helper image loading
- there is no asset cache, registry, or lifetime model
- there is no GPU upload path
- errors are reported through the simple logger and boolean returns

## What future technologies may replace it?

The current loader functions may be replaced by an importer/runtime split,
streaming asset system, virtual resources, or cooked asset packages. Sparse
resources and virtual texturing are future renderer-adjacent directions, not
current requirements.

## How is this implemented in Dominique?

Current files:

- `src/dengine/utils/fileLoader.h`
- `src/dengine/utils/fileLoader.cpp`
- `src/dengine/sdl_helpers.h`
- `src/dengine/sdl_helpers.cpp`

`LoadFileToString` reads a whole file into a string. `LoadGLTF` calls `cgltf` to
parse a glTF file and currently discards the parsed data. `LoadObj` currently
returns true without loading data.

Image loading for the window icon uses `stb_image` through the SDL helper
function `loadImgFromFile2SDLSurface`.

## How do I replace this implementation?

Introduce typed asset records before adding renderer upload behavior. A
replacement should make these boundaries explicit:

```text
source file -> parsed CPU asset -> runtime asset handle -> GPU resource handle
```

If public asset APIs change, update the README examples, this doc, renderer
docs, and any examples that load assets.

## Examples and benchmarks

`examples/main.cpp` calls `LoadGLTF("WaterBottle.gltf")` and
`LoadObj("Prop_Tree_Palm_3.obj")`, but the example does not render loaded asset
data yet.

There are no asset tests or benchmarks yet. The first useful tests are:

- `LoadFileToString` success and failure
- `LoadGLTF` reports false for invalid or missing files
- `LoadGLTF` returns typed mesh/material counts after importer data exists
