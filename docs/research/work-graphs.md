# Research: Work Graphs

## Problem

Even GPU-driven rendering often requires the CPU to orchestrate dispatches and draws.

## Idea

Let the GPU schedule more GPU work itself.

Work graphs are a possible future direction where GPU tasks can spawn more GPU tasks.

## Why it matters

This could become a foundation for:

- procedural generation
- particles
- visibility
- animation
- streaming
- future renderers

## Status

Experimental / future-facing.

Do not build the core engine around this yet.
