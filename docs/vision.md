# Dominique Engine Vision

## Mission

Dominique aims to be a production-capable modular engine whose internals are designed to be understood.

It should not be a toy engine, but it also should not hide its architecture behind opaque abstractions.

## Identity

Dominique is not only a game engine.

It is a platform for:

- games
- creative coding
- procedural art
- interactive installations
- simulations
- visualization
- tools
- rendering experiments

## Design philosophy

Every subsystem should be:

- usable
- replaceable
- documented
- benchmarkable
- understandable
- modern-first

Modern-first does not mean everything must be implemented at once.

Dominique should prefer modern architecture, then introduce it through small, inspectable steps that can run, be studied, and be replaced.

## Key sentence

> A production-capable engine whose architecture explains itself.

## Educational model

The engine should teach through real implementations.

For each subsystem:

1. explain the problem
2. show the naive solution
3. show the modern solution
4. discuss AAA-scale approaches
5. describe likely future directions
6. provide references
7. provide runnable examples

Advanced architecture should arrive as usable modules, not as hidden complexity.

For example, the renderer can expose a clear baseline first, then add resource handles, visibility-buffer passes, GPU culling, and indirect draw generation as separate documented pieces.

## Creative coding

Creative coding remains a first-class use case.

Dominique should allow quick visual experimentation, inspired by Processing and similar frameworks, while still being built on modern rendering architecture.

Creative coding should benefit from the same renderer direction as games, simulations, tools, and visualization. It should not be forced onto a separate toy rendering path just because the entry point is friendlier.