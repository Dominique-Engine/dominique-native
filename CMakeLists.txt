cmake_minimum_required(VERSION 3.0.0)

project(Dominique VERSION 0.0.1)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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


include("collector/collector.cmake")#need to be after project()

include(CTest)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

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

set(GLAD_INSTALL ON)
set(DIRECTX OFF)

append_var_to_cmake_args(DIRECTX)
append_var_to_cmake_args(GLAD_INSTALL)
collect("https://github.com/Dav1dde/glad" "v0.1.34" Dominique)
collect("https://github.com/PotatoBite/xgetopt" "v1.0.0" Dominique)
collect("https://github.com/ThePhD/sol2" "v3.2.2" Dominique)
collect_src("https://github.com/g-truc/glm.git" "0.9.9.8" Dominique)

collect_and_find(spdlog "https://github.com/gabime/spdlog" "v1.8.5" Dominique)
collect_and_find(SDL2 "https://github.com/libsdl-org/SDL" "release-2.0.14" Dominique)

if (${SDL2_FOUND})
    if (WIN32)
        target_link_libraries(Dominique PRIVATE SDL2::SDL2main SDL2::SDL2-static glad spdlog::spdlog shell32)
    elseif (UNIX AND NOT APPLE)
        target_link_libraries(Dominique PRIVATE SDL2 SDL2::SDL2-static glad spdlog::spdlog)
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