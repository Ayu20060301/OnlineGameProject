#pragma once

#include <random>

class MyRandom
{
public:
	static void Init();
	static unsigned GetRandom();
	static bool GetBernoulli(float trueProb);
	static int GetDistribution(int min, int max);
	static float GetDistributionF(float min, float max);

private:
	static std::mt19937* m_Mt;
	static std::default_random_engine* m_Engine;
};
