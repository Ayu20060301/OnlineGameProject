#pragma once

/// <summary>
/// シーンの状態
/// </summary>
enum SceneState
{
	INIT,
	LOAD,
	START,
	LOOP,
	FIN,
	SCENE_STATE_MAX,
	SCENE_STATE_NONE = -1
};


/// <summary>
/// シーンの種類
/// </summary>
enum SceneType
{
	TITLE,
	PLAY,
	NETWORK_PLAY,
	SCENE_TYPE_NONE = -1,
};
