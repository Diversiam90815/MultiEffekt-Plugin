/*
  ==============================================================================

	Module			PannerBase
	Description		Base class for the panner

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>


template <typename SampleType>
class PannerBase
{
public:
	PannerBase()												= default;
	~PannerBase()												= default;

	virtual void prepare(const juce::dsp::ProcessSpec &spec)	= 0;
	virtual void process(juce::AudioBuffer<SampleType> &buffer) = 0;
	virtual void reset()										= 0;

	void		 enableLFO(bool enabled) { mLfoEnabled.store(enabled); }

protected:
	double getSampleRate() const { return mSampleRate; }

	void   setSampleRate(double rate) { mSampleRate = rate; }

	bool   getLfoEnabled() { return mLfoEnabled.load(); }

private:
	double			  mSampleRate{0};

	std::atomic<bool> mLfoEnabled;
};

template class PannerBase<float>;
template class PannerBase<double>;
