# LLM / Coding Agent Guide

This repository is designed to be friendly to LLMs and coding agents.

## Principles

- Prefer small focused files.
- Avoid hidden global state.
- Keep module boundaries explicit.
- Document architectural decisions in ADRs.
- Update docs when changing architecture.
- Add examples for new features.
- Add tests or validation steps when possible.
- Preserve the living-document approach.

## Agent workflow

When implementing a feature:

1. Read `README.md`.
2. Read the relevant module doc.
3. Read relevant ADRs.
4. Make a small change.
5. Update docs.
6. Add or update an example.
7. Run build/tests.
8. Summarize trade-offs.

## Renderer architecture guidance

When changing renderer architecture:

- update the relevant ADRs
- update `docs/modules/renderer.md`
- update related research docs
- update examples when behavior or public usage changes
- keep advanced features behind explicit capability checks
- document backend limitations, especially around SDL_GPU portability
- do not add experimental renderer features directly into the core path without documenting trade-offs

The current proposed renderer direction is bindless-first, visibility-buffer-based, and GPU-driven, with meshlets deferred as future work.

Treat that as a roadmap direction, not as permission to skip incremental, inspectable implementation steps.

## Do not

- introduce large opaque abstractions
- silently change public APIs
- add dependencies without ADR discussion
- hide important behavior behind macros
- generate large files unless clearly marked
- turn future renderer experiments into required core behavior without documentation

## Preferred output from agents

Each coding-agent task should end with:

- files changed
- commands run
- tests passed/failed
- design notes
- follow-up items