
#pragma once
#include "Parameters.h"
#include "juce_audio_basics/juce_audio_basics.h"


class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	void prepare(double sampleRate, int numSamples, int numChannels);

	void copyFromBufferToCircularBuffer(juce::AudioBuffer<float> &buffer);

	juce::AudioBuffer<float> getBuffer();

private:
	juce::AudioBuffer<float> mCircularBuffer;

	int						 mNumChannels{0};			 // Set in prepare()
	int						 mWritePosition{0};
	int						 mSizeOfBufferInSeconds = 2; // Buffer will be size of 2s of audio samples
};
