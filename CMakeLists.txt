cmake_minimum_required(VERSION 3.0.0)

project(Dominique VERSION 0.0.1)

add_definitions( -DAPP_VERSION="${CMAKE_PROJECT_VERSION}" )
add_definitions( -DCOMPILER_SPEC="${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}" )
add_definitions( -DAPP_NAME="${PROJECT_NAME}")
add_definitions( -DSDL_MAIN_HANDLED )#fix use of SDL, not fully tested on all platforms compilers, just on windows with MSVC and mingw

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(WIN32)
        message(INFO " detected GNU compiler in windows, passing flag -mconsole")
        set(CMAKE_EXE_LINKER_FLAGS "-mconsole")#console mode app// unrecognized by msvc
    endif()
endif()


include("collector/collector.cmake")#need to be after project()



include(CTest)

enable_testing()

set (CMAKE_CXX_STANDARD 17)


add_executable(Dominique ${GUI_TYPE}
              "src/main.cpp"
              )

include_directories("3rdParty")


set(GLAD_INSTALL ON)
append_var_to_cmake_args(GLAD_INSTALL)
#collect_src(    "https://github.com/skaslev/gl3w" "" Dominique)
collect( "https://github.com/Dav1dde/glad" "v0.1.34" Dominique )
collect_and_find( SDL2 "https://github.com/libsdl-org/SDL" "release-2.0.14" Dominique )
collect_and_find( CURL "https://github.com/curl/curl" "curl-7_79_1" Dominique )



if(${SDL2_FOUND} AND ${CURL_FOUND})
#if(${SDL2_FOUND})
    if (WIN32)       #Windows settings
        target_link_libraries (Dominique PRIVATE SDL2::SDL2main SDL2::SDL2-static opengl32 shell32 )#for sdl_opengl3 by find package
    elseif(UNIX AND NOT APPLE)#for linux only
        target_link_libraries (Dominique PRIVATE GL SDL2 ${CMAKE_DL_LIBS} )#for sdl_opengl3 by find package
    endif ()
endif()



include(GNUInstallDirs)

set_target_properties(Dominique
                      PROPERTIES 
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

### Add some usable files to project build folder
set (RequiredExtras
    "TODO.txt"
)
get_target_property(BINARY_EXECUTABLE_OUTPUT Dominique RUNTIME_OUTPUT_DIRECTORY)
foreach (_file ${RequiredExtras})
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        list( APPEND extraFiles COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_SOURCE_DIR}/${_file}" "${BINARY_EXECUTABLE_OUTPUT}/$<CONFIG>/")
    else()
        list( APPEND extraFiles COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_SOURCE_DIR}/${_file}" "${BINARY_EXECUTABLE_OUTPUT}/")
    endif()
endforeach()
add_custom_command(TARGET Dominique POST_BUILD
                    ${extraFiles}
)

#preparing install step
set_target_properties(Dominique PROPERTIES RESOURCE "${RequiredExtras}")

install(TARGETS Dominique
    RUNTIME DESTINATION  ${CMAKE_INSTALL_BINDIR}
    RESOURCE DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION  ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION  ${CMAKE_INSTALL_LIBDIR}
    OBJECTS DESTINATION  ${CMAKE_INSTALL_LIBDIR}
)
