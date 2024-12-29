/*
  ==============================================================================

	Module			MonoPanner
	Description		Panner effect module handling mono input signals

  ==============================================================================
*/

#include "MonoPanner.h"


template <typename SampleType>
MonoPanner<SampleType>::MonoPanner()
{
	// Initialize the LFO with a sine wave
	mLFO.initialise([](SampleType x) { return std::sin(x); });
}


template <typename SampleType>
void MonoPanner<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	mSampleRate = spec.sampleRate;
	mLFO.prepare(spec);
	reset();
}


template <typename SampleType>
void MonoPanner<SampleType>::reset()
{
	mLFO.reset();
}


template <typename SampleType>
void MonoPanner<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	const int numChannels = buffer.getNumChannels();
	const int numSamples  = buffer.getNumSamples();

	jassert(mSampleRate == 0); // Call ::prepare before attempting to call ::process()!
	jassert(numChannels < 2);  // No panning possible with only one channel!
	if (numChannels < 2)
		return;

	// Read parameter values
	auto basePan	= mPan.getNextValue();
	auto lfoFreq	= mLfoFrequency.getNextValue();
	auto lfoDepth	= mLfoDepth.getNextValue();
	bool lfoEnabled = mLfoEnabled.load();

	// Update LFO Frequency
	mLFO.setFrequency(lfoFreq, mSampleRate);

	// For each sample compute LFO value and final pan (if enabled)
	for (int sample = 0; sample < numSamples; ++sample)
	{
		// Process the LFO, generating a sine wave between -1.0f and +1.0f
		auto lfoValue		  = mLFO.processSample(0.0f);

		// Final pan including LFO Modulation
		// (e.g. basePan = 0.3, lfoDepth = 0.5f => lfoValue = +/-1 => finalPan goes from (0.3-0.5) to (0.3+0.5)
		auto finalPan		  = basePan + (lfoDepth * lfoValue);

		// Limit finalPan between -1.0 and +1.0
		finalPan			  = juce::jlimit<SampleType>((SampleType)-1.0, (SampleType)1.0, (SampleType)finalPan);

		// Convert pan (-1..+1) to left & right gains:
		//   leftGain  = cos( (pan + 1)*π/4 )
		//   rightGain = sin( (pan + 1)*π/4 )
		auto radiantValue	  = juce::MathConstants<SampleType>::pi * ((lfoEnabled ? finalPan : basePan) + 1.0f) * 0.25f;
		auto leftGain		  = std::cos(radiantValue);
		auto rightGain		  = std::sin(radiantValue);

		// Apply gain to the channels
		auto leftChanelData	  = buffer.getWritePointer(0);
		auto rightChannelData = buffer.getWritePointer(1);

		leftChanelData[sample] *= leftGain;
		rightChannelData[sample] *= rightGain;
	}
}


template <typename SampleType>
void MonoPanner<SampleType>::setPan(float newPan)
{
	mPan.setTargetValue(newPan);
}


template <typename SampleType>
void MonoPanner<SampleType>::setLfoRate(float newFrequency)
{
	mLfoFrequency.setTargetValue(newFrequency);
}


template <typename SampleType>
void MonoPanner<SampleType>::setLfoDepth(float newDepth)
{
	mLfoDepth.setTargetValue(newDepth);
}


template class MonoPanner<float>;
template class MonoPanner<double>;