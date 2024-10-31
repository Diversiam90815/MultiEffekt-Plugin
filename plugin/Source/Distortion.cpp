#include "Distortion.h"

template <typename SampleType>
Distortion<SampleType>::Distortion()
{
}


template <typename SampleType>
void Distortion<SampleType>::prepare(juce::dsp::ProcessSpec &spec)
{
	mSampleRate = spec.sampleRate;

	mDCFilter.prepare(spec);
	mDCFilter.setCutoffFrequency(10.0);
	mDCFilter.setType(juce::dsp::LinkwitzRileyFilter<float>::Type::highpass);

	reset();
}


template <typename SampleType>
void Distortion<SampleType>::reset()
{
	if (mSampleRate <= 0)
		return;

	mDrive.reset(mSampleRate, 0.02);
	mDrive.setTargetValue(0.0f);

	mMix.reset(mSampleRate, 0.02);
	mMix.setTargetValue(1.0f);

	mOutput.reset(mSampleRate, 0.02);
	mOutput.setTargetValue(0.0f);
}



template <typename SampleType>
void Distortion<SampleType>::setDrive(SampleType newDrive)
{
	mDrive.setTargetValue(newDrive);
}

template <typename SampleType>
void Distortion<SampleType>::setMix(SampleType newMix)
{
	mMix.setTargetValue(newMix);
}

template <typename SampleType>
void Distortion<SampleType>::setOutput(SampleType newOutput)
{
	mOutput.setTargetValue(newOutput);
}


template <typename SampleType>
template <typename ProcessContext>
void Distortion<SampleType>::process(const ProcessContext &context) noexcept
{
	const auto &inputBlock	= context.getInputBlock();
	auto	   &outputBlock = context.getOutputBlock();
	const auto	numChannels = outputBlock.getNumChannels();
	const auto	numSamples	= outputBlock.getNumSamples();

	jassert(inputBlock.getNumChannels() == numChannels);
	jassert(inputBlock.getNumSamples() == numSamples);

	for (size_t channel = 0; channel < numChannels; ++channel)
	{
		auto *inputSamples	= inputBlock.getChannelPointer(channel);
		auto *outputSamples = outputBlock.getChannelPointer(channel);

		for (size_t i = 0; i < numSamples; ++i)
		{
			outputSamples[i] = mDCFilter.processSample(channel, outputSamples[i]);
			outputSamples[i] = processSample(inputSamples[i]);
		}
	}
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

// Explicit instantiation of member function templates
template void Distortion<float>::process<juce::dsp::ProcessContextReplacing<float>>(const juce::dsp::ProcessContextReplacing<float> &) noexcept;
template void Distortion<double>::process<juce::dsp::ProcessContextReplacing<double>>(const juce::dsp::ProcessContextReplacing<double> &) noexcept;
