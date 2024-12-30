/*
  ==============================================================================

	Module			Distortion
	Description		Handler for multiple distortion effect types : Saturation, Hard & Soft Clipping

  ==============================================================================
*/

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

	void		   setDrive(float newDrive);
	void		   setMix(float newMix);
	void		   setOutput(float newOutput);

	DistortionType getCurrentDistortionType() const;
	void		   setCurrentDistortionType(const DistortionType newType);


private:
	SampleType							  processSoftClipping(SampleType inputSample);

	SampleType							  processHardClipping(SampleType inputSample);

	SampleType							  processSaturation(SampleType inputSample);


	juce::dsp::LinkwitzRileyFilter<float> mDCFilter;

	juce::SmoothedValue<float>			  mDrive;
	juce::SmoothedValue<float>			  mMix;
	juce::SmoothedValue<float>			  mOutput;

	std::atomic<DistortionType>			  mDistortionType;

	float								  mSampleRate			  = 0;

	const float						  mSoftClipperCoefficient = (2.0f / juce::MathConstants<float>::pi);
};
