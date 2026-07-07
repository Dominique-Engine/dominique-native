# Research: Meshlets

## Problem

Large meshes are too coarse for efficient culling, LOD, and cache usage.

## Idea

Split meshes into small clusters of triangles.

Each meshlet can be culled, streamed, and rendered independently.

## Relationship to mesh shaders

Mesh shaders are a hardware/API path for processing meshlets efficiently.

But meshlet workflows can also be implemented with compute + indirect draws.

## Learning path

1. load normal mesh
2. offline meshlet generation
3. CPU meshlet culling
4. GPU meshlet culling
5. indirect draw backend
6. mesh shader backend
