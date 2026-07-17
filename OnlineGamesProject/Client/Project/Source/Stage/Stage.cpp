#include "DxLib.h"
#include "Stage.h"
#include "StageParameter.h"
#include "../Block/BlockParameter.h"
#include "../GameSetting/GameSetting.h"


constexpr int STAGE_WIDTH = BLOCK_WIDTH * BLOCK_MAP_COL;
constexpr int STAGE_HEIGHT = BLOCK_HEIGHT * BLOCK_MAP_ROW;
constexpr int STAGE_POS_X = SCREEN_WIDTH * 0.5f - STAGE_WIDTH * 0.5f;
constexpr int STAGE_POS_Y = SCREEN_HEIGHT * 0.5f - STAGE_HEIGHT * 0.5f;


Stage::Stage()
{
	m_Handle = 0;
}

Stage::~Stage()
{
}

void Stage::Load()
{
}

void Stage::Draw()
{
	DrawBox((int)STAGE_POS_X, (int)STAGE_POS_Y, (int)(STAGE_POS_X + STAGE_WIDTH), (int)(STAGE_POS_X + STAGE_HEIGHT), GetColor(0, 125, 0), true);
}

void Stage::Fin()
{
}

float Stage::GetPosX()
{
	return STAGE_POS_X;
}

float Stage::GetPosY()
{
	return STAGE_POS_Y;
}
