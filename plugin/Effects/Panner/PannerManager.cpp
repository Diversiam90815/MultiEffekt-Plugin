/*
  ==============================================================================

	Module			PannerManager
	Description		Managing multiple panner modules depending on type

  ==============================================================================
*/

#include "PannerManager.h"


template <typename SampleType>
void PannerManager<SampleType>::setPannerMode(int numInputChannels)
{
	mNumInputChannels = numInputChannels;
	mPannerMode		  = (numInputChannels == 1) ? PannerType::Mono : PannerType::Stereo;
}


template <typename SampleType>
void PannerManager<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	if (mPannerMode == PannerType::Mono)
		mMonoPanner.prepare(spec);
	else if (mPannerMode == PannerType::Stereo)
		mStereoPanner.prepare(spec);
}


template <typename SampleType>
void PannerManager<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	if (mPannerMode == PannerType::Mono)
		mMonoPanner.process(buffer);
	else if (mPannerMode == PannerType::Stereo)
		mStereoPanner.process(buffer);
}


template <typename SampleType>
void PannerManager<SampleType>::reset()
{
	if (mPannerMode == PannerType::Mono)
		mMonoPanner.reset();
	else if (mPannerMode == PannerType::Stereo)
		mStereoPanner.reset();
}


template <typename SampleType>
void PannerManager<SampleType>::enableLFO(bool enabled)
{
	if (mPannerMode == PannerType::Mono)
		mMonoPanner.enableLFO(enabled);
	else if (mPannerMode == PannerType::Stereo)
		mStereoPanner.enableLFO(enabled);
}


template <typename SampleType>
void PannerManager<SampleType>::processMonoPanner(float pan, float lfoFreq, float lfoDepth)
{
	if (mPannerMode == PannerType::Mono)
	{
		mMonoPanner.setPan(pan);
		mMonoPanner.setLfoRate(lfoFreq);
		mMonoPanner.setLfoDepth(lfoDepth);
	}
}


template <typename SampleType>
void PannerManager<SampleType>::processStereoPanner(float leftPan, float rightPan, float leftLfoFreq, float rightLfoFreq, float leftLfoDepth, float rightLfoDepth)
{
	if (mPannerMode == PannerType::Stereo)
	{
		mStereoPanner.setLeftChannelPan(leftPan);
		mStereoPanner.setRightChannelPan(rightPan);
		mStereoPanner.setLeftChannelLfoRate(leftLfoFreq);
		mStereoPanner.setRightChannelLfoRate(rightLfoFreq);
		mStereoPanner.setLeftChannelLfoDepth(leftLfoDepth);
		mStereoPanner.setRightChannelLfoDepth(rightLfoDepth);
	}
}


// Explicit template instantiations
template class PannerManager<float>;
template class PannerManager<double>;
