# ADR-0001: Project Philosophy

## Status

Accepted

## Context

Dominique should be useful for real applications while also helping people learn modern engine architecture.

The project should not become a toy-only educational renderer, but it also should not become an opaque production engine.

## Decision

Dominique will be a production-capable modular engine whose architecture is intentionally transparent.

The engine should explain itself through:

- documentation
- examples
- replaceable implementations
- clear module boundaries
- architecture decision records

## Alternatives considered

### Pure game engine

Rejected as too broad and too competitive with established engines.

### Pure educational demo framework

Rejected because usability is a core goal.

### Pure graphics framework

Too narrow. Dominique should support broader engine architecture.

## Consequences

Every subsystem needs both usability and explanation.

This increases documentation burden but creates the project's unique identity.

## Future work

Define the homepage language and public API feel.
