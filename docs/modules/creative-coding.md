# Module: Creative Coding

## What problem does this solve?

The creative coding module should provide a friendly entry point for quick
visual experiments while still using Dominique's real engine architecture.

## Why did old engines solve it differently?

Creative coding tools often prioritize immediate drawing APIs and hide the
renderer architecture. That makes sketches fast to write, but it can create a
separate toy path that does not benefit from the engine renderer.

## What is the naive implementation?

A naive implementation exposes callbacks such as setup, update, and draw, plus
simple drawing helpers for shapes, colors, textures, and time.

## What is the modern implementation?

A modern implementation should layer a friendly API over the same renderer,
assets, input, and timing systems used by games, simulations, tools, and
visualization.

## How do large engines scale it?

Large creative tools add live reload, editor panels, parameter controls,
recording, timeline support, shader editing, scripting, asset browsers, and
integration with input devices or installations.

## What are the trade-offs?

A friendly API can hide useful architecture if it becomes a separate path.
Dominique should keep creative coding ergonomic without bypassing module
contracts.

Current limitations include:

- no creative coding API
- no timing abstraction
- no input abstraction
- no immediate shape drawing
- no shader sketch workflow
- no live reload

## What future technologies may replace it?

The API may eventually be backed by scripting, shader hot reload, node graphs,
or editor tools. These should remain clients of the same renderer and asset
modules.

## How is this implemented in Dominique?

It is not implemented yet.

The closest current behavior is the engine lifecycle in `examples/main.cpp` and
the `UpdateHandler` component in `src/dengine/components/scriptable.hpp`.

## How do I replace this implementation?

Start with a small wrapper over the existing lifecycle rather than inventing a
new runtime. The first contract should make setup/update/draw timing explicit
and document which renderer features are available.

If public creative coding APIs are added, include examples and keep them backed
by normal engine modules.

## Examples and benchmarks

There are no creative coding examples or benchmarks yet.

The first useful example is a minimal sketch that opens a window, tracks time,
and draws through the same renderer path as the engine examples.
