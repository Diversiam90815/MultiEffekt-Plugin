/*
  ==============================================================================

	Module			PannerManager
	Description		Managing multiple panner modules depending on type

  ==============================================================================
*/

#pragma once

#include "MonoPanner.h"
#include "StereoPanner.h"
#include "Parameters.h"
#include "EffectBase.h"


template <typename SampleType>
class PannerManager : public EffectBase<SampleType>
{
public:
	PannerManager()	 = default;
	~PannerManager() = default;

	void	   prepare(const juce::dsp::ProcessSpec &spec) override;
	void	   process(juce::AudioBuffer<SampleType> &buffer) override;
	void	   reset() override;
	EffectType getEffectType() const override { return EffectType::Panner; }

	void	   setParameter(const std::string &name, float value) override;
	float	   getParameter(const std::string &name) const override;

	void	   setPannerMode(int numInputChannels);

	void	   enableLFO(bool enabled);


private:
	void					 processMonoPanner(float pan, float lfoFreq, float lfoDepth);
	void					 processStereoPanner(float leftPan, float rightPan, float leftLfoFreq, float rightLfoFreq, float leftLfoDepth, float rightLfoDepth);


	PannerType				 mPannerMode{PannerType::Mono};

	int						 mNumInputChannels{0};

	MonoPanner<SampleType>	 mMonoPanner;

	StereoPanner<SampleType> mStereoPanner;
};


