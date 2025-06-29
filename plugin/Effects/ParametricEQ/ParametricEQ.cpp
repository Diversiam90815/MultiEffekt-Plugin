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
}


template <typename SampleType>
void ParametricEQ<SampleType>::prepare(const juce::dsp::ProcessSpec &spec)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::process(juce::AudioBuffer<SampleType> &buffer)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::reset()
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::setParameter(const std::string &name, float value)
{
}


template <typename SampleType>
float ParametricEQ<SampleType>::getParameter(const std::string &name) const
{
	return 0.0f;
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandFrequency(int bandIndex, float frequency)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandGain(int bandIndex, float gainDB)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandQ(int bandIndex, float q)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandEnabled(int bandIndex, bool enabled)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::setBandType(int bandIndex, EQBandType type)
{
}


template <typename SampleType>
float ParametricEQ<SampleType>::getBandFrequency(int bandIndex) const
{
	return 0.0f;
}


template <typename SampleType>
float ParametricEQ<SampleType>::getBandGain(int bandIndex) const
{
	return 0.0f;
}


template <typename SampleType>
float ParametricEQ<SampleType>::getBandQ(int bandIndex) const
{
	return 0.0f;
}


template <typename SampleType>
bool ParametricEQ<SampleType>::getBandEnabled(int bandIndex) const
{
	return false;
}


template <typename SampleType>
EQBandType ParametricEQ<SampleType>::getBandType(int bandIndex) const
{
	return EQBandType();
}


template <typename SampleType>
void ParametricEQ<SampleType>::updateBandCoefficients(int bandIndex)
{
}


template <typename SampleType>
void ParametricEQ<SampleType>::updateAllBands()
{
}
