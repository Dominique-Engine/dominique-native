# AGENTS.md

Guidance for coding agents working on Dominique Engine.

## Project intent

Dominique is a production-capable modular engine whose architecture is intentionally transparent.

Do not optimize only for shipping code. Optimize for understandable architecture.

## Before coding

Read:

1. `README.md`
2. `docs/vision.md`
3. `docs/roadmap.md`
4. relevant ADRs
5. relevant module docs

## Before committing or opening PRs

Read `docs/llm/commit-pr-style.md` and follow it for commit messages, PR titles, and PR bodies.

## Rules

- Keep changes small.
- Update docs with architecture changes.
- Add examples for new features.
- Prefer explicit code over clever code.
- Avoid hidden global state.
- Respect module boundaries.
- Do not introduce dependencies without documenting why.

## Summary required after work

Report:

- files changed
- commands run
- tests passed/failed
- design trade-offs
- open follow-ups