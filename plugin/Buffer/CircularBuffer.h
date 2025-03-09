/*
  ==============================================================================

	Module			CircularBuffer
	Description		Buffer handler for time based effects

  ==============================================================================
*/

#pragma once

#include "Parameters.h"
#include "juce_audio_basics/juce_audio_basics.h"


template <typename SampleType>
class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	void						  prepare(double sampleRate, int numSamples, int numChannels, int bufferLengthInSeconds);

	void						  copyFromBufferToCircularBuffer(juce::AudioBuffer<SampleType> &buffer);

	juce::AudioBuffer<SampleType>& getBuffer();

private:
	juce::AudioBuffer<SampleType> mCircularBuffer;

	int							  mNumChannels{0};			  // Set in prepare()

	int							  mWritePosition{0};

	int							  mSizeOfBufferInSeconds = 2; // number of seconds the buffer will be in size of
};
