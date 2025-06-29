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
}


template <typename SampleType>
void Delay<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	// Use the stored maxDelayInMS if it was set, otherwise calculate a default
	if (mMaxDelayInMS <= 0.0f)
	{
		// Set a reasonable default based on maximum block size
		// This gives us roughly 20-50ms of delay at typical sample rates
		mMaxDelayInMS = static_cast<float>(spec.maximumBlockSize) * 1000.0f / static_cast<float>(spec.sampleRate) * 10.0f;

		// Ensure we have at least 10ms and at most 2000ms (2 seconds)
		mMaxDelayInMS = juce::jlimit(10.0f, 2000.0f, mMaxDelayInMS);
	}

	// Call the existing prepare method with the calculated or stored max delay
	prepare(const_cast<juce::dsp::ProcessSpec &>(spec), mMaxDelayInMS);
}


template <typename SampleType>
void Delay<SampleType>::prepare(const juce::dsp::ProcessSpec &spec, float maxDelayInMS)
{
	// Store the parameters locally
	mMaxDelayInMS = maxDelayInMS;
	this->setSampleRate(spec.sampleRate);
	this->setNumChannels(spec.numChannels);
	this->setMaxBlockSize(spec.maximumBlockSize);

	// prepare the buffer
	prepareDelayBuffer();

	mCircularBufferLength = mDelayBuffer.getBuffer().getNumSamples();

	mWritePositions.resize(spec.numChannels);

	for (int channel = 0; channel < spec.numChannels; ++channel)
	{
		mWritePositions[channel] = 0;
	}

	mChannelDelayTimes.resize(spec.numChannels);
	for (int channel = 0; channel < spec.numChannels; ++channel)
	{
		mChannelDelayTimes[channel].reset(spec.sampleRate, 0.02);
	}
}


template <typename SampleType>
void Delay<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	const int					   numSamples		   = buffer.getNumSamples();
	const int					   numChannels		   = buffer.getNumChannels();

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
			float			 feedbackValue			 = mFeedback.getNextValue();
			float			 mixValue				 = mMix.getNextValue();

			// Get the channel specific delay time
			float			 thisChannelDelayTimeMS	 = mChannelDelayTimes[channel].getNextValue();
			int				 thisChannelDelaySamples = (int)(thisChannelDelayTimeMS * (this->getSampleRate() / 1000.0f));

			// Current Sample from input
			const SampleType inputSample			 = channelData[i];

			// Write current input sample to the delay buffer (considering feedback)
			SampleType		 delayedSample			 = delayBufferData[writePosition];
			SampleType		 newDelayValues			 = inputSample + (delayedSample * feedbackValue);
			delayBufferData[writePosition]			 = newDelayValues;

			// Compute read position
			int readPosition						 = (writePosition - thisChannelDelaySamples) % mCircularBufferLength;
			while (readPosition < 0)
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
void Delay<SampleType>::reset()
{
	// Clear delay buffer and reset write positions
	if (mDelayBuffer.getBuffer().getNumSamples() > 0)
	{
		mDelayBuffer.getBuffer().clear();
	}

	for (auto &pos : mWritePositions)
	{
		pos = 0;
	}
}


template <typename SampleType>
void Delay<SampleType>::setParameter(const std::string &name, float value)
{
	if (name == "mix")
		setMix(value);
	else if (name == "feedback")
		setFeedback(value);
	else if (name == "delayTimeLeft" && mChannelDelayTimes.size() > 0)
		setChannelDelayTime(0, value);
	else if (name == "delayTimeRight" && mChannelDelayTimes.size() > 1)
		setChannelDelayTime(1, value);
	else if (name == "maxDelayInMS")
	{
		mMaxDelayInMS = value;
		// TODO : reprepare delay / buffer
	}
}


template <typename SampleType>
float Delay<SampleType>::getParameter(const std::string &name) const
{
	if (name == "mix")
		return mMix.getCurrentValue();
	else if (name == "feedback")
		return mFeedback.getCurrentValue();
	else if (name == "delayTimeLeft" && mChannelDelayTimes.size() > 0)
		return mChannelDelayTimes[0].getCurrentValue();
	else if (name == "delayTimeRight" && mChannelDelayTimes.size() > 1)
		return mChannelDelayTimes[1].getCurrentValue();
	else if (name == "maxDelayInMS")
		return mMaxDelayInMS;

	return 0.0f;
}


template <typename SampleType>
void Delay<SampleType>::prepareDelayBuffer()
{
	mDelayBuffer.prepare(this->getSampleRate(), this->getMaxBlockSize(), this->getNumChannels(), static_cast<int>(mMaxDelayInMS * 0.001f * this->getSampleRate()));
}


template <typename SampleType>
void Delay<SampleType>::setMix(float newValue)
{
	mMix.setTargetValue(newValue);
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


template <typename SampleType>
void Delay<SampleType>::setChannelDelayTime(int channel, float timeInMS)
{
	if (channel < 0 || channel >= this->getNumChannels())
		return;

	mChannelDelayTimes[channel].setTargetValue(timeInMS);
}


// Declare Distortion Template Classes that may be used
template class Delay<float>;
template class Delay<double>;
