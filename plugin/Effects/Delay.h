/*
  ==============================================================================

	Module			Delay
	Description		Delay effect module

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "CircularBuffer.h"


class Delay
{
public:
	Delay();

	void prepare(juce::dsp::ProcessSpec &spec, float maxDelayInMS);


	void process(juce::AudioBuffer<float> &buffer);


private:
	juce::SmoothedValue<float> mDelayTimeMS			 = 500;	 // dummy parameters for now
	juce::SmoothedValue<float> mFeedback			 = 0.3f; // dummy parameters for now
	juce::SmoothedValue<float> mMix					 = 0.5f; // dummy parameters for now

	int						   mDelayInSamples		 = 0;	 // how many samples the read pointer will be offset (delayTime in Seconds * sampleRate)



	int						   mWritePosition		 = 0;
	int						   mCircularBufferLength = 0;

	double					   mSampleRate			 = 48000;
	int						   mNumChannels			 = 0;
	int						   mMaxBlockSize		 = 0;

	CircularBuffer			   mDelayBuffer;
};