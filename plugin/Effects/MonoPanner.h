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

	// Resets any internal states (LFO phase, etc.)
	void reset() override;

	void process(juce::AudioBuffer<SampleType> &buffer) override;

	// Sets the static (base) pan value. Range typically -1.0 = hard left, 1.0 = hard right, 0.0 = center.
	void setPan(float newPan);

	// Sets the LFO rate in Hz.
	void setLfoRate(float newFrequency);

	// Sets the LFO depth. 0.0 = no modulation, 1.0 = full range.
	void setLfoDepth(float newDepth);

private:
	juce::SmoothedValue<float>		  mPan;

	juce::SmoothedValue<float>		  mLfoFrequency;

	juce::SmoothedValue<float>		  mLfoDepth;

	juce::dsp::Oscillator<SampleType> mLFO;
};
