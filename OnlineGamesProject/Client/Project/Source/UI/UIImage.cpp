#include "DxLib.h"
#include "UIImage.h"

UIImage::UIImage()
{
	m_Handle = 0;
}


UIImage::~UIImage()
{
	Fin();
}

void UIImage::Load(const char* path)
{
	m_Handle = LoadGraph(path);
	GetGraphSize(m_Handle, &m_Width, &m_Height);
}

void UIImage::Draw()
{
	DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_Handle, true);
}

void UIImage::Fin()
{
	DeleteGraph(m_Handle);
}

UIBase* UIImage::Clone()
{
	UIImage* clone = new UIImage;
	*clone = *this;

	return clone;
}
