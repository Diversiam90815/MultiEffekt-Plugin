/*
  ==============================================================================

	Module			EffectBase
	Description		Base class for all audio effects, enabling polymorphic behavior

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>
#include <string>


enum class EffectType
{
	None	   = 0,
	Distortion = 1,
	Delay	   = 2,
	Panner	   = 3
};


template <typename SampleType>
class EffectBase
{
public:
	EffectBase()													  = default;
	virtual ~EffectBase()											  = default;

	// Core processing interface
	virtual void	   prepare(const juce::dsp::ProcessSpec &spec)	  = 0;
	virtual void	   process(juce::AudioBuffer<SampleType> &buffer) = 0;
	virtual void	   reset()										  = 0;

	// Effect identification
	virtual EffectType getEffectType() const						  = 0;

	// Parameter interface for generic parameter handling
	virtual void	   setParameter(const std::string &name, float value) {}
	virtual float	   getParameter(const std::string &name) const { return 0.0f; }

	// Bypass functionality
	virtual void	   setBypassed(bool shouldBeBypassed) { mBypassed = shouldBeBypassed; }
	virtual bool	   isBypassed() const { return mBypassed; }

protected:
	// Helper bypass processing
	void   processBypassed(juce::AudioBuffer<SampleType> &buffer) { juce::ignoreUnused(buffer); }

	double getSampleRate() const { return mSampleRate; }
	void   setSampleRate(double sampleRate) { mSampleRate = sampleRate; }

	int	   getNumChannels() const { return mNumChannels; }
	void   setNumChannels(const int numChannels) { mNumChannels = numChannels; }

	int	   getMaxBlockSize() const { return mMaxBlockSize; }
	void   setMaxBlockSize(const int maxBlockSize) { mMaxBlockSize = maxBlockSize; }

private:
	bool   mBypassed{false};
	double mSampleRate{48000.0};
	int	   mNumChannels{0};
	int	   mMaxBlockSize{0};
};

// Explicit template instantiations
template class EffectBase<float>;
template class EffectBase<double>;
