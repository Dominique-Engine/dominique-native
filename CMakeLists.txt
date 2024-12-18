cmake_minimum_required(VERSION 3.5.0)
project(Dominique VERSION 0.0.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set this definitions per terget and not global
add_definitions(-DAPP_VERSION="${CMAKE_PROJECT_VERSION}")
add_definitions(-DCOMPILER_SPEC="${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
add_definitions(-DAPP_NAME="${PROJECT_NAME}")
add_definitions(-DSDL_MAIN_HANDLED)#fix use of SDL, not fully tested on all platforms compilers, just on windows with MSVC and mingw

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

set(CMAKE_CXX_STANDARD 20)

set(DOMINIQUE_SOURCES
        "src/dengine/core.cpp"
        "src/dengine/utils/fileLoader.cpp"
        "src/dengine/utils/uuid.cpp"
        "src/dengine/openGL/coreGL.cpp"
        "src/dengine/openGL/renderer/renderer.cpp"
        "src/dengine/spdlog_helper.cpp"
        "src/dengine/sdl_helpers.cpp"
        "3rdParty/cgltf/cgltf.cpp"
        "3rdParty/tinyobjloader/tiny_obj_loader.cc"
)

add_library(Dominique STATIC
        ${DOMINIQUE_SOURCES}
)

include_directories("3rdParty")
include_directories("src")

find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

if (${SDL2_FOUND})
    if (WIN32)
        target_link_libraries(Dominique PRIVATE SDL2::SDL2main SDL2::SDL2-static glad::glad shell32)
    elseif (UNIX)
        target_link_libraries(Dominique PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
                $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static> glad::glad)
    endif ()
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


if (DENGINE_EXAMPLES)
    # add examples
    include("examples/examples.cmake")
endif (DENGINE_EXAMPLES)
