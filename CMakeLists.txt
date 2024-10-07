cmake_minimum_required(VERSION 3.25)

project(PluginTemplate VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

# Allow folders in Visual Studio solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (SOURCE_FILES_DIR ${PROJECT_SOURCE_DIR}/Source/)
set (SUBMODULES_DIR ${PROJECT_SOURCE_DIR}/submodules/)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#-----------------------------------------------------------------------------------------
# Files
#-----------------------------------------------------------------------------------------

set(Header_Files
        ${SOURCE_FILES_DIR}/PluginProcessor.h
        ${SOURCE_FILES_DIR}/PluginEditor.h
        
        ${SOURCE_FILES_DIR}/Parameters.h
)

set(Source_Files
         ${SOURCE_FILES_DIR}/PluginProcessor.cpp
         ${SOURCE_FILES_DIR}/PluginEditor.cpp
)

source_group("Source Files" FILES ${Source_Files})


#-----------------------------------------------------------------------------------------
# Juce API
#-----------------------------------------------------------------------------------------

add_subdirectory(submodules/JUCE)

# Add the plugin target
juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "DiversiamProduction"
    PLUGIN_MANUFACTURER_CODE 3160
    PLUGIN_CODE IOTO
    FORMATS Standalone
    PRODUCT_NAME "${PROJECT_NAME}"
)

# Generate the JuceHeader.h
juce_generate_juce_header(${PROJECT_NAME})



set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

target_sources(${PROJECT_NAME} PRIVATE  
        ${ALL_FILES} 
)


target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
)


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
        -DENV_DEVELOPMENT
        _CRT_SECURE_NO_WARNINGS
)


set (PROJECT_LIBS juce::juce_audio_utils
                  juce::juce_audio_plugin_client
                  juce::juce_core
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBS} )


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
        /WX-        # Don't treat warnings as errors
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
)

# Suppress specific compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    /wd4146  # Suppress warning C4146
    /wd4996  # Suppress warning C4996
)