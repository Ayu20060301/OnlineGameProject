#include "DxLib.h"
#include "Splite.h"

Splite::Splite()
{
	m_Handle = 0;
	m_Transform = {};
	m_Width = 0;
	m_Height = 0;
	m_CenterX = 0;
	m_CenterY = 0;
}

Splite::~Splite()
{
	Fin();
}

void Splite::Load(const char* filePath)
{
	m_Handle = LoadGraph(filePath);

	//画像サイズや中心位置設定
	GetGraphSize(m_Handle, &m_Width, &m_Height);
	m_CenterX = m_Width / 2;
	m_CenterY = m_Height / 2;

}

void Splite::Draw()
{
	if (m_Handle != 0)
	{
		const VECTOR& pos = m_Transform.GetPos();
		const VECTOR& rot = m_Transform.GetRot();
		const VECTOR& scale = m_Transform.GetScale();
		DrawRotaGraph3((int)pos.x, (int)pos.y, m_CenterX, m_CenterY, (double)scale.x, (double)scale.y, (double)rot.z, m_Handle,true);
	}
}

void Splite::Fin()
{
	if (m_Handle != 0)
	{
		DeleteGraph(m_Handle);
		m_Handle = 0;
	}
}
