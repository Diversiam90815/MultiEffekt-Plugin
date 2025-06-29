/*
  ==============================================================================

	Module			Delay
	Description		Delay effect module

  ==============================================================================
*/

#pragma once

#include "EffectBase.h"
#include "CircularBuffer.h"
#include "Parameters.h"


template <typename SampleType>
class Delay : public EffectBase<SampleType>
{
public:
	Delay();
	~Delay() = default;

	void	   prepare(const juce::dsp::ProcessSpec &spec) override;
	void	   prepare(const juce::dsp::ProcessSpec &spec, float maxDelayInMS);
	void	   process(juce::AudioBuffer<SampleType> &buffer) override;
	void	   reset() override;
	EffectType getEffectType() const override { return EffectType::Delay; }

	void	   setParameter(const std::string &name, float value) override;
	float	   getParameter(const std::string &name) const override;

	void	   prepareDelayBuffer();

	void	   setMix(float newValue);
	void	   setFeedback(float newValue);

	DelayType  getDelayType() const;
	void	   setDelayType(DelayType type);

	void	   setChannelDelayTime(int channel, float timeInMS);

private:
	juce::SmoothedValue<float>				mFeedback;
	juce::SmoothedValue<float>				mMix;

	std::vector<juce::SmoothedValue<float>> mChannelDelayTimes; // Using different delay times for each channel

	int										mCircularBufferLength{0};

	std::vector<int>						mWritePositions;

	float									mMaxDelayInMS{0.0f};

	DelayType								mDelayType{DelayType::SingleTap};

	CircularBuffer<SampleType>				mDelayBuffer;
};
