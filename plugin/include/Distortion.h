
#pragma once

#include <juce_dsp/juce_dsp.h>


template <typename SampleType>
class Distortion
{
public:
	Distortion();

	void prepare(juce::dsp::ProcessSpec &spec);

	void reset();

	template <typename ProcessContext>
	void process(const ProcessContext &context) noexcept
	{
	}

	void processSample(SampleType input) noexcept
	{
	}

private:

	float mSampleRate;
};
