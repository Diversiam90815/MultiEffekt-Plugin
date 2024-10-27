#-----------------------------------------------------------------------------------------
# Audio Plugin
#-----------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)

project(AudioPlugin VERSION 0.1.0)


#-----------------------------------------------------------------------------------------
#   Directories
#-----------------------------------------------------------------------------------------

set (SOURCE_FILES_DIR ${PROJECT_SOURCE_DIR}/Source)
set (HEADER_FILES_DIR ${PROJECT_SOURCE_DIR}/include)


#-----------------------------------------------------------------------------------------
#   Juce Plugin Target
#-----------------------------------------------------------------------------------------

juce_add_plugin(${PROJECT_NAME}
                COMPANY_NAME "DiversiamProduction"
                PLUGIN_CODE IOTO
                IS_SYNTH FALSE
                NEEDS_MIDI_INPUT FALSE
                NEEDS_MIDI_OUTPUT FALSE
                FORMATS VST3 Standalone
                PLUGIN_MANUFACTURER_CODE 3160
                PRODUCT_NAME "${PROJECT_NAME}"
)

configure_file(${CMAKE_SOURCE_DIR}/Project.h.in ${CMAKE_BINARY_DIR}/include/Project.h @ONLY)


#-----------------------------------------------------------------------------------------
#   Files
#-----------------------------------------------------------------------------------------

set(Header_Files
        ${HEADER_FILES_DIR}/PluginProcessor.h
        ${HEADER_FILES_DIR}/PluginEditor.h
        
        ${HEADER_FILES_DIR}/Parameters.h
)

set(Source_Files
         ${SOURCE_FILES_DIR}/PluginProcessor.cpp
         ${SOURCE_FILES_DIR}/PluginEditor.cpp
)


#-----------------------------------------------------------------------------------------
#   Source Groups
#-----------------------------------------------------------------------------------------

source_group("Plugin Sources" FILES ${Source_Files})
source_group("Plugin Headers" FILES ${Header_Files})


#-----------------------------------------------------------------------------------------
#   Target Sources
#-----------------------------------------------------------------------------------------

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

target_sources(${PROJECT_NAME} PRIVATE  
        ${ALL_FILES} 
)


#-----------------------------------------------------------------------------------------
#   Target Include Directories
#-----------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${CMAKE_BINARY_DIR}/include
        ${SOURCE_FILES_DIR}
        ${HEADER_FILES_DIR}
)


#-----------------------------------------------------------------------------------------
#   Target Link Libraries
#-----------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_plugin_client
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)


#-----------------------------------------------------------------------------------------
#   Target Compile Definitions
#-----------------------------------------------------------------------------------------

## JUCE compiler options
target_compile_definitions(${PROJECT_NAME} PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WINDOWS_MEDIA_FORMAT=1
        JUCE_LOAD_CURL_SYMBOLS_LAZILY=1
        JUCE_WASAPI=1
        JUCE_DIRECTSOUND=1
        JUCE_ASIO=0
        JUCE_USE_ANDROID_OBOE=1
        JUCE_USE_OBOE_STABILIZED_CALLBACK=1
)

## Project compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
                /Oi;
                /Gy
        >
        $<$<CONFIG:Debug>:
                /Od;
                /Z7
        >
        /sdl
        /MP
        /wd4146  # Suppress warning C4146
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
)
