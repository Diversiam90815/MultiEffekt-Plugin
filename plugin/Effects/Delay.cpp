/*
  ==============================================================================

	Module			Delay
	Description		Delay effect module

  ==============================================================================
*/

#include "Delay.h"


template <typename SampleType>
Delay<SampleType>::Delay()
{
	mDelayType = DelayType::SingleTap;
}


template <typename SampleType>
void Delay<SampleType>::prepare(juce::dsp::ProcessSpec &spec, float maxDelayInMS)
{
	// Store the parameters locally
	mSampleRate	  = spec.sampleRate;
	mNumChannels  = spec.numChannels;
	mMaxBlockSize = spec.maximumBlockSize;

	// prepare the buffer
	mDelayBuffer.prepare(mSampleRate, mMaxBlockSize, mNumChannels, ((int)maxDelayInMS * 0.001));

	mCircularBufferLength = mDelayBuffer.getBuffer().getNumSamples();

	mWritePositions.resize(mNumChannels);

	for (int channel = 0; channel < mNumChannels; ++channel)
	{
		mWritePositions[channel] = 0;
	}
}


template <typename SampleType>
void Delay<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	const int numSamples							   = buffer.getNumSamples();
	const int numChannels							   = buffer.getNumChannels();

	mDelayInSamples									   = (int)(mDelayTimeMS.getCurrentValue() * (mSampleRate / 1000.0));

	// For each channel we will
	// 1. Write the incoming samples into the delay buffer
	// 2. Read out delayed samples from the delay buffer
	// 3. Apply feedback
	// 4. Mix into output

	// Get reference to buffer
	juce::AudioBuffer<SampleType> &delayBufferRef	   = mDelayBuffer.getBuffer();
	auto						   delayBufferWritePtr = delayBufferRef.getArrayOfWritePointers();

	for (int channel = 0; channel < numChannels; ++channel)
	{
		SampleType *channelData		= buffer.getWritePointer(channel);
		SampleType *delayBufferData = delayBufferWritePtr[channel];

		int		   &writePosition	= mWritePositions[channel];

		for (int i = 0; i < numSamples; ++i)
		{
			float			 feedbackValue	= mFeedback.getNextValue();
			float			 mixValue		= mMix.getNextValue();

			// Current Sample from input
			const SampleType inputSample	= channelData[i];

			// Write current input sample to the delay buffer (considering feedback)
			SampleType		 delayedSample	= delayBufferData[writePosition];
			SampleType		 newDelayValues = inputSample + (delayedSample * feedbackValue);
			delayBufferData[writePosition]	= newDelayValues;

			// Compute read position
			int readPosition				= (writePosition - mDelayInSamples) % mCircularBufferLength;
			if (readPosition < 0)
			{
				readPosition += mCircularBufferLength; // Wrap around
			}

			// Get delayed output
			SampleType out = delayBufferData[readPosition];

			// Mix delayed output
			channelData[i] = (SampleType(1.0f) - mixValue) * inputSample + (mixValue * out);

			// Set write position
			++writePosition;
			if (writePosition >= mCircularBufferLength)
			{
				writePosition = 0;
			}
		}
	}
}


template <typename SampleType>
void Delay<SampleType>::setMix(float newValue)
{
	mMix.setTargetValue(newValue);
}


template <typename SampleType>
void Delay<SampleType>::setDelayTime(float timeInMS)
{
	mDelayTimeMS.setTargetValue(timeInMS);
}


template <typename SampleType>
void Delay<SampleType>::setFeedback(float newValue)
{
	mFeedback.setTargetValue(newValue);
}


template <typename SampleType>
DelayType Delay<SampleType>::getDelayType() const
{
	return mDelayType;
}


template <typename SampleType>
void Delay<SampleType>::setDelayType(DelayType type)
{
	if (mDelayType != type)
	{
		mDelayType = type;
	}
}



// Declare Distortion Template Classes that may be used
template class Delay<float>;
template class Delay<double>;
