
#include "PluginProcessor.h"
#include "PluginEditor.h"


PluginProcessor::PluginProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
						 .withInput("Input", AudioChannelSet::stereo(), true)
#endif
						 .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
						 ),
	  mValueTreeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
	mValueTreeState.addParameterListener(paramInput, this);
	mValueTreeState.addParameterListener(paramOutput, this);
	mValueTreeState.addParameterListener(paramDrive, this);
	mValueTreeState.addParameterListener(paramBlend, this);
}


PluginProcessor::~PluginProcessor()
{
	mValueTreeState.removeParameterListener(paramInput, this);
	mValueTreeState.removeParameterListener(paramOutput, this);
	mValueTreeState.removeParameterListener(paramDrive, this);
	mValueTreeState.removeParameterListener(paramBlend, this);
}


const String PluginProcessor::getName() const
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


const String PluginProcessor::getProgramName(int index)
{
	return {};
}


void PluginProcessor::changeProgramName(int index, const String &newName)
{
}


void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Set the initial values of the parameters
	input  = Decibels::decibelsToGain(mValueTreeState.getRawParameterValue(paramInput)->load());
	drive  = Decibels::decibelsToGain(mValueTreeState.getRawParameterValue(paramDrive)->load());
	output = Decibels::decibelsToGain(mValueTreeState.getRawParameterValue(paramOutput)->load());
	blend  = jmap(mValueTreeState.getRawParameterValue(paramBlend)->load(), 0.0f, 100.0f, 0.0f, 1.0f);
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
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif


void PluginProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
	ignoreUnused(midiMessages);

	ScopedNoDenormals noDenormals;
	auto			  totalNumInputChannels	 = getTotalNumInputChannels();
	auto			  totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto *channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			// Store clean sample for later blend
			float cleanSignal = channelData[sample];

			// Apply input gain
			channelData[sample] *= input;

			// Apply hyperbolic tangent to simulate natural saturation at high gain
			channelData[sample]	  = std::tanh(drive * channelData[sample]);

			// Apply distortion (arctangent function)
			float distortedSignal = (2.0f / MathConstants<float>::pi) * atan(channelData[sample]);

			// Blend between distorted and clean signal
			channelData[sample]	  = (blend * distortedSignal + (1.0f - blend) * cleanSignal) * output;
		}
	}
}


bool PluginProcessor::hasEditor() const
{
	return true;
}


AudioProcessorEditor *PluginProcessor::createEditor()
{
	// We create a generic audio processor editor here, so we can work with the processing
	// without concerning about the UI at first!

	return new GenericAudioProcessorEditor(*this);
}


void PluginProcessor::getStateInformation(MemoryBlock &destData)
{
}


void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
}


AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<RangedAudioParameter>> params;

	// add parameters here
	auto											   input  = std::make_unique<AudioParameterFloat>(paramInput, inputGainName, inputMinValue, inputMaxValue, inputDefaultValue);
	auto											   output = std::make_unique<AudioParameterFloat>(paramOutput, outputName, outputMinValue, outputMaxValue, outputDefaultValue);
	auto											   drive  = std::make_unique<AudioParameterFloat>(paramDrive, driveName, driveMinValue, driveMaxValue, driveDefaultValue);
	auto											   blend  = std::make_unique<AudioParameterFloat>(paramBlend, blendName, blendMinValue, blendMaxValue, blendDefaultValue);

	params.push_back(std::move(input));
	params.push_back(std::move(output));
	params.push_back(std::move(drive));
	params.push_back(std::move(blend));

	return {params.begin(), params.end()};
}


void PluginProcessor::parameterChanged(const String &parameterID, float newValue)
{
	if (parameterID == paramInput)
	{
		input = Decibels::decibelsToGain(mValueTreeState.getRawParameterValue(paramInput)->load());
	}

	else if (parameterID == paramDrive)
	{
		drive = Decibels::decibelsToGain(mValueTreeState.getRawParameterValue(paramDrive)->load());
	}

	else if (parameterID == paramOutput)
	{
		output = Decibels::decibelsToGain(mValueTreeState.getRawParameterValue(paramOutput)->load());
	}

	else if (parameterID == paramBlend)
	{
		blend = jmap(mValueTreeState.getRawParameterValue(paramBlend)->load(), 0.0f, 100.0f, 0.0f, 1.0f);
	}
}


AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new PluginProcessor();
}
