#pragma once

constexpr int ITEM_WIDTH = 40;
constexpr int ITEM_HEIGHT = 40;

enum ItemID
{
	ITEM_ID_PLAYER_SPEED_UP,
	ITEM_ID_BULLET_RAPID_UP,
	ITEM_ID_BULLET_SPEED_UP,
	ITEM_ID_MAX
};


struct ItemParameter
{
	int id;
	float value;
	int animID;
};

const ItemParameter ITEM_MASTER_PARAM[ITEM_ID_MAX] =
{
	{ITEM_ID_PLAYER_SPEED_UP,1.0f,0},
	{ITEM_ID_BULLET_RAPID_UP,0.5f,1},
	{ITEM_ID_BULLET_SPEED_UP,0.5f,2},
}
