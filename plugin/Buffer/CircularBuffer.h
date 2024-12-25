
#pragma once
#include "Parameters.h"
#include "juce_audio_basics/juce_audio_basics.h"


class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	void					 prepare(double sampleRate, int numSamples, int numChannels, int bufferLengthInSeconds);

	void					 copyFromBufferToCircularBuffer(juce::AudioBuffer<float> &buffer);

	juce::AudioBuffer<float> getBuffer();

private:
	juce::AudioBuffer<float> mCircularBuffer;

	int						 mNumChannels{0};			 // Set in prepare()
	int						 mWritePosition{0};
	int						 mSizeOfBufferInSeconds = 2; // number of seconds the buffer will be in size of
};
