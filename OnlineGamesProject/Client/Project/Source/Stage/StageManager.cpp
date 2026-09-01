#include "DxLib.h"
#include "StageManager.h"
#include "Stage.h"
#include "../MyMath/MyMath.h"

StageManager::StageManager()
{
	m_Stage = nullptr;
}

StageManager::~StageManager()
{
	Fin();
}

void StageManager::Load()
{
	if (m_Stage == nullptr) return;

	m_Stage->Load();
}

void StageManager::Draw()
{
	if (m_Stage == nullptr) return;

	m_Stage->Draw();
}

void StageManager::Fin()
{
	if (m_Stage == nullptr) return;

	m_Stage->Fin();
	delete m_Stage;
	m_Stage = nullptr;
}

/// <summary>
/// ステージのローカル座標をワールド座標に変換する
/// </summary>
/// <param name="pos">ステージのローカル座標</param>
/// <returns>ワールド座標</returns>
VECTOR StageManager::ConvertStagePosToWorldPos(VECTOR pos)
{
	VECTOR result = {};
	Stage* stage = StageManager::GetInstance()->GetStage();
	if (!stage)
	{
		return result;
	}

	float stagePosX = stage->GetPosX();
	float stagePosY = stage->GetPosY();
	result = MyMath::VecAdd(pos, VGet(stagePosX, stagePosY, 0.0f));

	return result;
}

void StageManager::CreateStage()
{
	if (!m_Stage)
	{
		m_Stage = new Stage;
	}
}
