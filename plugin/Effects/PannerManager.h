
#pragma once
#include "MonoPanner.h"
#include "StereoPanner.h"

enum PannerMode
{
	Mono = 1,
	Stereo
};


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


private:
	PannerMode				 mPannerMode;

	int						 mNumInputChannels = 0;

	MonoPanner<SampleType>	 mMonoPanner;

	StereoPanner<SampleType> mStereoPanner;
};
