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

/// <summary>
/// エフェクト画像をロード
/// </summary>
void SpriteAnimationManager::Load()
{
	//既にロード済みなら二重ロードしない
	if (m_Handles != nullptr) return;

	//アニメーション種類の最大数
	const int max = static_cast<int>(SpriteAnimationType::MAX);
	
	//ハンドル配列を確保
	m_Handles = new int[max];
	
	//マスターデータ
	const SpriteAnimationParam* param = SPRITE_ANIM_MASTER_PARAM;

	//画像をロード
	for (int i = 0; i < max; i++)
	{
		m_Handles[i] = LoadGraph(param[i].path);
	}
}

/// <summary>
/// 毎フレームの更新
/// </summary>
void SpriteAnimationManager::Step()
{
	for (SpriteAnimation* anim : m_Animations)
	{
		anim->Step();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void SpriteAnimationManager::Draw()
{
	for (SpriteAnimation* anim : m_Animations)
	{
		anim->Draw();
	}
}

/// <summary>
/// 終了処理
/// </summary>
void SpriteAnimationManager::Fin()
{
	if (m_Handles != nullptr)
	{
		const int max =
			static_cast<int>(SpriteAnimationType::MAX);


		for (int i = 0; i < max; i++)
		{
			// 無効なハンドルは削除しない
			if (m_Handles[i] != -1)
			{
				DeleteGraph(m_Handles[i]);
			}
		}


		delete[] m_Handles;

		m_Handles = nullptr;
	}
}

//アニメーションを再生
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
