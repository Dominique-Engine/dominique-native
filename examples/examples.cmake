# EXAMPLES

set(EXAMPLES_FOLDER ${CMAKE_BINARY_DIR}/examples)

#test
add_executable(DEexample ${GUI_TYPE}
        "examples/main.cpp"
)

add_dependencies(DEexample Dominique)

#find_package(glm CONFIG REQUIRED)

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

foreach (_file ${ExamplesRequiredExtras})
    list(APPEND extraFiles COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_SOURCE_DIR}/${_file}" "$<TARGET_FILE_DIR:DEexample>/")
endforeach ()

if (WIN32)
    list(APPEND extraFiles COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:DEexample>/")
endif ()

add_custom_command(TARGET DEexample POST_BUILD
        ${extraFiles}
)
