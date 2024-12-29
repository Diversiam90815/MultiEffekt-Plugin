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

//==============================================
//				Audio Processor
//==============================================

constexpr auto			paramInput				   = "input";
constexpr auto			inputGainName			   = "Input";
constexpr float			inputMinValue			   = -24.0f;
constexpr float			inputMaxValue			   = 6.0f;
constexpr float			inputDefaultValue		   = 0.0f;

constexpr auto			paramOutput				   = "output";
constexpr auto			outputName				   = "Output";
constexpr float			outputMinValue			   = -24.0f;
constexpr float			outputMaxValue			   = 24.0f;
constexpr float			outputDefaultValue		   = 0.0f;


//==============================================
//				Distortion
//==============================================

constexpr auto			paramDrive				   = "drive";
constexpr auto			driveName				   = "Drive";
constexpr float			driveMinValue			   = 0.0f;
constexpr float			driveMaxValue			   = 24.0f;
constexpr float			driveDefaultValue		   = 0.0f;

constexpr auto			paramBlendDist			   = "drywetDistortion";
constexpr auto			blendNameDistortion		   = "Dry/Wet (Distortion)";
constexpr auto			blendNameDelay			   = "Dry/Wet (Delay)";
constexpr auto			paramBlendDelay			   = "drywetDelay";
constexpr float			blendMinValue			   = 0.0f;
constexpr float			blendMaxValue			   = 1.0f;
constexpr float			blendDefaultValue		   = 0.0f;

constexpr auto			paramDistModel			   = "distortiontype";
constexpr auto			distModelName			   = "Type";
const juce::StringArray distModelsArray			   = {"Hard", "Soft", "Saturation"};


//==============================================
//				Delay
//==============================================

constexpr auto			paramDelayTimeLeft		   = "delayTimeMSLeft";
constexpr auto			delayTimeNameLeft		   = "Delay Time in MS (Left)";
constexpr auto			delayTimeNameRight		   = "Delay Time in MS (Right)";
constexpr auto			paramDelayTimeRight		   = "delayTimeMSRight";
constexpr float			delayTimeMinValue		   = 0.0f;
constexpr float			delayTimeMaxValue		   = 2000.f; // 2 Seconds of maximum delay time
constexpr float			delayTimeDefaultValue	   = 0.0f;

constexpr auto			paramDelayFeedback		   = "delayFeedback";
constexpr auto			delayFeedbackName		   = "Feedback";
constexpr float			delayFeedbackMinValue	   = 0.0f;
constexpr float			delayFeedbackMaxValue	   = 1.0f;
constexpr float			delayFeedbackDefaultValue  = 0.0f;

constexpr auto			paramDelayModel			   = "delaytype";
constexpr auto			delayModelName			   = "Type";
const juce::StringArray delayModelArray			   = {"Single Tap", "Ping Pong"};


//==============================================
//				Panner
//==============================================

constexpr auto			paramMonoPanValue		   = "monoPanValue";
constexpr auto			monoPanValueName		   = "Pan";
constexpr float			monoPanValueMin			   = -1.0f;
constexpr float			monoPanValueMax			   = 1.0f;
constexpr float			monoPanValueDefault		   = 0.0f;

constexpr auto			paramStereoLeftPanValue	   = "stereoLeftPanValue";
constexpr auto			stereoLeftPanValueName	   = "Pan (Left Channel)";
constexpr float			stereoLeftPanValueMin	   = -1.0f;
constexpr float			stereoLeftPanValueMax	   = 1.0f;
constexpr float			stereoLeftPanValueDefault  = 0.0f;

constexpr auto			paramStereoRightPanValue   = "stereoRightPanValue";
constexpr auto			stereoRightPanValueName	   = "Pan (Right Channel)";
constexpr float			stereoRightPanValueMin	   = -1.0f;
constexpr float			stereoRightPanValueMax	   = 1.0f;
constexpr float			stereoRightPanValueDefault = 0.0f;


constexpr auto			paramMonoLfoFreq		   = "monoLfoFreq";
constexpr auto			monoLfoFreqName			   = "LFO Frequency";
constexpr float			monoLfoFreqMin			   = 0.0f;
constexpr float			monoLfoFreqMax			   = 20.0f;
constexpr float			monoLfoFreqDefault		   = 0.0f;

constexpr auto			paramStereoLeftLfoFreq	   = "stereoLeftLfoFreq";
constexpr auto			stereoLeftLfoFreqName	   = "LFO Frequency (Left Channel)";
constexpr float			stereoLeftLfoFreqMin	   = 0.0f;
constexpr float			stereoLeftLfoFreqMax	   = 20.0f;
constexpr float			stereoLeftLfoFreqDefault   = 0.0f;

constexpr auto			paramStereoRightLfoFreq	   = "stereoRightLfoFreq";
constexpr auto			stereoRightLfoFreqName	   = "LFO Frequency (Right Channel)";
constexpr float			stereoRightLfoFreqMin	   = 0.0f;
constexpr float			stereoRightLfoFreqMax	   = 20.0f;
constexpr float			stereoRightLfoFreqDefault  = 0.0f;


constexpr auto			paramMonoLfoDepth		   = "monoLfoDepth";
constexpr auto			monoLfoDepthName		   = "LFO Depth";
constexpr float			monoLfoDepthMin			   = 0.0f;
constexpr float			monoLfoDepthMax			   = 1.0f;
constexpr float			monoLfoDepthDefault		   = 0.0f;

constexpr auto			paramStereoLeftLfoDepth	   = "stereoLeftLfoDepth";
constexpr auto			stereoLeftLfoDepthName	   = "LFO Depth (Left Channel)";
constexpr float			stereoLeftLfoDepthMin	   = 0.0f;
constexpr float			stereoLeftLfoDepthMax	   = 1.0f;
constexpr float			stereoLeftLfoDepthDefault  = 0.0f;

constexpr auto			paramStereoRightLfoDepth   = "stereoRightLfoDepth";
constexpr auto			stereoRightLfoDepthName	   = "LFO Depth (Right Channel)";
constexpr float			stereoRightLfoDepthMin	   = 0.0f;
constexpr float			stereoRightLfoDepthMax	   = 1.0f;
constexpr float			stereoRightLfoDepthDefault = 0.0f;

constexpr auto			paramPannerLfoEnabled	   = "pannerLfoEnabledBool";
constexpr auto			pannerLfoEnabledName	   = "LFO enabled";
constexpr bool			pannerLfoEnabledDefault	   = false;


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