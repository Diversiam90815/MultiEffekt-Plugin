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

	mWritePosition = 0;
}


void Delay::process(juce::AudioBuffer<float> &buffer)
{
	const int numSamples = buffer.getNumSamples();
	const int numChannels = buffer.getNumChannels();

	mDelayInSamples		  = (int)(mDelayTimeMS.getCurrentValue() * 1000 * mSampleRate);

	// For each channel we will
	// 1. Write the incoming samples into the delay buffer
	// 2. Read out delayed samples from the delay buffer
	// 3. Apply feedback
	// 4. Mix into output


}


