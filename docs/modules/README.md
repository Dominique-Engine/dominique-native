# Engine Modules

Use `_template.md` when adding or rewriting a module doc.

Initial modules:

- Platform
- GPU
- Render Graph
- Renderer
- Assets
- Streaming
- Scene
- ECS
- Audio
- Physics
- Tools

Early modules can live as one `docs/modules/<module>.md` file. As modules grow,
split the same contract into nearby files:

- `README.md`
- `DESIGN.md`
- `API.md`
- `EXAMPLES.md`
- `TESTS.md`
- `BENCHMARKS.md`
- `ROADMAP.md`

Each module doc should clearly mark what exists today, what is planned, and what
contracts must stay stable during replacement.
