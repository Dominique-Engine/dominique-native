# Examples Plan

Every feature should have a runnable example.

## Current example

The current repository has one example target, `DEexample`, built from
`examples/main.cpp`.

It currently demonstrates:

- creating a `de::DE`
- creating a scene
- calling the asset loader stubs
- initializing the engine
- running the SDL event loop
- clearing the swapchain through SDL_GPU
- cleaning up

It does not yet demonstrate mesh rendering, materials, render graphs, GPU
culling, or bindless resources.

## Initial examples

1. `01_window`
2. `02_triangle`
3. `03_textured_quad`
4. `04_gltf_mesh`
5. `05_pbr_material`
6. `06_render_graph`
7. `07_shadow_map`
8. `08_forward_plus`
9. `09_gpu_culling`
10. `10_bindless_materials`

## Rule

Examples should be small, focused, and documented.

Each example should explain:

- what it demonstrates
- what modern concept it maps to
- what limitations it has
