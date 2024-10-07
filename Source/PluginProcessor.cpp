
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
	  mValueTreeState(*this, nullptr, "PATERMERS", createParameterLayout())
#endif
{
	mValueTreeState.addParameterListener(paramInput, this);
}


PluginProcessor::~PluginProcessor()
{
	mValueTreeState.removeParameterListener(paramInput, this);
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


const juce::String PluginProcessor::getProgramName(int index)
{
	return {};
}


void PluginProcessor::changeProgramName(int index, const String &newName)
{
}


void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}


void PluginProcessor::releaseResources()
{
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
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
	ScopedNoDenormals noDenormals;
	auto			  totalNumInputChannels	 = getTotalNumInputChannels();
	auto			  totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto *channelData = buffer.getWritePointer(channel);

		// ..do something to the data...
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
	auto											   input = std::make_unique<AudioParameterFloat>(paramInput, inputGainName, inputMinValue, inputMaxValue, inputDefaultValue);

	params.push_back(std::move(input));

	return {params.begin(), params.end()};
}


void PluginProcessor::parameterChanged(const String &parameterID, float newValue)
{
}


AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new PluginProcessor();
}
