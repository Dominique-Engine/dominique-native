# Dominique

c++ modular framework for creative coding, generative art, and dynamic visual development.

![Dominique engine latest example](./images/2.png "a title")

See [`docs/`](./docs/) for project specifications.

## Build

### Requirements

- Git
- CMake 3.14+
- A C++20 compiler
- Linux: SDL's normal build dependencies for your windowing backend, such as X11 or Wayland development packages

### Dependencies

The project expects SDL3 and glm to exist under `vendored/`.

```bash
./fetch_deps.sh
```

### Configure and build

```bash
cmake -B build -S .
cmake --build build
```

Examples are built by default. To skip them:

```bash
cmake -B build -S . -DDENGINE_EXAMPLES=OFF
cmake --build build
```

### Run the example

```bash
./build/examples/DEexample
```

With a multi-config generator such as Visual Studio, the executable is usually under a configuration subdirectory, for example:

```bash
./build/examples/Debug/DEexample.exe
```

### Run tests

```bash
ctest --test-dir build --output-on-failure
```

### Nix shell

If you use Nix, enter the development shell and run the bundled build helper:

```bash
nix develop
build
```

## Goals

- Modern c++
- Multiplatform
- Engine as a lib
- Some sort of plug and play
- All batteries(barebones) included
- JUST LEARN ALL THE STUFF

## Stack

- c++ 20
- SDL3
- glm
- cmake

## Webgraphy

- style guide: [google](https://google.github.io/styleguide/cppguide.html)
- ecs: [this blog](https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html)
-
uuid: [this header](https://www.boost.org/doc/libs/1_81_0/boost/uuid/uuid.hpp), [this blog](https://lowrey.me/guid-generation-in-c-11/),
the good old wikipedia
