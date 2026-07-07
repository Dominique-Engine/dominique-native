# Continuation Prompt for Another Chat

Use this prompt to continue the project in a new conversation.

---

We are designing Dominique Engine.

Context:

Dominique is a production-capable, modular engine whose architecture is intentionally transparent and educational.

It is not only a game engine. It should support games, creative coding, interactive visuals, simulations, visualization, tools, and rendering experiments.

Core philosophy:

- modern-first
- usable, not toy-only
- plug-and-play modules
- replaceable implementations
- documentation-first
- examples as learning material
- stable public APIs with swappable internals
- designed for humans and LLM/coding agents

Major roadmap topics:

1. Render Graphs
2. GPU-driven Rendering
3. Bindless Resources
4. Meshlets
5. Work Graphs
6. Sparse Resources / Virtual Assets
7. Neural Rendering

Important accepted ideas:

- The engine should explain itself.
- Documentation is part of the product.
- Creative coding is a first-class use case.
- ECS is only one subsystem, not the center.
- Use ADRs to track decisions.
- Keep a living roadmap and design docs.
- The repository should include agent guidance, clear module boundaries, and small files.

Current likely stack:

- SDL3 for platform/window/input.
- SDL_GPU as the first rendering backend.
- C++ likely, but exact project structure still open.
- Native backend escape hatches may be needed later for advanced features.

Next useful task:

Help design one of these:

1. public API feel and module system
2. homepage/presentation messaging
3. render graph minimal architecture
4. bindless resources learning module
5. LLM/coding-agent-ready repo structure
6. first vertical slice implementation plan

Please continue from this context and preserve the living-document approach.
