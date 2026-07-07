# Presentation / Website Notes

## Current direction

The website should not sell Dominique as just another game engine.

It should communicate:

- Dominique is a modern engine architecture platform
- build interactive applications
- learn modern engine architecture
- replace subsystems
- understand real implementations
- modern rendering from first principles
- creative coding, games, simulations, visualization, and tools share the same architecture

## Renderer messaging

The renderer direction is modern-first but incremental.

It is designed around:

- bindless-style resource handles
- GPU-driven rendering
- visibility-buffer techniques
- explicit render graph passes
- replaceable renderer modules

Experimental techniques are explored as replaceable modules, not forced into the core path.

Meshlets, mesh shaders, work graphs, ray tracing, and neural rendering should be presented as future research areas unless a specific implementation exists.

## Possible tagline directions

- Build interactive worlds. Understand the engine beneath them.
- Modern engine architecture, made explorable.
- A modular engine that explains itself.
- Build visuals, simulations, and games with transparent modern architecture.
- Learn modern engines by replacing one subsystem at a time.

## Homepage sections

1. Hero
2. What Dominique is
3. Modular architecture diagram
4. Creative coding / interactive visuals
5. Modern renderer roadmap
6. Replaceable subsystem examples
7. Documentation philosophy
8. Examples gallery
9. Get started

## Avoid

- fake testimonials
- generic ECS-centered marketing
- green framework claims
- overemphasis on UUID/internal utilities
- vague "game engine" positioning
- claims that Dominique is a AAA engine
- implying meshlets are required for renderer v1
- promising API features that SDL_GPU may not expose yet