/*
  ==============================================================================

	Module			Panner
	Description		Panner effect module

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>


template <typename SampleType>
class Panner
{
public:
	Panner();
	~Panner() = default;

	void prepare(const juce::dsp::ProcessSpec &spec);

	// Resets any internal states (LFO phase, etc.)
	void reset();

	void process(juce::AudioBuffer<SampleType> &buffer);

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

	double							  mSampleRate = 0;
};
