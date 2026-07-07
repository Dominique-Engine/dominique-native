# ADR-0008: LLM and Coding Agent Readiness

## Status

Accepted

## Context

The engine should be built in the context of LLMs and coding agents.

Future contributors may use coding agents to explore, modify, and implement modules.

The repository should therefore be easy for both humans and agents to navigate.

## Decision

Dominique will maintain explicit guidance for LLM/coding-agent usage.

The repository should include:

- `AGENTS.md`
- small modules
- clear ownership boundaries
- explicit build/test commands
- local examples
- ADRs
- coding conventions
- module templates
- documentation templates

## Design implications

Prefer:

- small files
- clear names
- low hidden magic
- explicit dependencies
- examples per feature
- tests near modules
- generated files clearly marked

Avoid:

- giant source files
- implicit global state
- unclear ownership
- undocumented macros
- scattered initialization logic

## Future work

Create a module scaffolding command and agent-friendly issue templates.
