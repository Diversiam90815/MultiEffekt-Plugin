/*
  ==============================================================================

	Module			Paramters
	Description		Collection of constants and enums used in the project

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>


//==============================================================================
//						PARAMETERS
//==============================================================================

constexpr auto			inputGainName			  = "Input";
constexpr auto			paramInput				  = "input";
constexpr float			inputMinValue			  = -24.0f;
constexpr float			inputMaxValue			  = 6.0f;
constexpr float			inputDefaultValue		  = 0.0f;

constexpr auto			outputName				  = "Output";
constexpr auto			paramOutput				  = "output";
constexpr float			outputMinValue			  = -24.0f;
constexpr float			outputMaxValue			  = 24.0f;
constexpr float			outputDefaultValue		  = 0.0f;

constexpr auto			driveName				  = "Drive";
constexpr auto			paramDrive				  = "drive";
constexpr float			driveMinValue			  = 0.0f;
constexpr float			driveMaxValue			  = 24.0f;
constexpr float			driveDefaultValue		  = 0.0f;

constexpr auto			blendNameDistortion		  = "Dry/Wet (Distortion)";
constexpr auto			paramBlendDist			  = "drywetDistortion";
constexpr auto			blendNameDelay			  = "Dry/Wet (Delay)";
constexpr auto			paramBlendDelay			  = "drywetDelay";
constexpr float			blendMinValue			  = 0.0f;
constexpr float			blendMaxValue			  = 1.0f;
constexpr float			blendDefaultValue		  = 0.0f;

constexpr auto			distModelName			  = "Type";
constexpr auto			paramDistModel			  = "distortiontype";
const juce::StringArray distModelsArray			  = {"Hard", "Soft", "Saturation"};

constexpr auto			delayTimeName			  = "Delay Time in MS";
constexpr auto			paramDelayTime			  = "delayTimeMS";
constexpr float			delayTimeMinValue		  = 0.0f;
constexpr float			delayTimeMaxValue		  = 2000.f; // 2 Seconds of maximum delay time
constexpr float			delayTimeDefaultValue	  = 0.0f;

constexpr auto			delayFeedbackName		  = "Feedback";
constexpr auto			paramDelayFeedback		  = "delayFeedback";
constexpr float			delayFeedbackMinValue	  = 0.0f;
constexpr float			delayFeedbackMaxValue	  = 1.0f;
constexpr float			delayFeedbackDefaultValue = 0.0f;

constexpr auto			delayModelName			  = "Type";
constexpr auto			paramDelayModel			  = "delaytype";
const juce::StringArray delayModelArray			  = {"Single Tap", "Ping Pong"};


//==============================================================================
//						ENUM
//==============================================================================

enum DistortionType
{
	hardClipping = 1,
	softClipping,
	saturation
};

enum DelayType
{
	SingleTap = 1,
	PingPong
};