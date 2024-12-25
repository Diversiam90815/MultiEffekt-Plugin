/*
  ==============================================================================

	Module			MainPluginProcessor
	Description		Main processor of the plugin

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


PluginProcessor::PluginProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
						 .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
						 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
						 ),
	  mValueTreeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
	mValueTreeState.addParameterListener(paramInput, this);
	mValueTreeState.addParameterListener(paramOutput, this);
	mValueTreeState.addParameterListener(paramDrive, this);
	mValueTreeState.addParameterListener(paramBlendDist, this);
	mValueTreeState.addParameterListener(paramDistModel, this);
	mValueTreeState.addParameterListener(paramBlendDelay, this);
	mValueTreeState.addParameterListener(paramDelayTime, this);
	mValueTreeState.addParameterListener(paramDelayFeedback, this);
}


PluginProcessor::~PluginProcessor()
{
	mValueTreeState.removeParameterListener(paramInput, this);
	mValueTreeState.removeParameterListener(paramOutput, this);
	mValueTreeState.removeParameterListener(paramDrive, this);
	mValueTreeState.removeParameterListener(paramBlendDist, this);
	mValueTreeState.removeParameterListener(paramDistModel, this);
	mValueTreeState.removeParameterListener(paramBlendDelay, this);
	mValueTreeState.removeParameterListener(paramDelayTime, this);
	mValueTreeState.removeParameterListener(paramDelayFeedback, this);
}


const juce::String PluginProcessor::getName() const
{
	return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}


bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}


bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
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
}


const juce::String PluginProcessor::getProgramName(int index)
{
	return {};
}


void PluginProcessor::changeProgramName(int index, const juce::String &newName)
{
}


void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Initialize spec for DSP modules
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate		  = sampleRate;
	spec.numChannels	  = getTotalNumInputChannels();

	mDistortionModule.prepare(spec);
	mDelayModule.prepare(spec, 2000);

	updateParameters();
}


void PluginProcessor::releaseResources()
{
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif


void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	juce::ignoreUnused(midiMessages);

	juce::ScopedNoDenormals noDenormals;
	auto					totalNumInputChannels  = getTotalNumInputChannels();
	auto					totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// Processing the distortion
	//juce::dsp::AudioBlock<float> block{buffer};
	//mDistortionModule.process(juce::dsp::ProcessContextReplacing<float>(block));

	mDelayModule.process(buffer);
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
}


void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
}


void PluginProcessor::updateParameters()
{
	mDistortionModule.setDrive(mValueTreeState.getRawParameterValue(paramDrive)->load());
	mDistortionModule.setOutput(mValueTreeState.getRawParameterValue(paramOutput)->load());
	mDistortionModule.setMix(mValueTreeState.getRawParameterValue(paramBlendDist)->load());

	mDelayModule.setMix(mValueTreeState.getRawParameterValue(paramBlendDelay)->load());
	mDelayModule.setDelayTime(mValueTreeState.getRawParameterValue(paramDelayTime)->load());
	mDelayModule.setFeedback(mValueTreeState.getRawParameterValue(paramDelayFeedback)->load());

	auto model = static_cast<int>(mValueTreeState.getRawParameterValue(paramDistModel)->load());
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


juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

	// add parameters here
	auto input			 = std::make_unique<juce::AudioParameterFloat>(paramInput, inputGainName, inputMinValue, inputMaxValue, inputDefaultValue);
	auto output			 = std::make_unique<juce::AudioParameterFloat>(paramOutput, outputName, outputMinValue, outputMaxValue, outputDefaultValue);

	// Distortion
	auto drive			 = std::make_unique<juce::AudioParameterFloat>(paramDrive, driveName, driveMinValue, driveMaxValue, driveDefaultValue);
	auto blendDistortion = std::make_unique<juce::AudioParameterFloat>(paramBlendDist, blendNameDistortion, blendMinValue, blendMaxValue, blendDefaultValue);
	auto distModel		 = std::make_unique<juce::AudioParameterChoice>(paramDistModel, distModelName, distModelsArray, 0);

	// Delay
	auto blendDelay		 = std::make_unique<juce::AudioParameterFloat>(paramBlendDelay, blendNameDelay, blendMinValue, blendMaxValue, blendDefaultValue);
	auto delayTime		 = std::make_unique<juce::AudioParameterFloat>(paramDelayTime, delayTimeName, delayTimeMinValue, delayTimeMaxValue, delayTimeDefaultValue);
	auto delayFeedback =
		std::make_unique<juce::AudioParameterFloat>(paramDelayFeedback, delayFeedbackName, delayFeedbackMinValue, delayFeedbackMaxValue, delayFeedbackDefaultValue);

	params.push_back(std::move(input));
	params.push_back(std::move(output));
	params.push_back(std::move(drive));
	params.push_back(std::move(blendDistortion));
	params.push_back(std::move(distModel));
	params.push_back(std::move(blendDelay));
	params.push_back(std::move(delayTime));
	params.push_back(std::move(delayFeedback));

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
