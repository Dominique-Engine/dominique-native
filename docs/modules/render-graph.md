# Module: Render Graph

## What problem does this solve?

A render graph describes render passes, dependencies, and resource lifetimes so
the renderer does not rely on a fragile hardcoded sequence as it grows.

## Why did old engines solve it differently?

Older or simpler renderers often call passes in a fixed order and manually
manage render targets. That works for a few passes, but it becomes hard to
modify, validate, and optimize.

## What is the naive implementation?

A naive implementation is a named list of passes where each pass declares the
resources it reads and writes. The graph can validate names and execute the
passes in the order they were added.

## What is the modern implementation?

A modern render graph derives pass ordering, transient resource allocation,
barriers, synchronization, and debug information from explicit pass/resource
declarations.

## How do large engines scale it?

Large engines add transient memory aliasing, async compute scheduling, pass
culling, resource state tracking, GPU profiling, debug graph views, frame
captures, and backend-specific barrier generation.

## What are the trade-offs?

A render graph improves clarity once the renderer has multiple passes. It can be
unnecessary overhead before Dominique has a triangle, mesh pass, or material
pass.

Current limitations include:

- no render graph implementation
- no pass declaration API
- no resource lifetime model
- no barrier or synchronization model
- no examples

## What future technologies may replace it?

Future GPU work graphs or task-graph systems may eventually absorb some render
graph responsibilities. Dominique should still start with an inspectable render
graph before relying on more advanced GPU task systems.

## How is this implemented in Dominique?

It is not implemented yet.

The current SDL_GPU renderer performs one explicit clear pass directly in
`src/dengine/sdl_gpu/core.cpp`.

## How do I replace this implementation?

The first implementation should be deliberately small:

```text
add pass
declare reads/writes
validate resource names
execute passes in order
show the graph in logs or debug output
```

When render graph behavior enters the core renderer path, update the renderer
doc, ADR-0004, and examples.

## Examples and benchmarks

There are no render graph examples or benchmarks yet.

The first useful example is a two-pass frame that clears an offscreen target and
copies or draws it to the swapchain.
