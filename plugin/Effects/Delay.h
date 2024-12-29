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
#include "Parameters.h"


template <typename SampleType>
class Delay
{
public:
	Delay();

	void	  prepare(juce::dsp::ProcessSpec &spec, float maxDelayInMS);

	void	  process(juce::AudioBuffer<SampleType> &buffer);

	void	  setMix(float newValue);
	void	  setFeedback(float newValue);

	DelayType getDelayType() const;
	void	  setDelayType(DelayType type);

	void	  setChannelDelayTime(int channel, float timeInMS);

private:
	juce::SmoothedValue<float>				mFeedback;
	juce::SmoothedValue<float>				mMix;

	std::vector<juce::SmoothedValue<float>> mChannelDelayTimes; // Using different delay times for each channel

	int										mCircularBufferLength = 0;

	std::vector<int>						mWritePositions;

	double									mSampleRate	  = 48000;
	int										mNumChannels  = 0;
	int										mMaxBlockSize = 0;

	DelayType								mDelayType;


	CircularBuffer<SampleType>				mDelayBuffer;
};
