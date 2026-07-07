# LLM-Native Module Contracts

## Purpose

Dominique modules should be understandable by humans and coding agents.

That requires more than comments in source files. Each substantial module should eventually describe its purpose, public contract, examples, tests, benchmarks, and roadmap in predictable places.

This is not bureaucracy. It is part of making the engine replaceable, educational, and friendly to coding agents.

## Contract

Every substantial module should eventually have:

- `README.md`
- `DESIGN.md`
- `API.md`
- `EXAMPLES.md`
- `TESTS.md`
- `BENCHMARKS.md`
- `ROADMAP.md`

Early modules may keep these sections in a single `docs/modules/<module>.md` file.

As a module grows, split the sections into files near the module implementation.

## File roles

### README.md

Explains what the module does and when to use it.

### DESIGN.md

Explains internal architecture, data flow, trade-offs, and replacement points.

### API.md

Defines public types, functions, handles, events, capabilities, and stability expectations.

### EXAMPLES.md

Shows small runnable examples and links to larger examples.

### TESTS.md

Explains what is tested, how to run tests, and what validation is still missing.

### BENCHMARKS.md

Defines expected performance questions and how benchmarks should be interpreted.

### ROADMAP.md

Lists staged improvements and future research without making every idea a current requirement.

## Why this matters

A module contract makes replacement possible.

For example, a renderer module can document:

- what data it consumes
- what resources it owns
- what handles it exposes
- what passes it contributes to the render graph
- what backend capabilities it requires
- what features are intentionally out of scope

A coding agent can then modify a module without guessing hidden ownership rules or inventing a new architecture.

## Guidance

Prefer clear module contracts over large abstract frameworks.

Document advanced features before placing them on the core path.

Use explicit capability checks for optional features.

Keep module docs close to examples, tests, and benchmarks.

When replacing an implementation, update the contract only if the public behavior changes.