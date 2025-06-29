/*
  ==============================================================================

	Module			ParametricEQ
	Description		4-band parametric equalizer effect module

  ==============================================================================
*/

#include "ParametricEQ.h"

template <typename SampleType>
ParametricEQ<SampleType>::ParametricEQ()
{
	// Initialize default values for each band
	for (int i = 0; i < getNumBands(); ++i)
	{
		mBands[i].frequency.setCurrentAndTargetValue(defaultFrequencies[i]);
		mBands[i].gain.setCurrentAndTargetValue(0.0f);
		mBands[i].q.setCurrentAndTargetValue(0.707f);
		mBands[i].type	  = defaultTypes[i];
		mBands[i].enabled = true;
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
	this->setSampleRate(spec.sampleRate);
	this->setNumChannels(spec.numChannels);
	this->setMaxBlockSize(spec.maximumBlockSize);

	for (auto &band : mBands)
	{
		band.filter.prepare(spec);
		band.filter.reset();

		// Set smoothing parameters (with a 10ms rampt time)
		const auto rampTime = 0.01;
		band.frequency.reset(spec.sampleRate, rampTime);
		band.gain.reset(spec.sampleRate, rampTime);
		band.q.reset(spec.sampleRate, rampTime);

		band.needsUpdate = true;
	}

	updateAllBands();
}


template <typename SampleType>
void ParametricEQ<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
	if (this->isBypassed())
	{
		this->processBypassed(buffer);
		return;
	}

	// Update coefficients if needed
	if (mNeedsUpdate)
	{
		updateAllBands();
		mNeedsUpdate = false;
	}

	// TODO: Add processing code
}


template <typename SampleType>
void ParametricEQ<SampleType>::reset()
{
	for (auto &band : mBands)
	{
		band.filter.reset();
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::setParameter(const std::string &name, float value)
{
	// Parse parameter name and extract band index + parameter type
	// Format is "band{index}_{parameter}, eg. "band0_frequency", "band2_q",..

	if (name.find("band") == 0)
	{
		const auto underscorePos = name.find("_");
		if (underscorePos != std::string::npos && underscorePos > 4)
		{
			const auto bandIndexStr = name.substr(4, underscorePos - 4);
			const auto paramName	= name.substr(underscorePos + 1);

			try
			{
				const int bandIndex = std::stoi(bandIndex);
				if (bandIndex >= 0 && bandIndex < getNumBands())
				{
					if (paramName == "frequency")
						setBandFrequency(bandIndex, value);
					else if (paramName == "gain")
						setBandGain(bandIndex, value);
					else if (paramName == "q")
						setBandQ(bandIndex, value);
					else if (paramName == "enabled")
						setBandEnabled(bandIndex, value);
				}
			}
			catch (const std::exception &)
			{
				// Invalid band index
				assert(false);
			}
		}
	}
}


template <typename SampleType>
float ParametricEQ<SampleType>::getParameter(const std::string &name) const
{
	// Parse parameter name similar to setParameter
	if (name.find("band") == 0)
	{
		const auto underscorePos = name.find('_');
		if (underscorePos != std::string::npos && underscorePos > 4)
		{
			const auto bandIndexStr = name.substr(4, underscorePos - 4);
			const auto paramName	= name.substr(underscorePos + 1);

			try
			{
				const int bandIndex = std::stoi(bandIndexStr);
				if (bandIndex >= 0 && bandIndex < getNumBands())
				{
					if (paramName == "frequency")
						return getBandFrequency(bandIndex);
					else if (paramName == "gain")
						return getBandGain(bandIndex);
					else if (paramName == "q")
						return getBandQ(bandIndex);
					else if (paramName == "enabled")
						return getBandEnabled(bandIndex) ? 1.0f : 0.0f;
				}
			}
			catch (const std::exception &)
			{
				// Invalid band index
				assert(false);
			}
		}
	}
	return 0.0f;
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandFrequency(int bandIndex, float frequency)
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
	{
		// Clamp frequency to valid range (20Hz - Nyquist)
		const auto clampedFreq = juce::jlimit(20.0f, static_cast<float>(mSampleRate * 0.49), frequency);
		mBands[bandIndex].frequency.setTargetValue(clampedFreq);
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandGain(int bandIndex, float gainDB)
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
	{
		// Clamp gain to reasonable range
		const auto clampedGain = juce::jlimit(-24.0f, 24.0f, gainDB);
		mBands[bandIndex].gain.setTargetValue(clampedGain);
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandQ(int bandIndex, float q)
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
	{
		// Clamp Q to reasonable range
		const auto clampedQ = juce::jlimit(0.1f, 20.0f, q);
		mBands[bandIndex].q.setTargetValue(clampedQ);
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandEnabled(int bandIndex, bool enabled)
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
	{
		mBands[bandIndex].enabled = enabled;
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandType(int bandIndex, EQBandType type)
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
	{
		mBands[bandIndex].type		  = type;
		mBands[bandIndex].needsUpdate = true;
	}
}


template <typename SampleType>
float ParametricEQ<SampleType>::getBandFrequency(int bandIndex) const
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
		return mBands[bandIndex].frequency.getCurrentValue();
	return 0.0f;
}


template <typename SampleType>
float ParametricEQ<SampleType>::getBandGain(int bandIndex) const
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
		return mBands[bandIndex].gain.getCurrentValue();
	return 0.0f;
}


template <typename SampleType>
float ParametricEQ<SampleType>::getBandQ(int bandIndex) const
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
		return mBands[bandIndex].q.getCurrentValue();
	return 0.0f;
}


template <typename SampleType>
bool ParametricEQ<SampleType>::getBandEnabled(int bandIndex) const
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
		return mBands[bandIndex].enabled.load();
	return false;
}


template <typename SampleType>
EQBandType ParametricEQ<SampleType>::getBandType(int bandIndex) const
{
	if (bandIndex >= 0 && bandIndex < getNumBands())
		return mBands[bandIndex].type.load();
	return EQBandType::Peaking;
}


template <typename SampleType>
void ParametricEQ<SampleType>::updateBandCoefficients(int bandIndex)
{
	if (bandIndex < 0 || bandIndex >= getNumBands())
		return;

	auto												  &band		  = mBands[bandIndex];
	const auto											   freq		  = band.frequency.getNextValue();
	const auto											   gain		  = band.gain.getNextValue();
	const auto											   q		  = band.q.getNextValue();
	const auto											   type		  = band.type.load();

	const auto											   sampleRate = this->getSampleRate();

	typename juce::dsp::IIR::Coefficients<SampleType>::Ptr coefficients;

	switch (type)
	{
	case EQBandType::LowShelf:
	{
		coefficients = juce::dsp::IIR::Coefficients<SampleType>::makeLowShelf(sampleRate, freq, q, juce::Decibels::decibelsToGain(gain));
		break;
	}
	case EQBandType::HighShelf:
	{
		coefficients = juce::dsp::IIR::Coefficients<SampleType>::makeHighShelf(sampleRate, freq, q, juce::Decibels::decibelsToGain(gain));
		break;
	}
	case EQBandType::Peaking:
	{
		coefficients = juce::dsp::IIR::Coefficients<SampleType>::makePeakFilter(sampleRate, freq, q, juce::Decibels::decibelsToGain(gain));
		break;
	}
	default:
	{
		coefficients = juce::dsp::IIR::Coefficients<SampleType>::makePeakFilter(mSampleRate, freq, q, juce::Decibels::decibelsToGain(gain));
		break;
	}
	}

	if (coefficients != nullptr)
	{
		band.filter.coefficients = coefficients;
		band.lastCoefficients	 = coefficients;
	}
}


template <typename SampleType>
void ParametricEQ<SampleType>::updateAllBands()
{
	for (int i = 0; i < getNumBands(); ++i)
	{
		updateBandCoefficients(i);
	}
}
