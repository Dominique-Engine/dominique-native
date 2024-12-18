# EXAMPLES

set(EXAMPLES_FOLDER ${CMAKE_BINARY_DIR}/examples)

#test
add_executable(DEexample ${GUI_TYPE}
        "examples/main.cpp"
)

add_dependencies(DEexample Dominique)

find_package(glm CONFIG REQUIRED)

target_link_libraries(DEexample PRIVATE Dominique)

set_target_properties(DEexample PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXAMPLES_FOLDER})


### Add some usable files to examples folder
set(ExamplesRequiredExtras
        "res/icon.png"
        "res/WaterBottle.gltf"
        "res/shaders/baseFragment.glsl"
        "res/shaders/baseVertex.glsl"
        "res/textures/lava.png"
        # "res/models/Prop_Tree_Palm_3.obj"
)

get_target_property(EXAMPLES_BINARY_EXECUTABLE_OUTPUT DEexample RUNTIME_OUTPUT_DIRECTORY)

find_package(glm CONFIG REQUIRED)

foreach (_file ${ExamplesRequiredExtras})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        list(APPEND extraFiles COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_SOURCE_DIR}/${_file}" "${EXAMPLES_BINARY_EXECUTABLE_OUTPUT}/$<CONFIG>/")
    else ()
        list(APPEND extraFiles COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_SOURCE_DIR}/${_file}" "${EXAMPLES_BINARY_EXECUTABLE_OUTPUT}/")
    endif ()
endforeach ()

add_custom_command(TARGET DEexample POST_BUILD
        ${extraFiles}
)