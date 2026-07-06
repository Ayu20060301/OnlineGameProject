#pragma once

#include "DxLib.h"

namespace MyMath
{
	// ベクトル関連の計算関数
	VECTOR VecCreate(VECTOR startPos, VECTOR endPos);
	VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	VECTOR VecScale(VECTOR vecA, float scale);
	float VecDot(VECTOR vecA, VECTOR vecB);
	float VecCross2D(VECTOR vecA, VECTOR vecB);
	VECTOR VecCross3D(VECTOR vecA, VECTOR vecB);
	float VecLong(VECTOR vec);
	VECTOR VecNormalize(VECTOR vec);
	VECTOR VecForwardZX(float rotY);
	// 行列関連の計算関数
	MATRIX MatCreate();
	MATRIX MatAdd(MATRIX matA, MATRIX matB);
	MATRIX MatSubt(MATRIX matA, MATRIX matB);
	MATRIX MatScale(MATRIX mat, float scale);
	MATRIX MatMult(MATRIX matA, MATRIX matB);
	MATRIX MatTransposition(MATRIX mat);
	MATRIX MatTranslation(VECTOR trans);
	MATRIX MatScale(VECTOR scale);
	MATRIX MatRotationPitch(float pitch);
	MATRIX MatRotationYaw(float yaw);
	MATRIX MatRotationRoll(float roll);
	VECTOR MatTransform(MATRIX transMat, VECTOR pos);
	// そのほか数学系の便利関数
	float MinF(float valueA, float valueB);
	float MaxF(float valueA, float valueB);
	float ClampF(float value, float min, float max);
	float RadianNormalize(float rad);
	float Absolute(float value);
	float GetDistance(VECTOR posA, VECTOR posB);
};

// ベクトル演算子オーバーロード
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
