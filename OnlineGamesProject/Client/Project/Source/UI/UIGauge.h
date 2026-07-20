#pragma once
#include "UIBase.h"

class UIGauge : public UIBase
{
public:
	UIGauge();
	~UIGauge();

public:
	void Load(const char* framePath, const char* gaugePath);
	void Draw() override;
	void Fin() override;
	UIBase* Clone() override;

public:
	void SetValue(float value) { m_Value = value; }
	void SetMaxValue(float max) { m_MaxValue = max; }
	void SetGaugePos(VECTOR pos) { m_GaugePos = pos; }

private:
	int m_FrameHandle;
	int m_GaugeHandle;
	int m_GaugeWidth;
	int m_GaugeHeight;
	float m_Value;
	float m_MaxValue;
	VECTOR m_GaugePos;
};
