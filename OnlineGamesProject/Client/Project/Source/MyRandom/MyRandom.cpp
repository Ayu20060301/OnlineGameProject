#include "MyRandom.h"

using namespace std;

mt19937* MyRandom::m_Mt = nullptr;
default_random_engine* MyRandom::m_Engine = nullptr;

void MyRandom::Init()
{
	//乱数シード設定
	random_device rd;
	m_Mt = new mt19937(rd());

	//乱数エンジン設定
	m_Engine = new default_random_engine(rd());
}

unsigned MyRandom::GetRandom()
{
	return (*m_Mt)();
}

bool MyRandom::GetBernoulli(float trueProb)
{
	bernoulli_distribution dist(trueProb);
	return dist(*m_Engine);
}

int MyRandom::GetDistribution(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(*m_Engine);
}

float MyRandom::GetDistributionF(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);
	return dist(*m_Engine);
}
