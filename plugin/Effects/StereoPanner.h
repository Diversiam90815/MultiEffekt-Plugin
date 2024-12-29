/*
  ==============================================================================

	Module			StereoPanner
	Description		Panner effect module handling stereo input signals

  ==============================================================================
*/

#pragma once

#include "PannerBase.h"

template <typename SampleType>
class StereoPanner : public PannerBase<SampleType>
{
public:
	StereoPanner();
	~StereoPanner() = default;

	void prepare(const juce::dsp::ProcessSpec &spec) override;
	void reset() override;

	void process(juce::AudioBuffer<SampleType> &buffer) override;

	// --- Set parameters for left channel
	void setLeftChannelPan(float newPan);
	void setLeftChannelLfoRate(float newFrequency);
	void setLeftChannelLfoDepth(float newDepth);

	// --- Set parameters for right channel
	void setRightChannelPan(float newPan);
	void setRightChannelLfoRate(float newFrequency);
	void setRightChannelLfoDepth(float newDepth);


private:
	juce::SmoothedValue<float>		  mLeftChannelPan;
	juce::SmoothedValue<float>		  mRightChannelPan;

	juce::SmoothedValue<float>		  mLeftChannelLfoFrequency;
	juce::SmoothedValue<float>		  mRightChannelLfoFrequency;

	juce::SmoothedValue<float>		  mLeftChannelLfoDepth;
	juce::SmoothedValue<float>		  mRightChannelLfoDepth;

	juce::dsp::Oscillator<SampleType> mLeftChannelLFO;
	juce::dsp::Oscillator<SampleType> mRightChannelLFO;
};
