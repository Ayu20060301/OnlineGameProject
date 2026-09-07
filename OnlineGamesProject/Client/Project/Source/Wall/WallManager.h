#pragma once
#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include "../Network/NetworkCommonParam.h"
#include <list>

class Wall;
class NetworkWall;
class Client;

/// <summary>
/// 壁オブジェクト管理クラス
/// </summary>
class WallManager : public Singleton<WallManager>
{
public:
	WallManager();
	~WallManager();

public:
	void Init(); //初期化
	void Load(); //ロード
	void Start(); //スタート
	void Step(); //ステップ
	void Update(); //更新処理
	void Draw(); //描画
	void Fin(); //終了

public:
	//壁オブジェクト作成
	Wall& CreateWall();

	//---ネットワーク関係---//

	//ネットワーク上の壁
	NetworkWall& CreateNetworkWall();

	//ネットワーク同期
	void SyncServerTransform(Network::WallTransformData data);

private:

	//生成されたオブジェクトの参照
	std::list<UniquePtr<Wall>> m_Walls;
};
