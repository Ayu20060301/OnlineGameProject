#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <list>
#include "../Network/NetworkCommonParam.h"

class Bullet;
class NetworkBullet;
class Client;

class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	virtual ~BulletManager();

public:
	void Init(); //初期化
	void Load(); //ロード
	void Start(); //開始
	void Step(); //ステップ
	void Update(); //更新処理
	void Draw(); //描画
	void Fin(); //終了

public:

	


	//弾の生成
	Bullet& CreateBullet();

	//中央からランダム方向へ弾を大量発射
	void CreateRandomBullets(int count);

	//ネットワーク関係
	NetworkBullet& CreateNetworkBullet(int id, bool m_IsSelf,VECTOR pos,VECTOR velocity);

	//ネットワーク弾の同期
	void SyncServerBullet(const Network::BulletTransformData& data);

	//ネットワーク弾の削除
	void DestroyNetworkBullet(int id);

	//弾を全削除
	void Clear();

private:
	std::list<UniquePtr<Bullet>> m_Bullets;
};