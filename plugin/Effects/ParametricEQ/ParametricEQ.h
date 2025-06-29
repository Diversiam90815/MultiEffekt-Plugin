/*
  ==============================================================================

	Module			ParametricEQ
	Description		4-band parametric equalizer effect module

  ==============================================================================
*/

#pragma once

#include <array>
#include <assert.h>

#include "EffectBase.h"
#include "Parameters.h"


enum class EQBandType
{
	HighShelf = 0,
	Peaking	  = 1,
	LowShelf  = 2
};


template <typename SampleType>
class ParametricEQ : public EffectBase<SampleType>
{
public:
	ParametricEQ();
	~ParametricEQ() = default;

	void				 prepare(const juce::dsp::ProcessSpec &spec) override;
	void				 process(juce::AudioBuffer<SampleType> &buffer) override;
	void				 reset() override;
	EffectType			 getEffectType() const override { return EffectType::EQ; }

	void				 setParameter(const std::string &name, float value) override;
	float				 getParameter(const std::string &name) const override;

	// Band-specific parameter setters
	void				 setBandFrequency(int bandIndex, float frequency);
	void				 setBandGain(int bandIndex, float gainDB);
	void				 setBandQ(int bandIndex, float q);
	void				 setBandEnabled(int bandIndex, bool enabled);
	void				 setBandType(int bandIndex, EQBandType type);

	// Parameter getters
	float				 getBandFrequency(int bandIndex) const;
	float				 getBandGain(int bandIndex) const;
	float				 getBandQ(int bandIndex) const;
	bool				 getBandEnabled(int bandIndex) const;
	EQBandType			 getBandType(int bandIndex) const;

	static constexpr int getNumBands() { return 4; }

private:
	struct EQBand
	{
		juce::dsp::IIR::Filter<SampleType>					   filter;
		juce::SmoothedValue<SampleType>						   frequency{1000.0f};
		juce::SmoothedValue<SampleType>						   gain{0.0f};
		juce::SmoothedValue<SampleType>						   q{0.707f};
		std::atomic<bool>									   enabled{true};
		std::atomic<EQBandType>								   type{EQBandType::Peaking};
		typename juce::dsp::IIR::Coefficients<SampleType>::Ptr lastCoefficients;
		bool												   needsUpate{true};
	};

	void									   updateBandCoefficients(int bandIndex);
	void									   updateAllBands();

	std::array<EQBand, 4>					   mBands;
	double									   mSampleRate{48000.0};
	bool									   mNeedsUpdate{true};

	// Default frequencies for each band
	static constexpr std::array<float, 4>	   defaultFrequencies = {100.0f, 500.0f, 2000.0f, 8000.0f};
	static constexpr std::array<EQBandType, 4> defaultTypes		  = {EQBandType::LowShelf, EQBandType::Peaking, EQBandType::Peaking, EQBandType::HighShelf};
};
