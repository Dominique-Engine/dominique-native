# ADR-0002: Use SDL3 as Platform Layer

## Status

Accepted

## Context

Dominique needs a portable platform baseline for creating windows, polling
events, and integrating with the first GPU backend.

The project should stay focused on engine architecture rather than maintaining
native windowing code for every operating system at the start.

## Decision

Use SDL3 as the initial platform layer.

SDL3 will own the first implementation of:

- window creation
- event polling
- controller and input access when added
- platform initialization and shutdown

The platform contract should still be separated from renderer ownership over
time. SDL3 is the first implementation, not a reason to mix platform, input, and
GPU responsibilities forever.

## Alternatives considered

### Native platform APIs

Native Win32, Cocoa, X11, Wayland, and other platform APIs would expose maximum
control, but they would slow down the first vertical slice and distract from the
engine architecture goals.

### GLFW

GLFW is a strong windowing choice, especially for OpenGL and Vulkan examples.
SDL3 is preferred here because it also covers controllers, audio, and broader
application needs that Dominique may grow into.

### SDL2

SDL2 is mature, but Dominique should start on SDL3 to align with the current SDL
API direction and SDL_GPU.

## Consequences

SDL3 becomes a core dependency for the initial engine.

The code can start with a portable window and event loop, but Dominique still
needs an explicit platform module boundary. The current implementation couples
SDL initialization with SDL_GPU setup, which should be split as the platform and
GPU docs become executable architecture.

## Future work

- Define a platform capability object.
- Add an input abstraction.
- Add frame timing and delta time.
- Add a short-running platform smoke test.
- Split SDL platform initialization from SDL_GPU device initialization.
