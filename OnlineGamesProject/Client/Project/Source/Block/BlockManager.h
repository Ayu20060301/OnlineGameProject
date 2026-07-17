#pragma once

#include "DxLib.h"
#include <vector>
#include <list>
#include "../Singleton/Singleton.h"

class Block;

class BlockManager : public Singleton<BlockManager>
{
public:
	BlockManager();
	~BlockManager();

public:
	void Init();   //初期化
	void Load();   //ロード
	void Start();  //開始
	void Draw();   //描画
	void Fin();    //終了

public:
	Block* CreateBlock();
	std::vector<Block*> GetBlocks() { return m_Blocks; }

private:

	//vectorのオブジェクトプールで管理
	std::vector<Block*> m_Blocks;
	
	//クローン元のブロック
	Block* m_OriginalBlock;
};
