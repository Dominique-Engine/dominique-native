# Documentation Model

Every subsystem should follow this structure.

Early subsystems may keep these sections in one file under `docs/modules/`.
Larger subsystems can split them into nearby module files later, but they should
keep the same questions answerable.

## Template

1. What problem does this solve?
2. Why did old engines solve it differently?
3. What is the naive implementation?
4. What is the modern implementation?
5. How do large engines scale it?
6. What are the trade-offs?
7. What future technologies may replace it?
8. How is this implemented in Dominique?
9. How do I replace this implementation?
10. Examples and benchmarks

Use `docs/modules/_template.md` when adding a new module doc.

## Current-state rule

Module docs must distinguish:

- what is implemented today
- what is only the intended direction
- what is intentionally out of scope
- what contracts must stay stable during replacement

Do not describe future renderer architecture as if it already exists in code.

## Philosophy

The engine should explain itself.

Documentation is not separate from architecture. It is part of the product.
