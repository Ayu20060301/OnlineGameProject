#include "UIGauge.h"
#include "../MyMath/MyMath.h"
 
UIGauge::UIGauge()
{
	m_FrameHandle = 0;
	m_GaugeHandle = 0;
	m_GaugeWidth = 0;
	m_GaugeHeight = 0;
	m_Value = 0.0f;
	m_MaxValue = 0.0f;
	m_GaugePos = {};
}

UIGauge::~UIGauge()
{
	Fin();
}

void UIGauge::Load(const char* framePath, const char* gaugePath)
{
	m_FrameHandle = LoadGraph(framePath);
	m_GaugeHandle = LoadGraph(gaugePath);

	GetGraphSize(m_GaugeHandle, &m_GaugeWidth, &m_GaugeHeight);
}

void UIGauge::Draw()
{
	VECTOR gaugePos = MyMath::VecAdd(m_Pos, m_GaugePos);
	float gaugeWidth = (float)m_GaugeWidth * (m_Value / m_MaxValue);


	DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_FrameHandle, true);
	DrawRectGraph((int)gaugePos.x, (int)gaugePos.y, 0, 0, (int)gaugeWidth, m_GaugeHeight,m_GaugeHandle, true);
}

void UIGauge::Fin()
{
	DeleteGraph(m_FrameHandle);
	DeleteGraph(m_GaugeHandle);
}

UIBase* UIGauge::Clone()
{
	UIGauge* clone = new UIGauge;
	*clone = *this;

	return clone;
}
