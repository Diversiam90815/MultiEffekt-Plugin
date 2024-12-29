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
}


const juce::String PluginProcessor::getName() const
{
	return JucePlugin_Name;
}


bool PluginProcessor::acceptsMidi() const
{
	return false;
}


bool PluginProcessor::producesMidi() const
{
	return false;
}


bool PluginProcessor::isMidiEffect() const
{
	return false;
}


double PluginProcessor::getTailLengthSeconds() const
{
	return 0.0;
}


int PluginProcessor::getNumPrograms()
{
	return 1;
}


int PluginProcessor::getCurrentProgram()
{
	return 0;
}


void PluginProcessor::setCurrentProgram(int index)
{
	juce::ignoreUnused(index);
}


const juce::String PluginProcessor::getProgramName(int index)
{
	juce::ignoreUnused(index);
	return {};
}


void PluginProcessor::changeProgramName(int index, const juce::String &newName)
{
	juce::ignoreUnused(index, newName);
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

	mPanner.setPannerMode(mNumInputChannels);
	mPanner.prepare(spec);

	updateParameters();
}


void PluginProcessor::releaseResources()
{
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

	// Processing the distortion
	juce::dsp::AudioBlock<float> block{buffer};
	mDistortionModule.process(juce::dsp::ProcessContextReplacing<float>(block));

	mDelayModule.process(buffer);

	mPanner.process(buffer);

	// Apply output gain
	float outputLevel = mOutput.getNextValue();
	buffer.applyGain(juce::Decibels::decibelsToGain(outputLevel));
}


bool PluginProcessor::hasEditor() const
{
	return true;
}


juce::AudioProcessorEditor *PluginProcessor::createEditor()
{
	// We create a generic audio processor editor here, so we can work with the processing
	// without concerning about the UI at first!

	return new juce::GenericAudioProcessorEditor(*this);
}


void PluginProcessor::getStateInformation(juce::MemoryBlock &destData)
{
	juce::ignoreUnused(destData);
}


void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
	juce::ignoreUnused(data, sizeInBytes);
}


void PluginProcessor::updateParameters()
{
	updateGainParameter();

	updateDistortionParameter();

	updateDelayParameter();

	updatePannerParameter();
}


void PluginProcessor::updateGainParameter()
{
	setInput(mValueTreeState.getRawParameterValue(paramInput)->load());
	setOutput(mValueTreeState.getRawParameterValue(paramOutput)->load());
}


void PluginProcessor::updateDelayParameter()
{
	mDelayModule.setMix(mValueTreeState.getRawParameterValue(paramMixDelay)->load());
	mDelayModule.setChannelDelayTime(0, mValueTreeState.getRawParameterValue(paramDelayTimeLeft)->load());
	mDelayModule.setChannelDelayTime(1, mValueTreeState.getRawParameterValue(paramDelayTimeRight)->load());
	mDelayModule.setFeedback(mValueTreeState.getRawParameterValue(paramDelayFeedback)->load());

	auto delayMode = static_cast<int>(mValueTreeState.getRawParameterValue(paramDelayModel)->load());
	switch (delayMode)
	{
	case 0:
	{
		mDelayModule.setDelayType(DelayType::SingleTap);
		break;
	}
	case 1:
	{
		mDelayModule.setDelayType(DelayType::PingPong);
		break;
	}
	default: break;
	}
}


void PluginProcessor::updateDistortionParameter()
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


void PluginProcessor::updatePannerParameter()
{
	mPanner.enableLFO(mValueTreeState.getRawParameterValue(paramPannerLfoEnabled)->load());

	if (mNumInputChannels == 1) // Mono
	{
		mPanner.processMonoPanner(mValueTreeState.getRawParameterValue(paramMonoPanValue)->load(), mValueTreeState.getRawParameterValue(paramMonoLfoFreq)->load(),
								  mValueTreeState.getRawParameterValue(paramMonoLfoDepth)->load());
	}
	else // Stereo
	{
		mPanner.processStereoPanner(mValueTreeState.getRawParameterValue(paramStereoLeftPanValue)->load(), mValueTreeState.getRawParameterValue(paramStereoRightPanValue)->load(),
									mValueTreeState.getRawParameterValue(paramStereoLeftLfoFreq)->load(), mValueTreeState.getRawParameterValue(paramStereoRightLfoFreq)->load(),
									mValueTreeState.getRawParameterValue(paramStereoLeftLfoDepth)->load(), mValueTreeState.getRawParameterValue(paramStereoRightLfoDepth)->load());
	}
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

	return {params.begin(), params.end()};
}


void PluginProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
	updateParameters();
}


juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new PluginProcessor();
}
