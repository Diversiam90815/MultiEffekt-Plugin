/*
  ==============================================================================

	Module			StereoPanner
	Description		Panner effect module handling stereo input signals

  ==============================================================================
*/

#include "StereoPanner.h"


template <typename SampleType>
inline StereoPanner<SampleType>::StereoPanner()
{
	// Initialize both LFOs with a sine wave
	mLeftChannelLFO.initialise([](SampleType x) { return std::sin(x); });
	mRightChannelLFO.initialise([](SampleType x) { return std::sin(x); });
}


template <typename SampleType>
void StereoPanner<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	PannerBase<SampleType>::setSampleRate(spec.sampleRate);
	
	mLeftChannelLFO.prepare(spec);
	mRightChannelLFO.prepare(spec);

	reset();
}


template <typename SampleType>
void StereoPanner<SampleType>::reset()
{
	mLeftChannelLFO.reset();
	mRightChannelLFO.reset();
}


template <typename SampleType>
void StereoPanner<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	const int numChannels = buffer.getNumChannels();
	const int numSamples  = buffer.getNumSamples();
	const double samplerate  = PannerBase<SampleType>::getSampleRate();

	jassert(samplerate != 0);  // Call ::prepare before attempting to call ::process()!
	jassert(numChannels >= 2); // No panning possible with only one channel!
	if (numChannels < 2)
		return;

	// For convenience
	auto *leftChanData	= buffer.getWritePointer(0);
	auto *rightChanData = buffer.getWritePointer(1);

	// Read parameter values
	float leftBasePan	= mLeftChannelPan.getNextValue();
	float leftLfoFreq	= mLeftChannelLfoFrequency.getNextValue();
	float leftLfoDepth	= mLeftChannelLfoDepth.getNextValue();

	float rightBasePan	= mRightChannelPan.getNextValue();
	float rightLfoFreq	= mRightChannelLfoFrequency.getNextValue();
	float rightLfoDepth = mRightChannelLfoDepth.getNextValue();

	bool  lfoEnabled	= PannerBase<SampleType>::getLfoEnabled();

	// Update LFO frequencies
	mLeftChannelLFO.setFrequency(leftLfoFreq, samplerate);
	mRightChannelLFO.setFrequency(rightLfoFreq, samplerate);

	for (int sample = 0; sample < numSamples; ++sample)
	{
		// Process the LFO, generating a sine wave between -1.0f and +1.0f
		auto  lfoLeftValue		= mLeftChannelLFO.processSample((SampleType)0.0);
		auto  lfoRightValue		= mRightChannelLFO.processSample((SampleType)0.0);

		// Final pan for each channel = basePan + LFO*depth
		float finalPanLeft		= leftBasePan + (lfoLeftValue * leftLfoDepth);
		float finalPanRight		= rightBasePan + (lfoRightValue * rightLfoDepth);

		// Limit finalPan between -1.0 and +1.0
		finalPanLeft			= juce::jlimit<float>(-1.0f, 1.0f, finalPanLeft);
		finalPanRight			= juce::jlimit<float>(-1.0f, 1.0f, finalPanRight);

		// Convert each pan to left/right gains (constant power pannin)
		//   leftGain  = cos( (pan + 1)*π/4 )
		//   rightGain = sin( (pan + 1)*π/4 )
		auto angleLeft			= juce::MathConstants<SampleType>::pi * ((lfoEnabled ? finalPanLeft : leftBasePan) + 1.0f) * 0.25f;
		auto angleRight			= juce::MathConstants<SampleType>::pi * ((lfoEnabled ? finalPanRight : rightBasePan) + 1.0f) * 0.25f;

		auto leftChanLeftGain	= std::cos(angleLeft);
		auto leftChanRightGain	= std::sin(angleLeft);

		auto rightChanLeftGain	= std::cos(angleRight);
		auto rightChanRightGain = std::sin(angleRight);

		// Original input samples
		auto inL				= leftChanData[sample];
		auto inR				= rightChanData[sample];


		// Apply gain to the channels

		// OutLeft = (LeftChan -> Left) + (RightChan -> Left)
		auto outL				= inL * leftChanLeftGain + inR * rightChanLeftGain;

		// OutRight = (LeftChan -> Right) + (RightChan -> Right)
		auto outR				= inL * leftChanRightGain + inR * rightChanRightGain;

		// Store back
		leftChanData[sample]	= outL;
		rightChanData[sample]	= outR;
	}
}


template <typename SampleType>
void StereoPanner<SampleType>::setLeftChannelPan(float newPan)
{
	mLeftChannelPan.setTargetValue(newPan);
}


template <typename SampleType>
void StereoPanner<SampleType>::setLeftChannelLfoRate(float newFrequency)
{
	mLeftChannelLfoFrequency.setTargetValue(newFrequency);
}


template <typename SampleType>
void StereoPanner<SampleType>::setLeftChannelLfoDepth(float newDepth)
{
	mLeftChannelLfoDepth.setTargetValue(newDepth);
}


template <typename SampleType>
void StereoPanner<SampleType>::setRightChannelPan(float newPan)
{
	mRightChannelPan.setTargetValue(newPan);
}


template <typename SampleType>
void StereoPanner<SampleType>::setRightChannelLfoRate(float newFrequency)
{
	mRightChannelLfoFrequency.setTargetValue(newFrequency);
}


template <typename SampleType>
void StereoPanner<SampleType>::setRightChannelLfoDepth(float newDepth)
{
	mRightChannelLfoDepth.setTargetValue(newDepth);
}


// Explicit template instantiations
template class StereoPanner<float>;
template class StereoPanner<double>;
