#include <gtest/gtest.h>

#include "PluginProcessor.h"

TEST(Delay, DelayTypeChange)
{
	Delay<float> delay;
	delay.setDelayType(DelayType::PingPong);

	ASSERT_EQ(delay.getDelayType(), DelayType::PingPong);
}