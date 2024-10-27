#include "Distortion.h"

template <typename SampleType>
Distortion<SampleType>::Distortion()
{
}


template <typename SampleType>
void Distortion<SampleType>::prepare(juce::dsp::ProcessSpec &spec)
{
	mSampleRate = spec.sampleRate;
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
		auto *inputSamples = inputBlock.getChannelPointer(channel);
		auto *outputSamples = outputBlock.getChannelPointer(channel);

		for (size_t i = 0; i < numSamples; ++i)
			outputSamples[i] = processSample(inputSamples[i]);
	}
}


template <typename SampleType>
void Distortion<SampleType>::processSample(SampleType input) noexcept
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
SampleType Distortion<SampleType>::processSoftClipping(SampleType input)
{
	return input;
}


template <typename SampleType>
SampleType Distortion<SampleType>::processHardClipping(SampleType input)
{
	if (std::abs(input) > 0.99f)
	{
		input = 0.99 / std::abs(input);
	}

	return input;
}


template <typename SampleType>
SampleType Distortion<SampleType>::processSaturation(SampleType input)
{
	// Apply distortion (arctangent function)
	input = (2.0f / juce::MathConstants<float>::pi) * atan(input);

	return input;
}



// Declare Distortion Template Classes that may be used
template class Distortion<float>;
template class Distortion<double>;