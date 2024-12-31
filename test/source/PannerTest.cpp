#include <gtest/gtest.h>

#include "PluginProcessor.h"
#include <thread>


TEST(PannerManager, MonoPanning)
{
	PannerManager<float>   panner;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	panner.setPannerMode(PannerType::Mono);
	panner.prepare(spec);

	juce::AudioBuffer<float> buffer(2, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f);				 // Impulse
	buffer.setSample(1, 0, 1.0f);				 // Impulse

	panner.enableLFO(false);
	panner.processMonoPanner(-0.5f, 0.0f, 0.0f);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	panner.process(buffer);

	// With a pan of -0.5f ( pan + 1 = 0.5 => π/4 * 0.5 = π/8)
	float leftGain	= std::cos(juce::MathConstants<float>::pi / 8.0f);
	float rightGain = std::sin(juce::MathConstants<float>::pi / 8.0f);
	
	ASSERT_NEAR(buffer.getSample(0, 0), leftGain, 0.1f);
	ASSERT_NEAR(buffer.getSample(1, 0), rightGain, 0.1f);
}

TEST(PannerManager, StereoPanning)
{
	PannerManager<float>   panner;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	panner.setPannerMode(PannerType::Stereo);
	panner.prepare(spec);

	panner.enableLFO(false); // Turn LFO Off

	juce::AudioBuffer<float> buffer(2, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f);									  // Impulse in left channel

	panner.processStereoPanner(+1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f); // Full Right pan with no LFO
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	panner.process(buffer);

	ASSERT_NEAR(buffer.getSample(0, 0), 0.0f, 0.1f); // Expect full pan to the right
	ASSERT_NEAR(buffer.getSample(1, 0), 1.0f, 0.1f); // Full signal in the right channel
}
