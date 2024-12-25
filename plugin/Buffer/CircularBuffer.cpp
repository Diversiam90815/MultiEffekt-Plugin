
#include "CircularBuffer.h"


CircularBuffer::CircularBuffer()
{
}


CircularBuffer::~CircularBuffer()
{
}


void CircularBuffer::prepare(double sampleRate, int numSamples, int numChannels, int bufferLengthInSeconds)
{
	mNumChannels				 = numChannels;
	mSizeOfBufferInSeconds		 = bufferLengthInSeconds;

	const int circularBufferSize = mSizeOfBufferInSeconds * (sampleRate + numSamples);
	mCircularBuffer.setSize(numChannels, circularBufferSize);
}


void CircularBuffer::copyFromBufferToCircularBuffer(juce::AudioBuffer<float> &buffer)
{
	for (int channel = 0; channel < mNumChannels; ++channel)
	{
		const int	 bufferLength		  = buffer.getNumSamples();
		const int	 circularBufferLength = mCircularBuffer.getNumSamples();

		const float *bufferData			  = buffer.getReadPointer(channel);
		const float *circularBufferData	  = mCircularBuffer.getReadPointer(channel);

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


juce::AudioBuffer<float> CircularBuffer::getBuffer()
{
	return mCircularBuffer;
}
