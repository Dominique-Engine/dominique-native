# Module: GPU

## What problem does this solve?

The GPU module owns the graphics device, swapchain access, command submission,
and backend-specific rendering entry points. It is the bridge between Dominique's
renderer direction and the graphics API exposed by SDL_GPU today.

## Why did old engines solve it differently?

Older engines often exposed OpenGL-style global state and per-draw binding
directly to gameplay or scene code. That made early rendering simple, but it
made replacement, validation, and modern GPU-driven workflows harder.

## What is the naive implementation?

A naive GPU module creates a device, clears the swapchain every frame, and
submits a command buffer.

## What is the modern implementation?

A modern GPU layer should expose explicit resources, command buffers, pipelines,
capabilities, synchronization points, and handles. Renderer modules should ask
for capabilities instead of branching on backend names.

## How do large engines scale it?

Large engines add upload queues, transient resource allocators, descriptor or
resource tables, shader compilation and hot reload, validation layers, frame
profiling, GPU markers, multi-queue scheduling, and backend-specific debugging.

## What are the trade-offs?

SDL_GPU gives Dominique a portable modern-ish baseline without starting with
native Vulkan, Metal, or D3D12. The trade-off is that SDL_GPU may not expose
every feature needed by the long-term bindless, visibility-buffer, GPU-driven
renderer path.

Current limitations include:

- no public GPU capability object
- no Dominique resource handles
- no GPU upload queue
- no pipeline abstraction
- no shader module abstraction
- no render graph integration
- no GPU tests or benchmarks
- some current structs still expose OpenGL-era names such as VAO/VBO/EBO IDs

## What future technologies may replace it?

Native Vulkan, Metal, or D3D12 backends may become escape hatches for advanced
experiments. Those should strengthen the same resource and capability contracts
rather than replacing the public renderer model.

## How is this implemented in Dominique?

The current SDL_GPU implementation lives in:

- `src/dengine/sdl_gpu/core.h`
- `src/dengine/sdl_gpu/core.cpp`

`de::core::sdl_gpu::Init` initializes SDL, creates a window, creates an
`SDL_GPUDevice`, and claims the window for that device. `Render` acquires a
command buffer and swapchain texture, clears it, ends the render pass, and
submits the command buffer. `Clean` destroys the window and calls `SDL_Quit`.

This is currently a clear-pass baseline, not the documented renderer v1
architecture.

## How do I replace this implementation?

Keep the renderer-facing contract backend-neutral. A replacement should avoid
adding new public OpenGL-style object IDs and should move toward explicit
resource handles and capability checks.

If the backend contract changes, update:

- this doc
- `docs/modules/renderer.md`
- `docs/adr/ADR-0003-use-sdl_gpu-as-initial-rendering-backend.md`
- relevant examples

## Examples and benchmarks

`examples/main.cpp` currently exercises SDL_GPU initialization and the clear
pass through the normal engine lifecycle.

There are no GPU benchmarks yet. The first useful GPU validation target is a
windowed smoke test that verifies command submission and swapchain presentation.
