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

	//弾を発射させる
	void FireBullet(VECTOR playerPos, int playerNumber);

	//弾の生成
	Bullet& CreateBullet();

	//ネットワーク関係
	NetworkBullet& CreateNetworkBullet(int id, bool m_IsSelf);
	void SyncServerTransform(Network::ResponseBulletTransformData data);
	void DieBullet(int bulletID);

	//弾を全削除
	void Clear();

private:
	std::list<UniquePtr<Bullet>> m_Bullets;
};