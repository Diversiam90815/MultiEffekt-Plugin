#include <gtest/gtest.h>

#include "PluginProcessor.h"



TEST(PluginProcessor, PrepareToPlay)
{
	PluginProcessor processor;
	processor.prepareToPlay(44100, 512);

	ASSERT_NO_THROW(processor.prepareToPlay(44100, 512)); // Ensure no exceptions are thrown
}

TEST(PluginProcessor, ProcessBlock)
{
	PluginProcessor processor;
	processor.prepareToPlay(44100, 512);

	juce::AudioBuffer<float> buffer(2, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f);

	juce::MidiBuffer midi;
	processor.processBlock(buffer, midi);

	ASSERT_NE(buffer.getSample(0, 0), 0.0f); // Expect processing to occur
}

TEST(Distortion, ProcessSample)
{
	Distortion<float>	   distortion;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	distortion.prepare(spec);

	// Set parameters
	distortion.setDrive(1.0f);
	distortion.setMix(1.0f);
	distortion.setOutput(1.0f);

	// Process a sample
	float inputSample  = 0.5f;
	float outputSample = distortion.processSample(inputSample);

	ASSERT_NEAR(outputSample, 0.5f, 0.1f); // Check output is within a reasonable range
}

TEST(Distortion, ParameterChange)
{
	Distortion<float> distortion;
	distortion.setCurrentDistortionType(DistortionType::saturation);
	ASSERT_EQ(distortion.getCurrentDistortionType(), DistortionType::saturation);
}


TEST(PannerManager, MonoPanning)
{
	PannerManager<float>   panner;
	juce::dsp::ProcessSpec spec{44100, 512, 1};
	panner.setPannerMode(1);
	panner.prepare(spec);

	juce::AudioBuffer<float> buffer(1, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f);					 // Impulse

	panner.enableLFO(false);
	panner.processMonoPanner(0.5f, 1.0f, 0.0f);		 // Set pan to center
	panner.process(buffer);

	ASSERT_NEAR(buffer.getSample(0, 0), 0.5f, 0.1f); // Check center pan effect
}

TEST(PannerManager, StereoPanning)
{
	PannerManager<float>   panner;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	panner.setPannerMode(2);
	panner.prepare(spec);

	juce::AudioBuffer<float> buffer(2, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f); // Impulse in left channel

	panner.processStereoPanner(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	panner.process(buffer);

	ASSERT_NEAR(buffer.getSample(0, 0), 0.0f, 0.1f); // Expect full pan to the right
	ASSERT_NEAR(buffer.getSample(1, 0), 1.0f, 0.1f); // Full signal in the right channel
}