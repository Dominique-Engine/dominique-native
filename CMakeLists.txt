cmake_minimum_required(VERSION 3.14)
project(Dominique VERSION 0.0.1)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set this definitions per terget and not global
add_definitions(-DAPP_VERSION="${CMAKE_PROJECT_VERSION}")
add_definitions(-DCOMPILER_SPEC="${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
add_definitions(-DAPP_NAME="${PROJECT_NAME}")
add_definitions(-DSDL_MAIN_HANDLED)#fix use of SDL, not fully tested on all platforms compilers, just on windows with MSVC and mingw

# SDL3
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/glm EXCLUDE_FROM_ALL)


set(DENGINE_EXAMPLES on CACHE BOOL "Build examples")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (WIN32)
        message(INFO " detected GNU compiler in windows, passing flag -mconsole")
        set(CMAKE_EXE_LINKER_FLAGS "-mconsole")#console mode app// unrecognized by msvc
    endif ()
endif ()

#include(CTest)
#
#enable_testing()

set(CMAKE_CXX_STANDARD 23)

set(DOMINIQUE_SOURCES
        "src/dengine/core.cpp"
        "src/dengine/components/registration/registration.cpp"
        "src/dengine/scene/scene.cpp"
        "src/dengine/utils/fileLoader.cpp"
        "src/dengine/utils/uuid.cpp"
        "src/dengine/sdl_gpu/core.cpp"
        "src/logger/logger.cpp"
        "src/dengine/sdl/sdl_helpers.cpp"
        "src/third_party/cgltf_impl.cpp"
        "vendored/tinyobjloader/tiny_obj_loader.cc"
)

add_library(Dominique STATIC
        ${DOMINIQUE_SOURCES}
)

include_directories("vendored")
include_directories("src")

if (WIN32)
    target_link_libraries(Dominique PRIVATE SDL3::SDL3 shell32 glm::glm)
elseif (UNIX)
    target_link_libraries(Dominique PRIVATE SDL3::SDL3 glm::glm)
endif ()

### Add some usable files to project build folder
set(RequiredExtras
        "TODO.txt"
)


include(GNUInstallDirs)

set_target_properties(Dominique
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS Dominique
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        RESOURCE DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        OBJECTS DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


#installing headers
install(DIRECTORY "./src/" # source directory
        DESTINATION "include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)

include(CTest)

enable_testing()

if (DENGINE_EXAMPLES)
    # add examples
    include("examples/examples.cmake")
endif (DENGINE_EXAMPLES)

# Add tests directory
add_subdirectory(tests)
