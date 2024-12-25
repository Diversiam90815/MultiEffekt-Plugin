/*
  ==============================================================================

	Module			CircularBuffer
	Description		Buffer handler for time based effects

  ==============================================================================
*/

#include "CircularBuffer.h"


template <typename SampleType>
CircularBuffer<SampleType>::CircularBuffer()
{
}


template <typename SampleType>
CircularBuffer<SampleType>::~CircularBuffer()
{
}


template <typename SampleType>
void CircularBuffer<SampleType>::prepare(double sampleRate, int numSamples, int numChannels, int bufferLengthInSeconds)
{
	mNumChannels				 = numChannels;
	mSizeOfBufferInSeconds		 = bufferLengthInSeconds;

	const int circularBufferSize = mSizeOfBufferInSeconds * (sampleRate + numSamples);
	mCircularBuffer.setSize(numChannels, circularBufferSize);
}


template <typename SampleType>
void CircularBuffer<SampleType>::copyFromBufferToCircularBuffer(juce::AudioBuffer<SampleType> &buffer)
{
	for (int channel = 0; channel < mNumChannels; ++channel)
	{
		const int	 bufferLength		  = buffer.getNumSamples();
		const int	 circularBufferLength = mCircularBuffer.getNumSamples();

		const SampleType *bufferData			  = buffer.getReadPointer(channel);
		const SampleType *circularBufferData	  = mCircularBuffer.getReadPointer(channel);

		// Copy Data
		if (circularBufferLength > bufferLength + mWritePosition)
		{
			mCircularBuffer.copyFrom(channel, mWritePosition, bufferData, bufferLength);
		}
		else
		{
			const int bufferRemain = circularBufferLength - mWritePosition;

			// Copy remaining samples to buffer
			mCircularBuffer.copyFrom(channel, mWritePosition, bufferData, bufferRemain);

			// Fill up the circular buffer
			mCircularBuffer.copyFrom(channel, 0, bufferData, bufferLength - bufferRemain);
		}

		mWritePosition += bufferLength;
		mWritePosition %= circularBufferLength;
	}
}


template <typename SampleType>
juce::AudioBuffer<SampleType> &CircularBuffer<SampleType>::getBuffer()
{
	return mCircularBuffer;
}



// Declare Distortion Template Classes that may be used
template class CircularBuffer<float>;
template class CircularBuffer<double>;
