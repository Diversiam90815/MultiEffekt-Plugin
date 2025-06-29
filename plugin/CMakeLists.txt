#==========================================
#   Audio Multi Effect Plugin
#       by Jens W. Langenberg
#==========================================

cmake_minimum_required(VERSION 3.25)

set(PROJECT_VERSION 0.1.71)

project(MultiEffectPlugin VERSION ${PROJECT_VERSION} LANGUAGES CXX)


#-----------------------------------------------------------------------------------------
#   Directories
#-----------------------------------------------------------------------------------------

set (SOURCE_FILES_DIR ${PROJECT_SOURCE_DIR})

set(PROCESSOR_DIR   ${SOURCE_FILES_DIR}/Processor)
set(EFFECTS_DIR     ${SOURCE_FILES_DIR}/Effects)
set(UI_DIR          ${SOURCE_FILES_DIR}/UI)
set(BUFFER_DIR      ${SOURCE_FILES_DIR}/Buffer)
set(MISC_DIR        ${SOURCE_FILES_DIR}/Misc)

set(ALL_PROJECT_DIRS
        ${PROCESSOR_DIR}
        ${EFFECTS_DIR}
        ${UI_DIR}
        ${BUFFER_DIR}
        ${MISC_DIR}
)


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

set(Effect_Base_Files 
        ${EFFECTS_DIR}/EffectBase.h
)

set(Processor_Files 
        ${PROCESSOR_DIR}/PluginProcessor.h  ${PROCESSOR_DIR}/PluginProcessor.cpp
)

set(Effect_Distortion_Files 
        ${EFFECTS_DIR}/Distortion/Distortion.h         ${EFFECTS_DIR}/Distortion/Distortion.cpp
)

set(Effect_Delay_Files 
        ${EFFECTS_DIR}/Delay/Delay.h              ${EFFECTS_DIR}/Delay/Delay.cpp
)

set(Effect_Panner_Files
        ${EFFECTS_DIR}/Panner/PannerBase.h
        ${EFFECTS_DIR}/Panner/PannerManager.h      ${EFFECTS_DIR}/Panner/PannerManager.cpp
        ${EFFECTS_DIR}/Panner/MonoPanner.h         ${EFFECTS_DIR}/Panner/MonoPanner.cpp
        ${EFFECTS_DIR}/Panner/StereoPanner.h       ${EFFECTS_DIR}/Panner/StereoPanner.cpp
)

set(UI_Files 
        ${UI_DIR}/PluginEditor.h            ${UI_DIR}/PluginEditor.cpp
)

set(Buffer_Files 
        ${BUFFER_DIR}/CircularBuffer.h      ${BUFFER_DIR}/CircularBuffer.cpp 
)

set(Misc_Files 
        ${MISC_DIR}/Parameters.h
)


set(ALL_FILES
    ${Processor_Files}
    ${Effect_Base_Files}
    ${Effect_Distortion_Files}
    ${Effect_Delay_Files}
    ${Effect_Panner_Files}
    ${UI_Files}
    ${Buffer_Files}
    ${Misc_Files}
)


#-----------------------------------------------------------------------------------------
#   Source Groups
#-----------------------------------------------------------------------------------------

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})


#-----------------------------------------------------------------------------------------
#   Target Sources
#-----------------------------------------------------------------------------------------

target_sources(${PROJECT_NAME} PRIVATE  
        ${ALL_FILES} 
)


#-----------------------------------------------------------------------------------------
#   Target Include Directories
#-----------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${CMAKE_BINARY_DIR}/include/
        ${ALL_PROJECT_DIRS}
)


#-----------------------------------------------------------------------------------------
#   Target Link Libraries
#-----------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_plugin_client
        juce::juce_core
        juce::juce_dsp
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
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
        _CRT_SECURE_NO_WARNINGS
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
        /wd4100  # Suppress warning C4100 (unreferenced parameter)
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
)
