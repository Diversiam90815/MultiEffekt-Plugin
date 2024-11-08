
#pragma once
#include "Parameters.h"
#include "juce_audio_basics/juce_audio_basics.h"


class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	void prepare(double sampleRate, int numSamples);
	
	void process();

	void processSample();

private:
	juce::AudioBuffer<float> circularBuffer;
};
