#include "SpriteAnimationManager.h"
#include "SpriteAnimation.h"

SpriteAnimationManager::SpriteAnimationManager()
{
	m_Animations = {};
	m_Handles = nullptr;
}

SpriteAnimationManager::~SpriteAnimationManager()
{
	Fin();
}

void SpriteAnimationManager::Load()
{
	//シーンごとに使う分だけロード
	const int max = static_cast<int>(SpriteAnimationType::MAX);
	int* nowPtr = m_Handles = new int[max];
	const SpriteAnimationParam* param = SPRITE_ANIM_MASTER_PARAM;
	for (int i = 0; i < max; i++, nowPtr++, param++)
	{
		*nowPtr = LoadGraph(param->path);
	}
}

void SpriteAnimationManager::Step()
{
	for (SpriteAnimation* anim : m_Animations)
	{
		anim->Step();
	}
}

void SpriteAnimationManager::Draw()
{
	for (SpriteAnimation* anim : m_Animations)
	{
		anim->Draw();
	}
}

void SpriteAnimationManager::Fin()
{
	const int max = static_cast<int>(SpriteAnimationType::MAX);
	int* nowPtr = m_Handles;

	for (int i = 0; i < max; i++, nowPtr++)
	{
		DeleteGraph(*nowPtr);
	}
	delete[] m_Handles;

	for (SpriteAnimation* anim : m_Animations)
	{
		delete anim;
	}
	m_Animations.clear();
	m_Animations.shrink_to_fit();
}

SpriteAnimation* SpriteAnimationManager::Play(int id, VECTOR pos, int interval, bool isLoop)
{
	//未使用があれば使いまわす
	for (SpriteAnimation* anim : m_Animations)
	{
		if (!anim->IsActive())
		{
			anim->SetUp(m_Handles[id], &SPRITE_ANIM_MASTER_PARAM[id], pos, interval, isLoop);
			return anim;
		}
	}

	//未使用がなければ新しく作る
	SpriteAnimation* anim = new SpriteAnimation;
	anim->SetUp(m_Handles[id], &SPRITE_ANIM_MASTER_PARAM[id], pos, interval, isLoop);

	m_Animations.push_back(anim);

	return anim;
}
