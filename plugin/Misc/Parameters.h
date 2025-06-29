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

constexpr auto			paramMixDelay			   = "mix";
constexpr auto			delayMixName			   = "Mix (Delay)";
constexpr auto			paramMixDistortion		   = "mix";
constexpr auto			distortionMixName		   = "Mix (Distortion)";
constexpr float			mixMinValue				   = 0.0f;
constexpr float			mixMaxValue				   = 1.0f;
constexpr float			mixDefaultValue			   = 0.0f;


//==============================================
//				Distortion
//==============================================

constexpr auto			paramDistortionDrive	   = "drive";
constexpr auto			distortionDriveName		   = "Drive";
constexpr float			distortionDriveMin		   = 0.0f;
constexpr float			distortionDriveMax		   = 24.0f;
constexpr float			distortionDriveDefault	   = 0.0f;

constexpr auto			paramDistortionType		   = "distortiontype";
constexpr auto			distortionTypeName		   = "Type";
const juce::StringArray distortionTypeArray		   = {"Hard", "Soft", "Saturation"};


//==============================================
//				Delay
//==============================================

constexpr auto			paramDelayTimeLeft		   = "delayTimeLeft";
constexpr auto			delayTimeNameLeft		   = "Delay Time in MS (Left)";
constexpr auto			paramDelayTimeRight		   = "delayTimeRight";
constexpr auto			delayTimeNameRight		   = "Delay Time in MS (Right)";
constexpr float			delayTimeMin			   = 0.0f;
constexpr float			delayTimeMax			   = 2000.f; // 2 Seconds of maximum delay time
constexpr float			delayTimeDefault		   = 0.0f;

constexpr auto			paramDelayFeedback		   = "feedback";
constexpr auto			delayFeedbackName		   = "Feedback";
constexpr float			delayFeedbackMin		   = 0.0f;
constexpr float			delayFeedbackMax		   = 1.0f;
constexpr float			delayFeedbackDefault	   = 0.0f;

constexpr auto			paramDelayModel			   = "delaytype";
constexpr auto			delayTypeName			   = "Type";
const juce::StringArray delayTypeArray			   = {"Single Tap", "Ping Pong"};


//==============================================
//				Panner
//==============================================

constexpr auto			paramMonoPanValue		   = "pan";
constexpr auto			monoPanValueName		   = "Pan";
constexpr float			monoPanValueMin			   = -1.0f;
constexpr float			monoPanValueMax			   = 1.0f;
constexpr float			monoPanValueDefault		   = 0.0f;

constexpr auto			paramStereoLeftPanValue	   = "leftPan";
constexpr auto			stereoLeftPanValueName	   = "Pan (Left Channel)";
constexpr float			stereoLeftPanValueMin	   = -1.0f;
constexpr float			stereoLeftPanValueMax	   = 1.0f;
constexpr float			stereoLeftPanValueDefault  = 0.0f;

constexpr auto			paramStereoRightPanValue   = "rightPan";
constexpr auto			stereoRightPanValueName	   = "Pan (Right Channel)";
constexpr float			stereoRightPanValueMin	   = -1.0f;
constexpr float			stereoRightPanValueMax	   = 1.0f;
constexpr float			stereoRightPanValueDefault = 0.0f;


constexpr auto			paramMonoLfoFreq		   = "lfoFreq";
constexpr auto			monoLfoFreqName			   = "LFO Frequency";
constexpr float			monoLfoFreqMin			   = 0.0f;
constexpr float			monoLfoFreqMax			   = 20.0f;
constexpr float			monoLfoFreqDefault		   = 0.0f;

constexpr auto			paramStereoLeftLfoFreq	   = "leftLfoFreq";
constexpr auto			stereoLeftLfoFreqName	   = "LFO Frequency (Left Channel)";
constexpr float			stereoLeftLfoFreqMin	   = 0.0f;
constexpr float			stereoLeftLfoFreqMax	   = 20.0f;
constexpr float			stereoLeftLfoFreqDefault   = 0.0f;

constexpr auto			paramStereoRightLfoFreq	   = "rightLfoFreq";
constexpr auto			stereoRightLfoFreqName	   = "LFO Frequency (Right Channel)";
constexpr float			stereoRightLfoFreqMin	   = 0.0f;
constexpr float			stereoRightLfoFreqMax	   = 20.0f;
constexpr float			stereoRightLfoFreqDefault  = 0.0f;


constexpr auto			paramMonoLfoDepth		   = "lfoDepth";
constexpr auto			monoLfoDepthName		   = "LFO Depth";
constexpr float			monoLfoDepthMin			   = 0.0f;
constexpr float			monoLfoDepthMax			   = 1.0f;
constexpr float			monoLfoDepthDefault		   = 0.0f;

constexpr auto			paramStereoLeftLfoDepth	   = "leftLfoDepth";
constexpr auto			stereoLeftLfoDepthName	   = "LFO Depth (Left Channel)";
constexpr float			stereoLeftLfoDepthMin	   = 0.0f;
constexpr float			stereoLeftLfoDepthMax	   = 1.0f;
constexpr float			stereoLeftLfoDepthDefault  = 0.0f;

constexpr auto			paramStereoRightLfoDepth   = "rightLfoDepth";
constexpr auto			stereoRightLfoDepthName	   = "LFO Depth (Right Channel)";
constexpr float			stereoRightLfoDepthMin	   = 0.0f;
constexpr float			stereoRightLfoDepthMax	   = 1.0f;
constexpr float			stereoRightLfoDepthDefault = 0.0f;

constexpr auto			paramPannerLfoEnabled	   = "lfoEnabled";
constexpr auto			pannerLfoEnabledName	   = "LFO enabled";
constexpr bool			pannerLfoEnabledDefault	   = false;


//==============================================
//				Effect Params
//==============================================

// Distortion parameter mappings (EffectBase parameter name -> JUCE parameter ID)
constexpr auto			distortionParameters	   = std::array{paramDistortionDrive, paramMixDistortion, paramOutput, paramDistortionType};

// Delay parameter mappings
constexpr auto			delayParameters			   = std::array{paramMixDelay, paramDelayTimeLeft, paramDelayTimeRight, paramDelayFeedback, paramDelayModel};

// Gain parameter mappings
constexpr auto			gainParameters			   = std::array{paramInput, paramOutput};

// Panner parameter mappings
constexpr auto			pannerMonoParameters	   = std::array{paramMonoPanValue, paramMonoLfoFreq, paramMonoLfoDepth};

constexpr auto			pannerStereoParameters =
	std::array{paramStereoLeftPanValue, paramStereoRightPanValue, paramStereoLeftLfoFreq, paramStereoRightLfoFreq, paramStereoLeftLfoDepth, paramStereoRightLfoDepth};

constexpr auto pannerCommonParameters = std::array{paramPannerLfoEnabled};


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

enum PannerType
{
	Mono = 1,
	Stereo
};
