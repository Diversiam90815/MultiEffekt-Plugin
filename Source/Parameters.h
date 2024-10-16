#pragma once

#include <JuceHeader.h>

//==============================================================================
//						PARAMETERS
//==============================================================================

constexpr auto	inputGainName	   = "Input";
constexpr auto	paramInput		   = "input";
constexpr float inputMinValue	   = -24.0f;
constexpr float inputMaxValue	   = 6.0f;
constexpr float inputDefaultValue  = 0.0f;

constexpr auto	outputName		   = "Output";
constexpr auto	paramOutput		   = "output";
constexpr float outputMinValue	   = -24.0f;
constexpr float outputMaxValue	   = 6.0f;
constexpr float outputDefaultValue = 0.0f;

constexpr auto	driveName		   = "Drive";
constexpr auto	paramDrive		   = "drive";
constexpr float driveMinValue	   = 0.0f;
constexpr float driveMaxValue	   = 24.0f;
constexpr float driveDefaultValue  = 0.0f;

constexpr auto	blendName		   = "Dry/Wet";
constexpr auto	paramBlend		   = "drywet";
constexpr float blendMinValue	   = 0.0f;
constexpr float blendMaxValue	   = 100.0f;
constexpr float blendDefaultValue  = 0.0f;