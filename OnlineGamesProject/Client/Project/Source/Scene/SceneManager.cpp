#include "SceneManager.h"
#include "TitleScene.h"
#include "NetworkPlayScene.h"
#include "PlayScene.h"

SceneManager::SceneManager()
{
    m_Scenes = {};
    m_State = SCENE_STATE_NONE;
    m_NextScene = SCENE_TYPE_NONE;

    for (int i = 0; i < SCENE_STATE_MAX; i++)
    {
        m_StateFunc[i] = nullptr;
    }
}

SceneManager::~SceneManager()
{
    Fin();
}

void SceneManager::Init()
{
    //関数ポインタ配列に各関数を設定
    m_StateFunc[INIT] = &SceneManager::InitScene;
    m_StateFunc[LOAD] = &SceneManager::LoadScene;
    m_StateFunc[START] = &SceneManager::StartScene;
    m_StateFunc[LOOP] = &SceneManager::LoopScene;
    m_StateFunc[FIN] = &SceneManager::FinScene;

    //最初のシーンを生成して初期化から開始
    ChangeScene(TITLE);
}

void SceneManager::Step()
{
    //関数ポインタ配列であれば1行で状態ごとの関数を呼べる
    (this->*m_StateFunc[m_State])();
}

void SceneManager::Fin()
{
    ClearScene();
}

/// <summary>
/// 空いているシーンをすべて閉じて次のシーンへ遷移する
/// </summary>
/// <param name="type">遷移先のシーン</param>
/// <param name="fadeOutSpeed"></param>
void SceneManager::ChangeScene(SceneType type, float fadeOutSpeed)
{
    //次のシーンを設定
    m_NextScene = type;
    m_State = FIN;
}

/// <summary>
/// 一番上にシーンを追加する
/// </summary>
/// <param name="type">追加するシーン</param>
void SceneManager::AddScene(SceneType type)
{
    //終了中に追加はできない
    if (m_State == FIN) return;

    //シーンを生成して追加
    SceneBase* scene = CreateScene(type);

    scene->Init();
    scene->Load();
    scene->Start();

    m_Scenes.push_back(scene);
}

void SceneManager::InitScene()
{
    //シーンを初期化してロードへ
    for (SceneBase* scene : m_Scenes)
    {
        scene->Init();
    }

    m_State = LOAD;
}

void SceneManager::LoadScene()
{
    //ロードしてスタートへ
    for (SceneBase* scene : m_Scenes)
    {
        scene->Load();
    }
    m_State = START;
}

void SceneManager::StartScene()
{
    //スタートしてループへ
    for (SceneBase* scene : m_Scenes)
    {
        scene->Start();
    }
    m_State = LOOP;
}

void SceneManager::LoopScene()
{
    //ループ処理を順番に行う
    for (SceneBase* scene : m_Scenes)
    {
        if (!scene->IsActive()) continue;

        scene->Step();
        scene->Update();
        scene->Draw();
    }
}

void SceneManager::FinScene()
{
    //シーンを全削除
    ClearScene();

    //次のシーンを生成して配列に追加
    SceneBase* scene = CreateScene(m_NextScene);
    m_Scenes.push_back(scene);

    //初期化状態に戻す
    m_State = INIT;
}

/// <summary>
/// シーンの生成
/// </summary>
/// <param name="type">生成するシーン</param>
/// <returns></returns>
SceneBase* SceneManager::CreateScene(SceneType type)
{
    SceneBase* scene = nullptr;
    switch (type)
    {
       case TITLE:         scene = new TitleScene;   break;
       case PLAY:          scene = new PlayScene;   break;
       case NETWORK_PLAY:  scene = new NetworkPlayScene;  break;
    }

    if (scene) scene->SetActive(true);

    return scene;
}

/// <summary>
/// 配列内のシーンを全て終了&削除
/// </summary>
void SceneManager::ClearScene()
{
    for (SceneBase* scene : m_Scenes)
    {
        scene->Fin();
        delete scene;
    }

    m_Scenes.clear();
    m_Scenes.shrink_to_fit();
}
