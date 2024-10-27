#include "Distortion.h"

template <typename SampleType>
Distortion<SampleType>::Distortion()
{
}


template <typename SampleType>
void Distortion<SampleType>::prepare(juce::dsp::ProcessSpec &spec)
{
	mSampleRate = spec.sampleRate;
}


template <typename SampleType>
void Distortion<SampleType>::reset()
{
}


template class Distortion<float>;
template class Distortion<double>;