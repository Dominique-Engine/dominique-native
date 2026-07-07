# ADR-0003: Use SDL_GPU as Initial Rendering Backend

## Status

Accepted

## Context

Dominique needs a first rendering backend that can support an inspectable
baseline without forcing the project to choose native Vulkan, Metal, or D3D12
immediately.

The renderer roadmap is modern-first, but the first implementation must stay
small enough to run, document, and replace.

## Decision

Use SDL_GPU as the initial GPU and rendering backend.

SDL_GPU will provide the first implementation of:

- GPU device creation
- swapchain access
- command buffer submission
- render pass setup
- shader format selection

This does not make SDL_GPU the final renderer architecture. The public renderer
direction should still move toward resource handles, capabilities, render graph
passes, visibility buffers, and GPU-driven draw generation.

## Alternatives considered

### OpenGL first

OpenGL is familiar and easy to bring up, but it encourages global state and
direct binding patterns that conflict with Dominique's modern-first renderer
direction.

### Native Vulkan, Metal, or D3D12 first

Native modern APIs expose more control and advanced features, but starting there
would add platform and backend complexity before Dominique has stable module
contracts.

### SDL_Renderer

SDL_Renderer is useful for simple 2D rendering, but it is not the right base for
the documented renderer direction.

## Consequences

SDL_GPU gives Dominique a portable clear-pass baseline and a path toward modern
graphics concepts. It may not expose every feature needed for a fully bindless
or GPU-driven renderer, so capability checks and documented backend limitations
are required.

The current code still contains OpenGL-era names in renderer data structures.
Those should be treated as baseline debt and replaced with backend-neutral
resource handles before more renderer features are added.

## Future work

- Add a GPU capability object.
- Define first renderer resource handle types.
- Add a triangle example.
- Add shader loading through an explicit shader module contract.
- Document SDL_GPU limitations for bindless-style resources and indirect draws.
- Add native backend escape-hatch ADRs only when an experiment needs them.
