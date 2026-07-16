# Dominique documentation

This is the entry point for project specifications and review references. Start
here, select the subsystem affected by the change, and follow its linked source
and test paths before reviewing implementation details.

## Specifications

- [Error handling](./error-handling.md)
  - Governs: all fallible public APIs, resource-owning code, subsystem
    boundaries, and error-path tests
  - Primary paths: `src/` and `tests/`
- [Renderer architecture](./renderer-architecture.md)
  - Governs: `src/dengine/sdl_gpu/`, `src/dengine/sdl/`,
    `src/dengine/core.h`, and `src/dengine/core.cpp`
  - Related build references: `CMakeLists.txt` and
    `examples/examples.cmake`

## General references

- `README.md`: project overview and supported build/test commands
- `CMakeLists.txt`: language version, targets, dependencies, and installation
- `tests/CMakeLists.txt` and `tests/`: test registration and behavior
- `.clang-format` and `.clang-tidy`: code conventions and static checks
- `vendored/`: exact third-party APIs and versions

When adding a specification, list the implementation paths, tests, build files,
and external references it governs so agents can retrieve the right context
without scanning the whole repository.
