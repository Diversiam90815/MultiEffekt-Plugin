/*
  ==============================================================================

	Module			Panner
	Description		Panner effect module

  ==============================================================================
*/

#include "Panner.h"


template <typename SampleType>
Panner<SampleType>::Panner()
{
	// Initialize the LFO with a sine wave
	mLFO.initialise([](SampleType x) { return std::sin(x); });
}


template <typename SampleType>
void Panner<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	mSampleRate = spec.sampleRate;
	mLFO.prepare(spec);
	reset();
}


template <typename SampleType>
void Panner<SampleType>::reset()
{
	mLFO.reset();
}


template <typename SampleType>
void Panner<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
}


template <typename SampleType>
void Panner<SampleType>::setPan(float newPan)
{
	mPan.setTargetValue(newPan);
}


template <typename SampleType>
void Panner<SampleType>::setLfoRate(float newFrequency)
{
	mLfoFrequency.setTargetValue(newFrequency);
}


template <typename SampleType>
void Panner<SampleType>::setLfoDepth(float newDepth)
{
	mLfoDepth.setTargetValue(newDepth);
}
