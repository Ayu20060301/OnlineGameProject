#include <DxLib.h>
#include "Input.h"

int Input::m_InputState = 0;
int Input::m_PrevInputState = 0;

void Input::Init()
{
    m_InputState = 0;
    m_PrevInputState = 0;
}

void Input::Update()
{
    //前回の入力は覚えておく
    m_PrevInputState = m_InputState;

    //入力状態をクリア
    m_InputState = 0;

    //入力状態をビットフラグで設定
    if (CheckHitKey(KEY_INPUT_UP))
    {
        m_InputState |= KEY_UP;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        m_InputState |= KEY_DOWN;
    }
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        m_InputState |= KEY_LEFT;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        m_InputState |= KEY_RIGHT;
    }
    if (CheckHitKey(KEY_INPUT_Z))
    {
        m_InputState |= KEY_Z;
    }
    if (CheckHitKey(KEY_INPUT_A))
    {
        m_InputState |= KEY_A;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        m_InputState |= KEY_S;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        m_InputState |= KEY_D;
    }
    if (CheckHitKey(KEY_INPUT_1))
    {
        m_InputState |= KEY_1;
    }
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        m_InputState |= KEY_ENTER;
    }
    if (CheckHitKey(KEY_INPUT_LCONTROL))
    {
        m_InputState |= KEY_CTRL_L;
    }
    if (CheckHitKey(KEY_INPUT_RCONTROL))
    {
        m_InputState |= KEY_CTRL_R;
    }
    if (CheckHitKey(KEY_INPUT_Q))
    {
        m_InputState |= KEY_Q;
    }
    if (CheckHitKey(KEY_INPUT_E))
    {
        m_InputState |= KEY_E;
    }
    if (CheckHitKey(KEY_INPUT_X))
    {
        m_InputState |= KEY_X;
    }

}

void Input::Draw()
{
}

void Input::Fin()
{
}

/// <summary>
/// キー入力判定
/// </summary>
/// <param name="key">指定したキー</param>
/// <returns></returns>
bool Input::IsInputKey(InputKey key)
{
    return m_InputState & key;;
}

/// <summary>
/// キー押した瞬間判定
/// </summary>
/// <param name="key">指定したキー</param>
/// <returns></returns>
bool Input::IsTriggerKey(InputKey key)
{
    return (m_InputState & key) && !(m_PrevInputState & key);
}
