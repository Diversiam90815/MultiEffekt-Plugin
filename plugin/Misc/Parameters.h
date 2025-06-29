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

constexpr auto			paramMixDelay			   = "mixDelay";
constexpr auto			delayMixName			   = "Mix (Delay)";
constexpr auto			paramMixDistortion		   = "mixDistortion";
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
//				Parametric EQ
//==============================================

// Band 0 (Low Shelf)
constexpr auto			paramEqBand0Frequency	   = "band0_frequency";
constexpr auto			eqBand0FrequencyName	   = "Low Band Frequency";
constexpr float			eqBand0FrequencyMin		   = 20.0f;
constexpr float			eqBand0FrequencyMax		   = 500.0f;
constexpr float			eqBand0FrequencyDefault	   = 100.0f;

constexpr auto			paramEqBand0Gain		   = "band0_gain";
constexpr auto			eqBand0GainName			   = "Low Band Gain";
constexpr float			eqBandGainMin			   = -24.0f;
constexpr float			eqBandGainMax			   = 24.0f;
constexpr float			eqBandGainDefault		   = 0.0f;

constexpr auto			paramEqBand0Q			   = "band0_q";
constexpr auto			eqBand0QName			   = "Low Band Q";
constexpr float			eqBandQMin				   = 0.1f;
constexpr float			eqBandQMax				   = 20.0f;
constexpr float			eqBandQDefault			   = 0.707f;

constexpr auto			paramEqBand0Enabled		   = "band0_enabled";
constexpr auto			eqBand0EnabledName		   = "Low Band Enabled";
constexpr bool			eqBandEnabledDefault	   = true;

// Band 1 (Low Mid Peaking)
constexpr auto			paramEqBand1Frequency	   = "band1_frequency";
constexpr auto			eqBand1FrequencyName	   = "Low Mid Frequency";
constexpr float			eqBand1FrequencyMin		   = 100.0f;
constexpr float			eqBand1FrequencyMax		   = 2000.0f;
constexpr float			eqBand1FrequencyDefault	   = 500.0f;

constexpr auto			paramEqBand1Gain		   = "band1_gain";
constexpr auto			eqBand1GainName			   = "Low Mid Gain";

constexpr auto			paramEqBand1Q			   = "band1_q";
constexpr auto			eqBand1QName			   = "Low Mid Q";

constexpr auto			paramEqBand1Enabled		   = "band1_enabled";
constexpr auto			eqBand1EnabledName		   = "Low Mid Enabled";

// Band 2 (High Mid Peaking)
constexpr auto			paramEqBand2Frequency	   = "band2_frequency";
constexpr auto			eqBand2FrequencyName	   = "High Mid Frequency";
constexpr float			eqBand2FrequencyMin		   = 500.0f;
constexpr float			eqBand2FrequencyMax		   = 8000.0f;
constexpr float			eqBand2FrequencyDefault	   = 2000.0f;

constexpr auto			paramEqBand2Gain		   = "band2_gain";
constexpr auto			eqBand2GainName			   = "High Mid Gain";

constexpr auto			paramEqBand2Q			   = "band2_q";
constexpr auto			eqBand2QName			   = "High Mid Q";

constexpr auto			paramEqBand2Enabled		   = "band2_enabled";
constexpr auto			eqBand2EnabledName		   = "High Mid Enabled";

// Band 3 (High Shelf)
constexpr auto			paramEqBand3Frequency	   = "band3_frequency";
constexpr auto			eqBand3FrequencyName	   = "High Band Frequency";
constexpr float			eqBand3FrequencyMin		   = 2000.0f;
constexpr float			eqBand3FrequencyMax		   = 20000.0f;
constexpr float			eqBand3FrequencyDefault	   = 8000.0f;

constexpr auto			paramEqBand3Gain		   = "band3_gain";
constexpr auto			eqBand3GainName			   = "High Band Gain";

constexpr auto			paramEqBand3Q			   = "band3_q";
constexpr auto			eqBand3QName			   = "High Band Q";

constexpr auto			paramEqBand3Enabled		   = "band3_enabled";
constexpr auto			eqBand3EnabledName		   = "High Band Enabled";


//==============================================
//				Effect Params
//==============================================

// Distortion parameters
constexpr auto			distortionParameters	   = std::array{paramDistortionDrive, paramMixDistortion, paramOutput, paramDistortionType};

// Delay parameters
constexpr auto			delayParameters			   = std::array{paramMixDelay, paramDelayTimeLeft, paramDelayTimeRight, paramDelayFeedback, paramDelayModel};

// Gain parameters
constexpr auto			gainParameters			   = std::array{paramInput, paramOutput};

// Panner parameters
constexpr auto			pannerMonoParameters	   = std::array{paramMonoPanValue, paramMonoLfoFreq, paramMonoLfoDepth};

constexpr auto			pannerStereoParameters =
	std::array{paramStereoLeftPanValue, paramStereoRightPanValue, paramStereoLeftLfoFreq, paramStereoRightLfoFreq, paramStereoLeftLfoDepth, paramStereoRightLfoDepth};

constexpr auto pannerCommonParameters = std::array{paramPannerLfoEnabled};

// EQ parameters
constexpr auto eqParameters =
	std::array{paramEqBand0Frequency, paramEqBand0Gain, paramEqBand0Q, paramEqBand0Enabled, paramEqBand1Frequency, paramEqBand1Gain, paramEqBand1Q, paramEqBand1Enabled,
			   paramEqBand2Frequency, paramEqBand2Gain, paramEqBand2Q, paramEqBand2Enabled, paramEqBand3Frequency, paramEqBand3Gain, paramEqBand3Q, paramEqBand3Enabled};


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
