# Module System

## Goal

Dominique should be built around plug-and-play modules.

Modules allow the same concept to have multiple implementations.

## Example

```cpp
Engine engine;

engine.use<SDLPlatform>();
engine.use<SDLGpuDevice>();
engine.use<RenderGraph>();
engine.use<PBRRenderer>();

engine.run();
```

This is not final syntax. It communicates the desired feel:

- declarative setup
- explicit modules
- easy swapping
- readable initialization

## Open questions

- Should modules be registered at compile time or runtime?
- Should modules use dependency injection?
- Should modules expose service interfaces?
- Should examples use config files?
- How much should be template-based C++?
- How easy should it be for LLM coding agents to add a module?

## LLM consideration

Modules should have clear folder boundaries and small interfaces so coding agents can reason locally.
