/*
  ==============================================================================

	Module			Distortion
	Description		Handler for multiple distortion effect types : Saturation, Hard & Soft Clipping

  ==============================================================================
*/

#include "Distortion.h"

template <typename SampleType>
Distortion<SampleType>::Distortion()
{
}


template <typename SampleType>
void Distortion<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	// Store parameters using EffectBase methods
	this->setSampleRate(spec.sampleRate);
	this->setNumChannels(static_cast<int>(spec.numChannels));
	this->setMaxBlockSize(static_cast<int>(spec.maximumBlockSize));

	mDCFilter.prepare(spec);
	mDCFilter.setCutoffFrequency(10.0);
	mDCFilter.setType(juce::dsp::LinkwitzRileyFilter<float>::Type::highpass);

	reset();
}


template <typename SampleType>
void Distortion<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	if (this->isBypassed())
	{
		this->processBypassed(buffer);
		return;
	}

	const auto numChannels = buffer.getNumChannels();
	const auto numSamples  = buffer.getNumSamples();

	for (int channel = 0; channel < numChannels; ++channel)
	{
		auto *channelData = buffer.getWritePointer(channel);

		for (int i = 0; i < numSamples; ++i)
		{
			// Apply DC filter
			channelData[i] = mDCFilter.processSample(channel, channelData[i]);

			// Apply distortion
			channelData[i] = processSample(channelData[i]);
		}
	}
}


template <typename SampleType>
void Distortion<SampleType>::reset()
{
	if (this->getSampleRate() <= 0)
		return;

	mDrive.reset(this->getSampleRate(), 0.02);
	mDrive.setTargetValue(0.0f);

	mMix.reset(this->getSampleRate(), 0.02);
	mMix.setTargetValue(1.0f);

	mOutput.reset(this->getSampleRate(), 0.02);
	mOutput.setTargetValue(0.0f);

	mDCFilter.reset();
}


template <typename SampleType>
void Distortion<SampleType>::setDrive(float newDrive)
{
	mDrive.setTargetValue(newDrive);
}


template <typename SampleType>
void Distortion<SampleType>::setMix(float newMix)
{
	mMix.setTargetValue(newMix);
}


template <typename SampleType>
void Distortion<SampleType>::setOutput(float newOutput)
{
	mOutput.setTargetValue(newOutput);
}


template <typename SampleType>
SampleType Distortion<SampleType>::processSample(SampleType input) noexcept
{
	switch (getCurrentDistortionType())
	{
	case DistortionType::hardClipping:
	{
		return processHardClipping(input);
		break;
	}

	case DistortionType::softClipping:
	{
		return processSoftClipping(input);
		break;
	}

	case DistortionType::saturation:
	{
		return processSaturation(input);
		break;
	}

	default: break;
	}
}


template <typename SampleType>
void Distortion<SampleType>::setParameter(const std::string &name, float value)
{
	if (name == paramDistortionDrive)
		setDrive(value);
	else if (name == paramMixDistortion)
		setMix(value);
	else if (name == paramOutput)
		setOutput(value);
	else if (name == paramDistortionType)
		setCurrentDistortionType(static_cast<DistortionType>(static_cast<int>(value)));
}


template <typename SampleType>
float Distortion<SampleType>::getParameter(const std::string &name) const
{
	if (name == paramDistortionDrive)
		return mDrive.getCurrentValue();
	else if (name == paramMixDistortion)
		return mMix.getCurrentValue();
	else if (name == paramOutput)
		return mOutput.getCurrentValue();
	else if (name == paramDistortionType)
		return static_cast<float>(static_cast<int>(getCurrentDistortionType()));

	return 0.0f;
}


template <typename SampleType>
DistortionType Distortion<SampleType>::getCurrentDistortionType() const
{
	return mDistortionType;
}


template <typename SampleType>
void Distortion<SampleType>::setCurrentDistortionType(const DistortionType newType)
{
	if (mDistortionType != newType)
	{
		mDistortionType = newType;
	}
}


template <typename SampleType>
SampleType Distortion<SampleType>::processSoftClipping(SampleType inputSample)
{
	// Get the next values once per sample
	auto  driveValue  = mDrive.getNextValue();
	auto  mixValue	  = mMix.getNextValue();
	auto  outputValue = mOutput.getNextValue();

	float wetSignal	  = inputSample * juce::Decibels::decibelsToGain(mDrive.getNextValue());

	// Apply distortion (arctangent function)
	wetSignal		  = mSoftClipperCoefficient * std::atan(wetSignal);

	auto mix		  = (1.0 - mixValue) * inputSample + wetSignal * mixValue;

	return mix * juce::Decibels::decibelsToGain(outputValue);
}


template <typename SampleType>
SampleType Distortion<SampleType>::processHardClipping(SampleType inputSample)
{
	// Get the next values once per sample
	auto	   driveValue  = mDrive.getNextValue();
	auto	   mixValue	   = mMix.getNextValue();
	auto	   outputValue = mOutput.getNextValue();

	// Apply drive gain
	auto	   gain		   = juce::Decibels::decibelsToGain(driveValue);
	SampleType wetSignal   = inputSample * gain;

	// Hard clipping
	if (std::abs(wetSignal) > 0.99)
	{
		wetSignal *= 0.99 / std::abs(wetSignal);
	}

	// Mix dry and wet signals
	auto mix = (1.0 - mixValue) * inputSample + wetSignal * mixValue;

	// Apply output gain
	return mix * juce::Decibels::decibelsToGain(outputValue);
}


template <typename SampleType>
SampleType Distortion<SampleType>::processSaturation(SampleType inputSample)
{
	// Get the next values once per sample
	auto  driveValue  = mDrive.getNextValue();
	auto  mixValue	  = mMix.getNextValue();
	auto  outputValue = mOutput.getNextValue();

	auto  drive		  = juce::jmap(driveValue, 0.0f, 24.0f, 0.0f, 6.0f);

	float wetSignal	  = inputSample * juce::Decibels::decibelsToGain(drive);

	if (wetSignal >= 0.0)
	{
		wetSignal = std::tanh(wetSignal);
	}
	else
	{
		wetSignal = std::tanh(std::sinh(wetSignal)) - 0.2 * wetSignal * std::sin(juce::MathConstants<float>::pi * wetSignal);
	}

	auto mix = (1.0 - mixValue) * inputSample + wetSignal * mixValue;

	return mix * juce::Decibels::decibelsToGain(outputValue);
}


// Declare Distortion Template Classes that may be used
template class Distortion<float>;
template class Distortion<double>;
