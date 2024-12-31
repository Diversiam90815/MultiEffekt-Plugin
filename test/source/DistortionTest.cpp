#include <gtest/gtest.h>

#include "PluginProcessor.h"

#include <thread>


TEST(Distortion, ProcessSample)
{
	Distortion<float>	   distortion;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	distortion.prepare(spec);
	distortion.setCurrentDistortionType(DistortionType::softClipping);

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

TEST(Distortion, TypeChange)
{
	Distortion<float> distortion;
	distortion.setCurrentDistortionType(DistortionType::saturation);
	ASSERT_EQ(distortion.getCurrentDistortionType(), DistortionType::saturation);
}

TEST(Distortion, Reset)
{
	Distortion<float>	   distortion;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	distortion.prepare(spec);

	distortion.setDrive(10.0f);
	distortion.setMix(0.5f);
	distortion.setOutput(0.8f);

	distortion.reset();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	ASSERT_FLOAT_EQ(distortion.processSample(1.0f), 0.0f); // Default values should lead to no distortion
}
