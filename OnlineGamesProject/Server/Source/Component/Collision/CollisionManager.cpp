#include "CollisionManager.h"
#include "CollisionParameter.h"
#include "ColliderComponent.h"
#include "../../GameObject/GameObject.h"
#include "DxLib.h"

/// <summary>
/// 描画
/// </summary>
void CollisionManager::Draw()
{
	//登録されているコライダーを描画
	for (auto col : m_Colliders)
	{
		col->Draw();
	}
}

/// <summary>
/// コライダーをマネージャーに登録
/// </summary>
/// <param name="col">登録するコライダー</param>
void CollisionManager::Register(ColliderComponent* col)
{
	//nullptrガード
	if (!col) return;

	//多重登録の防止
	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), col);

	//既に登録済みなら何もしない
	if (it != m_Colliders.end()) return;

	m_Colliders.push_back(col);
}

/// <summary>
/// 登録されたコライダーを解除
/// </summary>
/// <param name="col">解除したいコライダー</param>
void CollisionManager::Unregister(ColliderComponent* col)
{
	//nullptrガード
	if (!col) return;

	//見つけて削除
	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), col);

	if (it != m_Colliders.end())
	{
		m_Colliders.erase(it);
	}

}

/// <summary>
/// 当たり判定
/// </summary>
void CollisionManager::CheckCollision()
{
	//全コライダー総当たり
	const size_t size = m_Colliders.size();
	for (int i = 0; i < size; i++)
	{
		ColliderComponent* a = m_Colliders[i];
		if (!a->IsActive()) continue;

		for (int j = i + 1; j < size; ++j)
		{
			ColliderComponent* b = m_Colliders[j];
			if (!b->IsActive()) continue;
			CollisionResult result = a->CheckCollide(*b);

			//当たったら死亡
			if (result.isHit)
			{
				//衝突処理
				a->GetOwner()->OverlapGameObject(*b->GetOwner());
				b->GetOwner()->OverlapGameObject(*a->GetOwner());
			}
		}
	}
}
