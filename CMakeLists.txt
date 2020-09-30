cmake_minimum_required(VERSION 3.17)

# Arduino toolchain
set(CMAKE_TOOLCHAIN_FILE arduino-cmake/Arduino-toolchain.cmake)

project(TelemetrySystem CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Clang time trace
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# enable cache system
include(cmake/Cache.cmake)

# sanitizer options if supported by compiler
add_library(project_options INTERFACE)
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

add_subdirectory(src)
