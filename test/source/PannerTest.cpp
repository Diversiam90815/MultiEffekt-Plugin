#include <gtest/gtest.h>

#include "PluginProcessor.h"
#include <thread>


TEST(PannerManager, MonoPanning)
{
	PannerManager<float>   panner;
	juce::dsp::ProcessSpec spec{44100, 512, 1};
	panner.setPannerMode(PannerType::Mono);
	panner.prepare(spec);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	juce::AudioBuffer<float> buffer(1, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f);					 // Impulse

	panner.enableLFO(false);
	panner.processMonoPanner(-0.5f, 0.0f, 0.0f);		 // Set pan to center
	panner.process(buffer);

	ASSERT_NEAR(buffer.getSample(0, 0), 0.5f, 0.1f); // Check center pan effect
}

TEST(PannerManager, StereoPanning)
{
	PannerManager<float>   panner;
	juce::dsp::ProcessSpec spec{44100, 512, 2};
	panner.setPannerMode(PannerType::Stereo);
	panner.prepare(spec);

	panner.enableLFO(false);	// Turn LFO Off


	juce::AudioBuffer<float> buffer(2, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f); // Impulse in left channel

	panner.processStereoPanner(+1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);	// Full Right pan with no LFO
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	panner.process(buffer);

	ASSERT_NEAR(buffer.getSample(0, 0), 0.0f, 0.1f); // Expect full pan to the right
	ASSERT_NEAR(buffer.getSample(1, 0), 1.0f, 0.1f); // Full signal in the right channel
}
