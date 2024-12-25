/*
  ==============================================================================

	Module			Delay
	Description		Delay effect module

  ==============================================================================
*/

#include "Delay.h"


Delay::Delay()
{
}


void Delay::prepare(juce::dsp::ProcessSpec &spec, float maxDelayInMS)
{
	// Store the parameters locally
	mSampleRate					= spec.sampleRate;
	mNumChannels				= spec.numChannels;
	mMaxBlockSize				= spec.maximumBlockSize;

	// prepare the buffer
	const int maxDelayInSamples = (int)std::ceil(maxDelayInMS * 1000 * mSampleRate);

	mDelayBuffer.prepare(mSampleRate, mMaxBlockSize, mNumChannels, ((int)maxDelayInMS * 1000));

	mCircularBufferLength = mDelayBuffer.getBuffer().getNumSamples();

	mWritePosition		  = 0;
}


void Delay::process(juce::AudioBuffer<float> &buffer)
{
	const int numSamples						 = buffer.getNumSamples();
	const int numChannels						 = buffer.getNumChannels();

	mDelayInSamples								 = (int)(mDelayTimeMS.getCurrentValue() * 1000 * mSampleRate);

	// For each channel we will
	// 1. Write the incoming samples into the delay buffer
	// 2. Read out delayed samples from the delay buffer
	// 3. Apply feedback
	// 4. Mix into output


	// Get reference to buffer
	juce::AudioBuffer<float> delayBufferRef		 = mDelayBuffer.getBuffer();
	auto					 delayBufferWritePtr = delayBufferRef.getArrayOfWritePointers();

	for (int channel = 0; channel < numChannels; ++channel)
	{
		float *channelData	   = buffer.getWritePointer(channel);
		float *delayBufferData = delayBufferWritePtr[channel];

		for (int i = 0; i < numSamples; ++i)
		{
			// Current Sample from input
			const float *in					= &channelData[i];
			const float	 inputSample		= channelData[i];

			// Write current input sample to the delay buffer (considering feedback)
			float		 delayedSample		= delayBufferData[mWritePosition];
			float		 newDelayValues		= inputSample + (delayedSample * mFeedback.getCurrentValue());
			delayBufferData[mWritePosition] = newDelayValues;

			// Compute read position
			int readPosition				= mWritePosition - mDelayInSamples;
			if (readPosition < 0)
			{
				readPosition += mCircularBufferLength; // Wrap around
			}

			// Get delayed output
			float out	   = delayBufferData[readPosition];

			// Mix delayed output
			channelData[i] = (1.0f - mMix.getCurrentValue()) * (*in) + (mMix.getCurrentValue() * out);

			// Set write position
			++mWritePosition;
			if (mWritePosition >= mCircularBufferLength)
			{
				mWritePosition = 0;
			}
		}
	}
}
