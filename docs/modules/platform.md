# Module: Platform

## What problem does this solve?

The platform module owns the application-facing window and event-loop baseline.
It is the layer that lets Dominique start, run, poll operating-system events,
and shut down without exposing every native platform API directly.

## Why did old engines solve it differently?

Older engines often used per-platform windowing code or tied platform setup
directly to a renderer such as OpenGL or DirectX. That can ship quickly, but it
mixes window lifetime, input, rendering, and operating-system details.

## What is the naive implementation?

A naive platform layer creates one window, polls events in a loop, exits on the
quit event, and calls update/render callbacks every frame.

## What is the modern implementation?

A modern platform layer exposes explicit services for windows, input, timing,
DPI, displays, files, clipboard, controller devices, and application lifecycle.
Renderer backends then consume platform surfaces or windows through clear
contracts.

## How do large engines scale it?

Large engines usually support multiple windows, editor windows, raw input,
gamepad hotplugging, frame timing, job-system integration, headless modes,
platform permissions, crash handling, and per-platform escape hatches.

## What are the trade-offs?

SDL3 gives Dominique a portable starting point and keeps the code small. The
trade-off is that the current implementation still couples platform startup to
the SDL_GPU backend.

Current limitations include:

- no separate input abstraction
- no explicit frame timing or delta time
- no multi-window model
- no headless/test platform
- no platform capability object
- icon loading is performed during `core::Init`
- the main loop is owned by `de::core::Run`

## What future technologies may replace it?

The SDL3 platform layer could later be replaced by native platform backends,
toolkit integration for editors, or a headless platform for tests and servers.
Those should remain behind the platform contract instead of leaking into engine
subsystems.

## How is this implemented in Dominique?

The current platform-facing API is in `src/dengine/core.h`:

- `de::DEConfig`
- `de::DE`
- `de::core::Init`
- `de::core::Run`
- `de::core::Clean`

SDL initialization and window creation currently happen inside
`src/dengine/sdl_gpu/core.cpp` because the first implemented backend is SDL_GPU.
The loop in `src/dengine/core.cpp` polls SDL events, runs `UpdateHandler`
components, prepares a simple camera render target, and calls the selected
renderer callback.

## How do I replace this implementation?

First separate platform ownership from GPU ownership. A replacement should keep
the engine lifecycle obvious:

```cpp
de::core::Init(app);
de::core::Run(app, scene);
de::core::Clean(app);
```

If that public lifecycle changes, update the README, this module doc, and the
SDL3 ADR.

## Examples and benchmarks

`examples/main.cpp` exercises the current lifecycle by creating a `de::DE`,
initializing it, running the loop, and cleaning it up.

There are no platform tests or benchmarks yet. The first useful validation is a
headless or short-running smoke test that can initialize and shut down the
platform layer without manual window interaction.
