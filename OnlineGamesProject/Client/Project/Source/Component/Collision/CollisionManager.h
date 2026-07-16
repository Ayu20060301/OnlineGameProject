#pragma once


#include "CollisionParameter.h"
#include "CollisionBase.h"
#include "../../Singleton/Singleton.h"
#include <vector>

// Box.hをインクルードしなくて済むように前方定義
class CollisionBase;
class CollisionAABB;
class CollisionSphere;

#define COLLISION_MAX 16

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();

public:
	void Draw();	// 描画
	void Fin();		// 終了

public:
	// 関数を呼ぶときに型指定するテンプレート
	CollisionAABB* CreateAABB();
	CollisionSphere* CreateSphere();

private:
	CollisionBase* CreateCollision(int id);

public:
	// 当たり判定のチェック
	void CheckCollision();
	void CheckPlayerAndBlock();
	void CheckPlayerAndBullet();
	void CheckPlayerAndItem();
	void CheckBlockAndBullet();

private:
	// CollisionManagerインスタンス
	static CollisionManager* m_Instance;
	// 当たり判定管理用配列
	std::vector<CollisionBase*> m_Collisions;
};
