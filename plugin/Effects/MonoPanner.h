/*
  ==============================================================================

	Module			MonoPanner
	Description		Panner effect module handling mono input signals

  ==============================================================================
*/

#pragma once

#include "PannerBase.h"


template <typename SampleType>
class MonoPanner : public PannerBase<SampleType>
{
public:
	MonoPanner();
	~MonoPanner() = default;

	void prepare(const juce::dsp::ProcessSpec &spec) override;

	void reset() override;

	void process(juce::AudioBuffer<SampleType> &buffer) override;

	void setPan(float newPan);

	void setLfoRate(float newFrequency);

	void setLfoDepth(float newDepth);

private:
	juce::SmoothedValue<float>		  mPan;

	juce::SmoothedValue<float>		  mLfoFrequency;

	juce::SmoothedValue<float>		  mLfoDepth;

	juce::dsp::Oscillator<SampleType> mLFO;
};
