#pragma once
#include "SceneBase.h"
#include "SceneParameter.h"
#include "../Singleton/Singleton.h"
#include <vector>


class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

public:
	void Init();
	void Update();
	void Fin();

	void ChangeScene(SceneType type, float fadeOutSpeed = 0.0f);
	void AddScene(SceneType type);

private:
	void InitScene();
    void LoadScene();
	void StartScene();
    void LoopScene();
    void FinScene();
	void FadeWait();

	SceneBase* CreateScene(SceneType type);
	void ClearScene();

private:
	//現在動いているシーン
	std::vector<SceneBase*> m_Scenes;

	//現在の状態
	SceneState m_State;

	//次に遷移するシーン
	SceneType m_NextScene;

	//状態ごとの関数を呼ぶ関数ポインタ配列
	void (SceneManager::* m_StateFunc[SCENE_STATE_MAX])(void);

	//フェードアウトの速度
	float m_FadeOutSpeed;
};
