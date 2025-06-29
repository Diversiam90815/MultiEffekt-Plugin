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


template <typename SampleType>
class PannerManager
{
public:
	PannerManager()	 = default;
	~PannerManager() = default;

	void setPannerMode(int numInputChannels);

	void prepare(const juce::dsp::ProcessSpec &spec);

	void process(juce::AudioBuffer<SampleType> &buffer);

	void reset();

	void enableLFO(bool enabled);

	void processMonoPanner(float pan, float lfoFreq, float lfoDepth);

	void processStereoPanner(float leftPan, float rightPan, float leftLfoFreq, float rightLfoFreq, float leftLfoDepth, float rightLfoDepth);


private:
	PannerType				 mPannerMode{PannerType::Mono};

	int						 mNumInputChannels{0};

	MonoPanner<SampleType>	 mMonoPanner;

	StereoPanner<SampleType> mStereoPanner;
};
