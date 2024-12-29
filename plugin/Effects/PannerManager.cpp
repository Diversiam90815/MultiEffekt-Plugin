
#include "PannerManager.h"


template <typename SampleType>
void PannerManager<SampleType>::setPannerMode(int numInputChannels)
{
	mNumInputChannels = numInputChannels;
	mPannerMode		  = (numInputChannels == 1) ? PannerMode::Mono : PannerMode::Stereo;
}


template <typename SampleType>
void PannerManager<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	if (mPannerMode == PannerMode::Mono)
		mMonoPanner.prepare(spec);
	else if (mPannerMode == PannerMode::Stereo)
		mStereoPanner.prepare(spec);
}


template <typename SampleType>
void PannerManager<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	if (mPannerMode == PannerMode::Mono)
		mMonoPanner.process(buffer);
	else if (mPannerMode == PannerMode::Stereo)
		mStereoPanner.process(buffer);
}


template <typename SampleType>
void PannerManager<SampleType>::reset()
{
	if (mPannerMode == PannerMode::Mono)
		mMonoPanner.reset();
	else if (mPannerMode == PannerMode::Stereo)
		mStereoPanner.reset();
}


template <typename SampleType>
void PannerManager<SampleType>::enableLFO(bool enabled)
{
	if (mPannerMode == PannerMode::Mono)
		mMonoPanner.enableLFO(enabled);
	else if (mPannerMode == PannerMode::Stereo)
		mStereoPanner.enableLFO(enabled);
}
