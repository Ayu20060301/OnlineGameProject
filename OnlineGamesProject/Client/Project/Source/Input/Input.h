#pragma once


/// <summary>
/// 入力ボタン定義
/// </summary>
enum InputKey
{
	KEY_UP     = (1 << 0),
	KEY_DOWN   = (1 << 1),
	KEY_LEFT   = (1 << 2),
	KEY_RIGHT  = (1 << 3),
	KEY_Z      = (1 << 4),
	KEY_A      = (1 << 5),
	KEY_W      = (1 << 6),
	KEY_S      = (1 << 7),
	KEY_D      = (1 << 8),
	KEY_1      = (1 << 9),
	KEY_ENTER  = (1 << 10),
	KEY_CTRL_L = (1 << 11),
	KEY_CTRL_R = (1 << 12),
	KEY_Q      = (1 << 13),
	KEY_E      = (1 << 14),
	KEY_X      = (1 << 15),
};

/// <summary>
/// 入力処理
/// </summary>
class Input
{
public:

	static void Init();
	static void Update();
	static void Draw();
	static void Fin();

	static bool  IsInputKey(InputKey key);  //キー入力判定
	static bool  IsTriggerKey(InputKey key);  //キー押した瞬間判定

private:
	//入力ビットフラグ
	static int m_InputState;

	//前回の入力ビット
	static int m_PrevInputState;
};
