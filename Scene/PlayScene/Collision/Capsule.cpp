#include"pch.h"
#include"Capsule.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// カプセルとカプセルの衝突判定関数
const bool& Capsule::HitCheck_Capsule2Capsule(
	  const Capsule& capsule1
	, const Capsule& capsule2)
{

	float s, t;

	DirectX::SimpleMath::Vector3 c1, c2;

	// カプセルの中心の線分間の距離の平方を計算
	float dist2 = ClosestPtSegmentSegment(capsule1.a, capsule1.b, capsule2.a, capsule2.b, s, t, c1, c2);

	float radius = capsule1.r + capsule2.r;

	return dist2 <= radius * radius;
}

// クランプ関数

const float& Capsule::Clamp(
	  const float& n
	, const float& min
	, const float& max)
{
	if (n < min) return min;

	if (n > max) return max;

	return n;
}

// ２つの線分の最短距離の平方を返す関数
// p1: 線分1の始点 q1: 線分1の終点
// p2: 線分2の始点 q2: 線分2の終点
// s: 線分１上の最短位置を表す係数 t: 線分2上の最短位置を表す係数
// c1: 線分１上の最短距離の位置 c2: 線分2上の最短距離の位置
// 返り値: ２つの線分の最短距離の平方
const float& Capsule::ClosestPtSegmentSegment(
	  const Vector3& p1
	, const Vector3& q1
	, const Vector3& p2
	, const Vector3& q2
	, float& s
	, float& t
	, Vector3& c1
	, Vector3& c2)
{
	Vector3 d1 = q1 - p1; Vector3 d2 = q2 - p2; Vector3 r = p1 - p2;

	float a = d1.Dot(d1); float e = d2.Dot(d2); float f = d2.Dot(r);

	if (a <= FLT_EPSILON && e <= FLT_EPSILON)
	{
		s = t = 0.0f;
		c1 = p1;
		c2 = p2;
		return (c1 - c2).Dot(c1 - c2);
	}

	if (a <= FLT_EPSILON)
	{
		s = 0.0f;
		t = f / e;
		t = Clamp(t, 0.0f, 1.0f);
	}
	else
	{
		float c = d1.Dot(r);
		if (e <= FLT_EPSILON)
		{
			t = 0.0f;
			s = Clamp(-c / a, 0.0f, 1.0f);
		}
		else
		{
			float b = d1.Dot(d2);
			float denom = a * e - b * b;
			if (denom != 0.0f)
			{
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				s = 0.0f;
			}

			float tnom = (b * s + f);

			if (tnom < 0.0f)
			{
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (tnom > e)
			{
				t = 1.0f;
				s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
			else
			{
				t = tnom / e;
			}
		}
	}

	c1 = p1 + d1 * s;
	c2 = p2 + d2 * t;

	return (c1 - c2).Dot(c1 - c2);
}