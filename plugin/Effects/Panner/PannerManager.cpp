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
	setPannerMode(spec.numChannels);

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
void PannerManager<SampleType>::setParameter(const std::string &name, float value)
{
	if (mPannerMode == PannerType::Mono)
	{
		if (name == paramMonoPanValue)
			mMonoPanner.setPan(value);
		else if (name == paramMonoLfoFreq)
			mMonoPanner.setLfoRate(value);
		else if (name == paramMonoLfoDepth)
			mMonoPanner.setLfoDepth(value);
		else if (name == paramPannerLfoEnabled)
			enableLFO(value > 0.5f);
	}
	else if (mPannerMode == PannerType::Stereo)
	{
		if (name == paramStereoLeftPanValue)
			mStereoPanner.setLeftChannelPan(value);
		else if (name == paramStereoRightPanValue)
			mStereoPanner.setRightChannelPan(value);
		else if (name == paramStereoLeftLfoFreq)
			mStereoPanner.setLeftChannelLfoRate(value);
		else if (name == paramStereoRightLfoFreq)
			mStereoPanner.setRightChannelLfoRate(value);
		else if (name == paramStereoLeftLfoDepth)
			mStereoPanner.setLeftChannelLfoDepth(value);
		else if (name == paramStereoRightLfoDepth)
			mStereoPanner.setRightChannelLfoDepth(value);
		else if (name == paramPannerLfoEnabled)
			enableLFO(value > 0.5f);
	}
}


template <typename SampleType>
float PannerManager<SampleType>::getParameter(const std::string &name) const
{
	if (mPannerMode == PannerType::Mono)
	{
		if (name == "pan")
			return mMonoPanner.getPan();
		else if (name == "lfoFreq")
			return mMonoPanner.getLfoRate();
		else if (name == "lfoDepth")
			return mMonoPanner.getLfoDepth();
	}
	else if (mPannerMode == PannerType::Stereo)
	{
		if (name == "leftPan")
			return mStereoPanner.getLeftChannelPan();
		else if (name == "rightPan")
			return mStereoPanner.getRightChannelPan();
		else if (name == "leftLfoFreq")
			return mStereoPanner.getLeftChannelLfoRate();
		else if (name == "rightLfoFreq")
			return mStereoPanner.getRightChannelLfoRate();
		else if (name == "leftLfoDepth")
			return mStereoPanner.getLeftChannelLfoDepth();
		else if (name == "rightLfoDepth")
			return mStereoPanner.getRightChannelLfoDepth();
	}

	return 0.0f;
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
