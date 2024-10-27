
#pragma once

#include <juce_dsp/juce_dsp.h>
#include "Parameters.h"


template <typename SampleType>
class Distortion
{
public:
	Distortion();

	void prepare(juce::dsp::ProcessSpec &spec);

	void reset();

	template <typename ProcessContext>
	void		   process(const ProcessContext &context) noexcept;

	SampleType	   processSample(SampleType input) noexcept;

	void		   setDrive(SampleType newDrive);
	void		   setMix(SampleType newMix);
	void		   setOutput(SampleType newOutput);

	DistortionType getCurrentDistortionType() const;
	void		   setCurrentDistortionType(const DistortionType newType);


private:
	SampleType					processSoftClipping(SampleType inputSample);

	SampleType					processHardClipping(SampleType inputSample);

	SampleType					processSaturation(SampleType inputSample);


	juce::dsp::LinkwitzRileyFilter<float> mDCFilter;

	juce::SmoothedValue<float>	mDrive;
	juce::SmoothedValue<float>	mMix;
	juce::SmoothedValue<float>	mOutput;

	std::atomic<DistortionType> mDistortionType;

	float						mSampleRate = 0;
};
