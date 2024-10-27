cmake_minimum_required(VERSION 3.25)

project(ProjectTemplate LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


## Setting the lib directory for project included packages
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

## Include the CPM (Package Manager used by CMake)
include(cmake/cpm.cmake)

## Setting the environment
add_compile_definitions(${PROJECT_NAME} PUBLIC -DENV_DEVELOPMENT)


#----------------------------
# Juce API
#----------------------------

CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY juce-framework/JUCE
        GIT_TAG 8.0.3
        VERSION 8.0.3
        SOURCE_DIR ${LIB_DIR}/juce
)


#----------------------------
# Google Test
#----------------------------

CPMAddPackage(
        NAME GOOGLETEST
        GITHUB_REPOSITORY google/googletest
        VERSION 1.15.2
        SOURCE_DIR ${LIB_DIR}/googletest
        OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
        )
        
enable_testing()


add_subdirectory(test)
add_subdirectory(plugin)


if(MSVC)
        add_compile_options(/Wall /WX)
else()
        add_compile_options(-Wall -Wextra -Wpedantic)
endif()


