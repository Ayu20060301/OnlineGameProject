#pragma once

#include "DxLib.h"

class MyMath
{
public:
	// ベクトル関連の計算関数
	static VECTOR VecCreate(VECTOR startPos, VECTOR endPos);
	static VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	static VECTOR VecScale(VECTOR vecA, float scale);
	static float VecDot(VECTOR vecA, VECTOR vecB);
	static float VecCross2D(VECTOR vecA, VECTOR vecB);
	static VECTOR VecCross3D(VECTOR vecA, VECTOR vecB);
	static float VecLong(VECTOR vec);
	static VECTOR VecNormalize(VECTOR vec);
	static VECTOR VecForwardZX(float rotY);
	// 行列関連の計算関数
	static MATRIX MatCreate();
	static MATRIX MatAdd(MATRIX matA, MATRIX matB);
	static MATRIX MatSubt(MATRIX matA, MATRIX matB);
	static MATRIX MatScale(MATRIX mat, float scale);
	static MATRIX MatMult(MATRIX matA, MATRIX matB);
	static MATRIX MatTransposition(MATRIX mat);
	static MATRIX MatTranslation(VECTOR trans);
	static MATRIX MatScale(VECTOR scale);
	static MATRIX MatRotationPitch(float pitch);
	static MATRIX MatRotationYaw(float pitch);
	static MATRIX MatRotationRoll(float pitch);
	static VECTOR MatTransform(MATRIX transMat, VECTOR pos);
	// そのほか数学系の便利関数
	static float MinF(float valueA, float valueB);
	static float MaxF(float valueA, float valueB);
	static float ClampF(float value, float min, float max);
	static float RadianNormalize(float rad);
	static float Absolute(float value);
	static float GetDistance(VECTOR posA, VECTOR posB);
};


//ベクトル演算子オーバーロード
inline VECTOR operator+(const VECTOR& vecA, const VECTOR& vecB)
{
	return MyMath::VecAdd(vecA, vecB);
}
inline VECTOR operator-(const VECTOR& vecA, const VECTOR& vecB)
{
	return MyMath::VecCreate(vecB, vecA);
}
inline VECTOR operator*(const VECTOR& v, const float& s)
{
	return MyMath::VecScale(v, s);
}
inline VECTOR operator/(const VECTOR& v, const float& s)
{
	return MyMath::VecScale(v, 1.0f / s);
}

inline VECTOR& operator+=(VECTOR& vecA, const VECTOR& vecB)
{
	vecA = MyMath::VecAdd(vecA, vecB);
	return vecA;
}
inline VECTOR& operator-=(VECTOR& vecA, const VECTOR& vecB)
{
	vecA = MyMath::VecCreate(vecB, vecA);
	return vecA;
}
inline VECTOR& operator*=(VECTOR& v, const float& s)
{
	v = MyMath::VecScale(v, s);
	return v;
}
inline VECTOR& operator/=(VECTOR& v, const float& s)
{
	v = MyMath::VecScale(v, 1.0f / s);
	return v;
}
