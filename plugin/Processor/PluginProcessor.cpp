/*
  ==============================================================================

	Module			MainPluginProcessor
	Description		Main processor of the plugin

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


PluginProcessor::PluginProcessor()
	: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true)),
	  mValueTreeState(*this, nullptr, "PARAMETERS", createParameterLayout())
{
	mValueTreeState.addParameterListener(paramInput, this);
	mValueTreeState.addParameterListener(paramOutput, this);
	mValueTreeState.addParameterListener(paramDistortionDrive, this);
	mValueTreeState.addParameterListener(paramMixDistortion, this);
	mValueTreeState.addParameterListener(paramDistortionType, this);
	mValueTreeState.addParameterListener(paramMixDelay, this);
	mValueTreeState.addParameterListener(paramDelayTimeLeft, this);
	mValueTreeState.addParameterListener(paramDelayTimeRight, this);
	mValueTreeState.addParameterListener(paramDelayFeedback, this);
	mValueTreeState.addParameterListener(paramDelayModel, this);
	mValueTreeState.addParameterListener(paramMonoPanValue, this);
	mValueTreeState.addParameterListener(paramStereoLeftPanValue, this);
	mValueTreeState.addParameterListener(paramStereoRightPanValue, this);
	mValueTreeState.addParameterListener(paramMonoLfoFreq, this);
	mValueTreeState.addParameterListener(paramStereoLeftLfoFreq, this);
	mValueTreeState.addParameterListener(paramStereoRightLfoFreq, this);
	mValueTreeState.addParameterListener(paramMonoLfoDepth, this);
	mValueTreeState.addParameterListener(paramStereoLeftLfoDepth, this);
	mValueTreeState.addParameterListener(paramStereoRightLfoDepth, this);
	mValueTreeState.addParameterListener(paramPannerLfoEnabled, this);
	mValueTreeState.addParameterListener(paramEqBand0Frequency, this);
	mValueTreeState.addParameterListener(paramEqBand0Gain, this);
	mValueTreeState.addParameterListener(paramEqBand0Q, this);
	mValueTreeState.addParameterListener(paramEqBand0Enabled, this);
	mValueTreeState.addParameterListener(paramEqBand1Frequency, this);
	mValueTreeState.addParameterListener(paramEqBand1Gain, this);
	mValueTreeState.addParameterListener(paramEqBand1Q, this);
	mValueTreeState.addParameterListener(paramEqBand1Enabled, this);
	mValueTreeState.addParameterListener(paramEqBand2Frequency, this);
	mValueTreeState.addParameterListener(paramEqBand2Gain, this);
	mValueTreeState.addParameterListener(paramEqBand2Q, this);
	mValueTreeState.addParameterListener(paramEqBand2Enabled, this);
	mValueTreeState.addParameterListener(paramEqBand3Frequency, this);
	mValueTreeState.addParameterListener(paramEqBand3Gain, this);
	mValueTreeState.addParameterListener(paramEqBand3Q, this);
	mValueTreeState.addParameterListener(paramEqBand3Enabled, this);
}


PluginProcessor::~PluginProcessor()
{
	mValueTreeState.removeParameterListener(paramInput, this);
	mValueTreeState.removeParameterListener(paramOutput, this);
	mValueTreeState.removeParameterListener(paramDistortionDrive, this);
	mValueTreeState.removeParameterListener(paramMixDistortion, this);
	mValueTreeState.removeParameterListener(paramDistortionType, this);
	mValueTreeState.removeParameterListener(paramMixDelay, this);
	mValueTreeState.removeParameterListener(paramDelayTimeLeft, this);
	mValueTreeState.removeParameterListener(paramDelayTimeRight, this);
	mValueTreeState.removeParameterListener(paramDelayFeedback, this);
	mValueTreeState.removeParameterListener(paramDelayModel, this);
	mValueTreeState.removeParameterListener(paramMonoPanValue, this);
	mValueTreeState.removeParameterListener(paramStereoLeftPanValue, this);
	mValueTreeState.removeParameterListener(paramStereoRightPanValue, this);
	mValueTreeState.removeParameterListener(paramMonoLfoFreq, this);
	mValueTreeState.removeParameterListener(paramStereoLeftLfoFreq, this);
	mValueTreeState.removeParameterListener(paramStereoRightLfoFreq, this);
	mValueTreeState.removeParameterListener(paramMonoLfoDepth, this);
	mValueTreeState.removeParameterListener(paramStereoLeftLfoDepth, this);
	mValueTreeState.removeParameterListener(paramStereoRightLfoDepth, this);
	mValueTreeState.removeParameterListener(paramPannerLfoEnabled, this);
	mValueTreeState.removeParameterListener(paramEqBand0Frequency, this);
	mValueTreeState.removeParameterListener(paramEqBand0Gain, this);
	mValueTreeState.removeParameterListener(paramEqBand0Q, this);
	mValueTreeState.removeParameterListener(paramEqBand0Enabled, this);
	mValueTreeState.removeParameterListener(paramEqBand1Frequency, this);
	mValueTreeState.removeParameterListener(paramEqBand1Gain, this);
	mValueTreeState.removeParameterListener(paramEqBand1Q, this);
	mValueTreeState.removeParameterListener(paramEqBand1Enabled, this);
	mValueTreeState.removeParameterListener(paramEqBand2Frequency, this);
	mValueTreeState.removeParameterListener(paramEqBand2Gain, this);
	mValueTreeState.removeParameterListener(paramEqBand2Q, this);
	mValueTreeState.removeParameterListener(paramEqBand2Enabled, this);
	mValueTreeState.removeParameterListener(paramEqBand3Frequency, this);
	mValueTreeState.removeParameterListener(paramEqBand3Gain, this);
	mValueTreeState.removeParameterListener(paramEqBand3Q, this);
	mValueTreeState.removeParameterListener(paramEqBand3Enabled, this);
}


void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	mNumInputChannels = getTotalNumInputChannels();

	// Initialize spec for DSP modules
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate		  = sampleRate;
	spec.numChannels	  = getTotalNumInputChannels();

	mDistortionModule.prepare(spec);
	mDelayModule.prepare(spec, 2000);
	mPannerModule.prepare(spec);
	mEQModule.prepare(spec);

	updateParameters();
}


void PluginProcessor::updateParameters()
{
	updateGainParameters();
	updateDelayParameters();
	updateDistortionParameters();
	updatePannerParameters();
	updateEQParameters();
}


void PluginProcessor::setParameter(const std::string &name, float value)
{
	if (name == paramInput)
		setInput(value);
	else if (name == paramOutput)
		setOutput(value);
}


bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;

	return true;
}


void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	juce::ignoreUnused(midiMessages);

	juce::ScopedNoDenormals noDenormals;
	auto					totalNumInputChannels  = getTotalNumInputChannels();
	auto					totalNumOutputChannels = getTotalNumOutputChannels();

	// Apply input gain
	float					inputLevel			   = mInput.getNextValue();
	buffer.applyGain(juce::Decibels::decibelsToGain(inputLevel));

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// Processing the modules
	mDistortionModule.process(buffer);
	mDelayModule.process(buffer);
	mPannerModule.process(buffer);
	mEQModule.process(buffer);

	// Apply output gain
	float outputLevel = mOutput.getNextValue();
	buffer.applyGain(juce::Decibels::decibelsToGain(outputLevel));
}


juce::AudioProcessorEditor *PluginProcessor::createEditor()
{
	// We create a generic audio processor editor here, so we can work with the processing
	// without concerning about the UI at first!

	return new juce::GenericAudioProcessorEditor(*this);
}


template <typename EffectType, size_t N>
void PluginProcessor::updateEffectParameters(EffectType &effect, const std::array<const char *, N> &parameters)
{
	for (const auto &paramId : parameters)
	{
		if (auto *rawValue = mValueTreeState.getRawParameterValue(paramId))
		{
			effect.setParameter(paramId, rawValue->load());
		}
	}
}


void PluginProcessor::updateGainParameters()
{
	updateEffectParameters(*this, gainParameters);
}


void PluginProcessor::updateDelayParameters()
{
	updateEffectParameters(mDelayModule, delayParameters);

	// Handle special type conversion for delay type
	auto delayMode = static_cast<int>(mValueTreeState.getRawParameterValue(paramDelayModel)->load());
	switch (delayMode)
	{
	case 0: mDelayModule.setDelayType(DelayType::SingleTap); break;
	case 1: mDelayModule.setDelayType(DelayType::PingPong); break;
	default: break;
	}
}


void PluginProcessor::updateDistortionParameters()
{
	mDistortionModule.setDrive(mValueTreeState.getRawParameterValue(paramDistortionDrive)->load());
	mDistortionModule.setOutput(mValueTreeState.getRawParameterValue(paramOutput)->load());
	mDistortionModule.setMix(mValueTreeState.getRawParameterValue(paramMixDistortion)->load());

	auto model = static_cast<int>(mValueTreeState.getRawParameterValue(paramDistortionType)->load());
	switch (model)
	{
	case 0:
	{
		mDistortionModule.setCurrentDistortionType(DistortionType::hardClipping);
		break;
	}
	case 1:
	{
		mDistortionModule.setCurrentDistortionType(DistortionType::softClipping);
		break;
	}
	case 2:
	{
		mDistortionModule.setCurrentDistortionType(DistortionType::saturation);
		break;
	}
	default: break;
	}
}


void PluginProcessor::updatePannerParameters()
{
	// Always set common parameters
	updateEffectParameters(mPannerModule, pannerCommonParameters);

	if (mNumInputChannels == 1) // Mono
	{
		updateEffectParameters(mPannerModule, pannerMonoParameters);
	}
	else // Stereo
	{
		updateEffectParameters(mPannerModule, pannerStereoParameters);
	}
}


void PluginProcessor::updateEQParameters()
{
	updateEffectParameters(mEQModule, eqParameters);
}


void PluginProcessor::setOutput(float value)
{
	mOutput.setTargetValue(value);
}


void PluginProcessor::setInput(float value)
{
	mInput.setTargetValue(value);
}


juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

	// add parameters here
	auto input			 = std::make_unique<juce::AudioParameterFloat>(paramInput, inputGainName, inputMinValue, inputMaxValue, inputDefaultValue);
	auto output			 = std::make_unique<juce::AudioParameterFloat>(paramOutput, outputName, outputMinValue, outputMaxValue, outputDefaultValue);

	// Distortion
	auto distModel		 = std::make_unique<juce::AudioParameterChoice>(paramDistortionType, distortionTypeName, distortionTypeArray, 0);
	auto drive			 = std::make_unique<juce::AudioParameterFloat>(paramDistortionDrive, distortionDriveName, distortionDriveMin, distortionDriveMax, distortionDriveDefault);
	auto blendDistortion = std::make_unique<juce::AudioParameterFloat>(paramMixDistortion, distortionMixName, mixMinValue, mixMaxValue, mixDefaultValue);

	// Delay
	auto delayModel		 = std::make_unique<juce::AudioParameterChoice>(paramDelayModel, delayTypeName, delayTypeArray, 0);
	auto blendDelay		 = std::make_unique<juce::AudioParameterFloat>(paramMixDelay, delayMixName, mixMinValue, mixMaxValue, mixDefaultValue);
	auto delayTimeLeft	 = std::make_unique<juce::AudioParameterFloat>(paramDelayTimeLeft, delayTimeNameLeft, delayTimeMin, delayTimeMax, delayTimeDefault);
	auto delayTimeRight	 = std::make_unique<juce::AudioParameterFloat>(paramDelayTimeRight, delayTimeNameRight, delayTimeMin, delayTimeMax, delayTimeDefault);
	auto delayFeedback	 = std::make_unique<juce::AudioParameterFloat>(paramDelayFeedback, delayFeedbackName, delayFeedbackMin, delayFeedbackMax, delayFeedbackDefault);

	// Panner
	auto monoPanValue	 = std::make_unique<juce::AudioParameterFloat>(paramMonoPanValue, monoPanValueName, monoPanValueMin, monoPanValueMax, monoPanValueDefault);
	auto stereoLeftPanValue =
		std::make_unique<juce::AudioParameterFloat>(paramStereoLeftPanValue, stereoLeftPanValueName, stereoLeftPanValueMin, stereoLeftPanValueMax, stereoLeftPanValueDefault);
	auto stereoRightPanValue =
		std::make_unique<juce::AudioParameterFloat>(paramStereoRightPanValue, stereoRightPanValueName, stereoRightPanValueMin, stereoRightPanValueMax, stereoRightPanValueDefault);
	auto monoLfoFreq = std::make_unique<juce::AudioParameterFloat>(paramMonoLfoFreq, monoLfoFreqName, monoLfoFreqMin, monoLfoFreqMax, monoLfoFreqDefault);
	auto stereoLeftLfoFreq =
		std::make_unique<juce::AudioParameterFloat>(paramStereoLeftLfoFreq, stereoLeftLfoFreqName, stereoLeftLfoFreqMin, stereoLeftLfoFreqMax, stereoLeftLfoFreqDefault);
	auto stereoRightLfoFreq =
		std::make_unique<juce::AudioParameterFloat>(paramStereoRightLfoFreq, stereoRightLfoFreqName, stereoRightLfoFreqMin, stereoRightLfoFreqMax, stereoRightLfoFreqDefault);
	auto monoLfoDepth = std::make_unique<juce::AudioParameterFloat>(paramMonoLfoDepth, monoLfoDepthName, monoLfoDepthMin, monoLfoDepthMax, monoLfoDepthDefault);
	auto stereoLeftLfoDepth =
		std::make_unique<juce::AudioParameterFloat>(paramStereoLeftLfoDepth, stereoLeftLfoDepthName, stereoLeftLfoDepthMin, stereoLeftLfoDepthMax, stereoLeftLfoDepthDefault);
	auto stereoRightLfoDepth =
		std::make_unique<juce::AudioParameterFloat>(paramStereoRightLfoDepth, stereoRightLfoDepthName, stereoRightLfoDepthMin, stereoRightLfoDepthMax, stereoRightLfoDepthDefault);
	auto pannerLfoEnabled = std::make_unique<juce::AudioParameterBool>(paramPannerLfoEnabled, pannerLfoEnabledName, pannerLfoEnabledDefault);

	// EQ Parameters
	auto eqBand0Frequency =
		std::make_unique<juce::AudioParameterFloat>(paramEqBand0Frequency, eqBand0FrequencyName, eqBand0FrequencyMin, eqBand0FrequencyMax, eqBand0FrequencyDefault);
	auto eqBand0Gain	= std::make_unique<juce::AudioParameterFloat>(paramEqBand0Gain, eqBand0GainName, eqBandGainMin, eqBandGainMax, eqBandGainDefault);
	auto eqBand0Q		= std::make_unique<juce::AudioParameterFloat>(paramEqBand0Q, eqBand0QName, eqBandQMin, eqBandQMax, eqBandQDefault);
	auto eqBand0Enabled = std::make_unique<juce::AudioParameterBool>(paramEqBand0Enabled, eqBand0EnabledName, eqBandEnabledDefault);

	auto eqBand1Frequency =
		std::make_unique<juce::AudioParameterFloat>(paramEqBand1Frequency, eqBand1FrequencyName, eqBand1FrequencyMin, eqBand1FrequencyMax, eqBand1FrequencyDefault);
	auto eqBand1Gain	= std::make_unique<juce::AudioParameterFloat>(paramEqBand1Gain, eqBand1GainName, eqBandGainMin, eqBandGainMax, eqBandGainDefault);
	auto eqBand1Q		= std::make_unique<juce::AudioParameterFloat>(paramEqBand1Q, eqBand1QName, eqBandQMin, eqBandQMax, eqBandQDefault);
	auto eqBand1Enabled = std::make_unique<juce::AudioParameterBool>(paramEqBand1Enabled, eqBand1EnabledName, eqBandEnabledDefault);

	auto eqBand2Frequency =
		std::make_unique<juce::AudioParameterFloat>(paramEqBand2Frequency, eqBand2FrequencyName, eqBand2FrequencyMin, eqBand2FrequencyMax, eqBand2FrequencyDefault);
	auto eqBand2Gain	= std::make_unique<juce::AudioParameterFloat>(paramEqBand2Gain, eqBand2GainName, eqBandGainMin, eqBandGainMax, eqBandGainDefault);
	auto eqBand2Q		= std::make_unique<juce::AudioParameterFloat>(paramEqBand2Q, eqBand2QName, eqBandQMin, eqBandQMax, eqBandQDefault);
	auto eqBand2Enabled = std::make_unique<juce::AudioParameterBool>(paramEqBand2Enabled, eqBand2EnabledName, eqBandEnabledDefault);

	auto eqBand3Frequency =
		std::make_unique<juce::AudioParameterFloat>(paramEqBand3Frequency, eqBand3FrequencyName, eqBand3FrequencyMin, eqBand3FrequencyMax, eqBand3FrequencyDefault);
	auto eqBand3Gain	= std::make_unique<juce::AudioParameterFloat>(paramEqBand3Gain, eqBand3GainName, eqBandGainMin, eqBandGainMax, eqBandGainDefault);
	auto eqBand3Q		= std::make_unique<juce::AudioParameterFloat>(paramEqBand3Q, eqBand3QName, eqBandQMin, eqBandQMax, eqBandQDefault);
	auto eqBand3Enabled = std::make_unique<juce::AudioParameterBool>(paramEqBand3Enabled, eqBand3EnabledName, eqBandEnabledDefault);


	// Add all parameters to the parameter list
	params.push_back(std::move(input));
	params.push_back(std::move(output));
	params.push_back(std::move(drive));
	params.push_back(std::move(blendDistortion));
	params.push_back(std::move(distModel));
	params.push_back(std::move(blendDelay));
	params.push_back(std::move(delayTimeLeft));
	params.push_back(std::move(delayTimeRight));
	params.push_back(std::move(delayFeedback));
	params.push_back(std::move(delayModel));
	params.push_back(std::move(monoPanValue));
	params.push_back(std::move(stereoLeftPanValue));
	params.push_back(std::move(stereoRightPanValue));
	params.push_back(std::move(monoLfoFreq));
	params.push_back(std::move(stereoLeftLfoFreq));
	params.push_back(std::move(stereoRightLfoFreq));
	params.push_back(std::move(monoLfoDepth));
	params.push_back(std::move(stereoLeftLfoDepth));
	params.push_back(std::move(stereoRightLfoDepth));
	params.push_back(std::move(pannerLfoEnabled));
	params.push_back(std::move(eqBand0Frequency));
	params.push_back(std::move(eqBand0Gain));
	params.push_back(std::move(eqBand0Q));
	params.push_back(std::move(eqBand0Enabled));
	params.push_back(std::move(eqBand1Frequency));
	params.push_back(std::move(eqBand1Gain));
	params.push_back(std::move(eqBand1Q));
	params.push_back(std::move(eqBand1Enabled));
	params.push_back(std::move(eqBand2Frequency));
	params.push_back(std::move(eqBand2Gain));
	params.push_back(std::move(eqBand2Q));
	params.push_back(std::move(eqBand2Enabled));
	params.push_back(std::move(eqBand3Frequency));
	params.push_back(std::move(eqBand3Gain));
	params.push_back(std::move(eqBand3Q));
	params.push_back(std::move(eqBand3Enabled));

	return {params.begin(), params.end()};
}


void PluginProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
	juce::ignoreUnused(parameterID, newValue);
	updateParameters();
}


juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new PluginProcessor();
}
