#pragma once
#include<SimpleMath.h>

// カプセルの構造体
struct Capsule
{
	DirectX::SimpleMath::Vector3 mStart; // 中間部の線分の開始点
	DirectX::SimpleMath::Vector3 mEnd; // 中間部の線分の終了点

	float mRadius; // 半径

	Capsule()
		:mStart()
		, mEnd()
		, mRadius()
	{

	}

	// カプセルとカプセルの衝突判定関数
	const bool HitCheck_Capsule2Capsule(
		  const Capsule& capsule1
		, const Capsule& capsule2);

	// クランプ関数
	const float Clamp(
		  const float& n
		, const float& min
		, const float& max);

	// ２つの線分の最短距離の平方を返す関数
	// p1: 線分1の始点 q1: 線分1の終点
	// p2: 線分2の始点 q2: 線分2の終点
	// s: 線分１上の最短位置を表す係数 t: 線分2上の最短位置を表す係数
	// c1: 線分１上の最短距離の位置 c2: 線分2上の最短距離の位置
	// 返り値: ２つの線分の最短距離の平方
	const float ClosestPtSegmentSegment(
		  const DirectX::SimpleMath::Vector3& p1
		, const DirectX::SimpleMath::Vector3& q1
		, const DirectX::SimpleMath::Vector3& p2
		, const DirectX::SimpleMath::Vector3& q2
		, float& s
		, float& t
		, DirectX::SimpleMath::Vector3& c1
		, DirectX::SimpleMath::Vector3& c2);
};