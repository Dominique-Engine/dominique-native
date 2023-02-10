# fritters-Frontend
Basic frontend for testing and using fritters

## Requirements

- Python: for GLAD generation
- Vulkan SDK: to use vulkan during rendering, if not present need to be disabled in cmake

![Alt text](./images/1.png "a title")

## Issues

Because a little hack to allow the use of cmake's `find_package()` and `ExternalProjecAdd()` the app should compile easily with clang, gcc or mingw, but with msvc if the SDL2 package is missing, the first build installs it along other dependencies and the build needs to be triggered a second time for the main app to be able to find deps and link correctly, cause the first try fails. If SDL2 is present from the beginning nothing happens, but i recommend install it from source(that is handled by the project itself).