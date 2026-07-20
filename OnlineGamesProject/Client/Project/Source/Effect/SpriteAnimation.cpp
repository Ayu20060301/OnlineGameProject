#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation()
{
	m_IsActive = false;
	m_IsHide = false;
	m_IsLoop = false;
	m_Handle = 0;
	m_NowFrame = 0;
	m_Timer = 0;
	m_Interval = 0;
	m_Pos = {};
	m_Param = nullptr;
}

SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::Step()
{
	if (!m_IsActive) return;

	//次のコマへ進めるか
	if (m_Timer <= 0)
	{
		//次のコマへ
		m_NowFrame++;

		//タイマーリセット
		m_Timer = m_Interval;

		//全コマ表示し終わったら非アクティブ
		if (m_NowFrame >= m_Param->frameNum)
		{
			//ループするかどうか
			if (m_IsLoop)
			{
				m_NowFrame = 0;
			}
			else
			{
				m_IsActive = false;

				//これ以上処理する必要なし
				return;
			}
		}
	}

	m_Timer--;
}

void SpriteAnimation::Draw()
{
	if (!m_IsActive) return;
	if (m_IsHide) return;

	//コマの切り取り一慶さん(横1行の画像の想定)
	int frameX = m_Param->frameWidth * m_NowFrame;

	//画像から表示するコマの部分だけ描画
	DrawRectGraph((int)m_Pos.x, (int)m_Pos.y, frameX, 0, m_Param->frameWidth, m_Param->frameHeight, m_Handle, true);
}

void SpriteAnimation::SetUp(int handle, const SpriteAnimationParam* param, VECTOR pos, int interval, bool isLoop)
{
	m_IsActive = true;
	m_IsLoop = isLoop;
	m_Handle = handle;
	m_NowFrame = 0;
	m_Param = param;
	m_Pos = pos;
	m_Interval = interval;
}
