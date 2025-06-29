cmake_minimum_required(VERSION 3.25)

project(AudioPluginTest)


enable_testing()


add_executable(${PROJECT_NAME}
    source/ProcessorTest.cpp
    source/DelayTest.cpp
    source/DistortionTest.cpp
    source/PannerTest.cpp
)


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${GOOGLETEST_SOURCE_DIR}/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../plugin/Effects/
        ${CMAKE_CURRENT_SOURCE_DIR}/../plugin/Buffer/
        ${CMAKE_CURRENT_SOURCE_DIR}/../plugin/Processor/
        ${CMAKE_CURRENT_SOURCE_DIR}/../plugin/UI/
        ${CMAKE_CURRENT_SOURCE_DIR}/../plugin/Misc/
        ${JUCE_SOURCE_DIR}/modules
        ${CMAKE_BINARY_DIR}/include  # Include directory where Project.h is generated

)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        MultiEffectPlugin
        GTest::gtest_main
)


include(GoogleTest)


target_compile_definitions(${PROJECT_NAME} PUBLIC
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)


## Discover GTests
if (CMAKE_GENERATOR STREQUAL Xcode)
gtest_discover_tests(${PROJECT_NAME} DISCOVERY_MODE PRE_TEST)
else()
gtest_discover_tests(${PROJECT_NAME})
endif()


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4100 )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()