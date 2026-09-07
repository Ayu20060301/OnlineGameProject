#include "WallManager.h"
#include "Wall.h"
#include "NetworkWall.h"
#include "../Network/Client.h"

WallManager::WallManager()
{
}

WallManager::~WallManager()
{
	Fin();
}

void WallManager::Init()
{
	for (auto& wall : m_Walls)
	{
		wall->Init();
	}
}

void WallManager::Load()
{
	for (auto& wall : m_Walls)
	{
		wall->Load();
	}
}

void WallManager::Start()
{
	for (auto& wall : m_Walls)
	{
		wall->Start();
	}
}


void WallManager::Step()
{
	for (auto& wall : m_Walls)
	{
		wall->Step();
	}
}


void WallManager::Update()
{
	for (auto& wall : m_Walls)
	{
		wall->Update();
	}
}


void WallManager::Draw()
{
	for (auto& wall : m_Walls)
	{
		wall->Draw();
	}
}


void WallManager::Fin()
{
	for (auto& wall : m_Walls)
	{
		wall->Fin();
	}
}

/// <summary>
/// 壁オブジェクトの生成
/// </summary>
/// <returns>生成曽田オブジェクトを返す</returns>
Wall& WallManager::CreateWall()
{
	//生成して初期化
	UniquePtr<Wall> wall = MakeUnique<Wall>();
	wall->Init();

	//リストに追加
	m_Walls.push_back(std::move(wall));

	return *(m_Walls.back().get());
}

NetworkWall& WallManager::CreateNetworkWall()
{
	//ネットワーク壁を生成
	UniquePtr<NetworkWall> wall = MakeUnique<NetworkWall>();

	//開始処理
	wall->Start();

	//Wallリストに追加
	m_Walls.push_back(std::move(wall));

	return *static_cast<NetworkWall*>(m_Walls.back().get());
}

/// <summary>
/// サーバーから受信したトランスフォームを使用
/// </summary>
/// <param name="data">サーバーから受信したトランスフォーム</param>
void WallManager::SyncServerTransform(Network::WallTransformData data)
{
	for (auto& wall : m_Walls)
	{
		NetworkWall* nwWall = static_cast<NetworkWall*>(wall.get());

		nwWall->SetServerPosition(data.pos);
	}
}
