# Repository Contract for Agents

## Expected root files

- `README.md`
- `AGENTS.md`
- `CMakeLists.txt` or chosen build config
- `docs/`
- `examples/`
- `engine/`
- `tools/`

## Documentation rules

If an agent changes a subsystem, it should update:

- module docs
- relevant ADR
- example docs
- roadmap if priority changed

## Code rules

Prefer:

- explicit ownership
- clear resource lifetime
- RAII wrappers
- narrow interfaces
- visible synchronization points
- named concepts matching docs

Avoid:

- clever metaprogramming without explanation
- giant manager classes
- hidden initialization
- unclear threading behavior
