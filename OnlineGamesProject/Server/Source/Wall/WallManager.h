#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <vector>


class Wall;

class WallManager : public Singleton<WallManager>
{
public:
	WallManager();
	~WallManager();

public:
	void Init();
	void Step();
	void Draw();

public:
	//壁オブジェクト作成
	Wall& CreateWall();

	//壁の削除
	void ClearWalls();

	std::vector<SharedPtr<Wall>> GetWalls() { return m_Walls; }

private:
	std::vector<SharedPtr<Wall>> m_Walls;
};
