#pragma once

#include "DxLib.h"
#include <vector>
#include "../Singleton/Singleton.h"
#include "EffectParameter.h"

class SpriteAnimation;

class SpriteAnimationManager : public Singleton<SpriteAnimationManager>
{
public:
	SpriteAnimationManager();
	~SpriteAnimationManager();

public:
	void Load();
	void Step();
	void Draw();
	void Fin();

public:
	SpriteAnimation* Play(int id, VECTOR pos, int interval, bool isLoop = false);

private:
	std::vector<SpriteAnimation*> m_Animations;
	int* m_Handles;
};
