# Renderer architecture

## Direction

The initial renderer uses SDL_GPU as a practical cross-platform backend while
engine-facing interfaces are developed. It must remain replaceable by a direct
Vulkan backend without changing the engine-facing API.

SDL3 provides platform services such as window creation, input, and events.
SDL_GPU implements graphics operations only.

## Required boundaries

- Keep SDL_GPU as an implementation detail of the initial backend.
- Do not expose SDL_GPU types through engine-facing or backend-independent
  renderer headers.
- Keep engine materials, resources, command submission, and synchronization
  independent of SDL_GPU concepts.
- Place the backend behind engine-owned handles and interfaces.
- Keep platform services separate from graphics operations.

The engine must not depend on SDL_GPU resource slots, pipelines, command
buffers, or synchronization semantics. Backend-specific translation belongs in
the SDL_GPU implementation.

## Review checklist

Renderer changes should preserve these boundaries and verify:

- swapchain acquisition failures and unavailable textures;
- resize and high-DPI behavior;
- command-buffer, render-pass, and submission ordering;
- cleanup on early exits and partial initialization;
- GPU device, resource, and window destruction order;
- portability across supported platforms and shader formats.
