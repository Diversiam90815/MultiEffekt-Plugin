/*
  ==============================================================================

	Module			Distortion
	Description		Handler for multiple distortion effect types : Saturation, Hard & Soft Clipping

  ==============================================================================
*/

#pragma once

#include "EffectBase.h"
#include "Parameters.h"

template <typename SampleType>
class Distortion : public EffectBase<SampleType>
{
public:
	Distortion();
	~Distortion() = default;

	void		   prepare(const juce::dsp::ProcessSpec &spec) override;
	void		   process(juce::AudioBuffer<SampleType> &buffer) override;
	void		   reset() override;
	EffectType	   getEffectType() const override { return EffectType::Distortion; }

	SampleType	   processSample(SampleType input) noexcept;

	void		   setParameter(const std::string &name, float value) override;
	float		   getParameter(const std::string &name) const override;

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

	const float							  mSoftClipperCoefficient = (2.0f / juce::MathConstants<float>::pi);
};
