# Module: Streaming

## What problem does this solve?

Streaming moves asset, scene, and resource data in and out of memory while the
application runs. It keeps large worlds and large asset sets from requiring all
data to be loaded at startup.

## Why did old engines solve it differently?

Smaller engines often load everything synchronously before gameplay starts.
That is simpler, but it does not scale to large scenes, large textures, or
interactive tools that need responsive loading.

## What is the naive implementation?

A naive streaming system can queue file loads on a background thread and publish
completed CPU-side assets back to the main thread.

## What is the modern implementation?

A modern streaming system coordinates file IO, decompression, asset import or
cooked asset loading, GPU uploads, lifetime tracking, priorities, budgets, and
fallback resources.

## How do large engines scale it?

Large engines add world partitioning, visibility or camera-driven priorities,
IO schedulers, GPU upload budgets, virtual texturing, sparse resources, asset
dependency graphs, and telemetry.

## What are the trade-offs?

Streaming adds complexity to ownership and synchronization. Dominique should not
add it to the core path until the asset and renderer handle contracts are clear.

Current limitations include:

- no streaming module
- no background loading
- no asset handles or lifetime validation
- no GPU upload queue
- no budgets or priority model

## What future technologies may replace it?

Sparse resources, virtual texturing, and platform-specific IO systems may shape
future streaming work. They should be documented as optional scaling paths, not
requirements for the first asset pipeline.

## How is this implemented in Dominique?

It is not implemented yet.

Current loading is synchronous and limited to helper functions in
`src/dengine/utils/fileLoader.cpp`.

## How do I replace this implementation?

Do not start with a large streaming framework. First define stable asset handles
and GPU upload ownership, then add asynchronous loading behind those contracts.

Any replacement should update:

- `docs/modules/assets.md`
- `docs/modules/gpu.md`
- renderer resource lifetime docs
- examples that depend on streamed assets

## Examples and benchmarks

There are no streaming examples or benchmarks yet.

The first useful validation target is loading a glTF asset asynchronously while
the window remains responsive, then publishing a typed asset record.
