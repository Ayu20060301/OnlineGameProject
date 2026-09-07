#include "WallManager.h"
#include "Wall.h"

WallManager::WallManager()
{
	m_Walls = {};
}

WallManager::~WallManager()
{
}

void WallManager::Init()
{

}

void WallManager::Step()
{
	//•Ç‚Ìã‰ºˆÚ“®
	for (auto& wall : m_Walls)
	{
		wall->Step();
	}
}

void WallManager::Draw()
{
	//•Ç‚Ì•`‰æ
	for (auto& wall : m_Walls)
	{
		wall->Draw();
	}
}

Wall& WallManager::CreateWall()
{
	//¶¬‚µ‚Ä‰Šú‰»
	UniquePtr<Wall> wall = MakeUnique<Wall>();
	wall->Init();

	//ƒŠƒXƒg‚É’Ç‰Á
	m_Walls.push_back(std::move(wall));

	return *(m_Walls.back().get());
}

void WallManager::ClearWalls()
{
	m_Walls.clear();
}
