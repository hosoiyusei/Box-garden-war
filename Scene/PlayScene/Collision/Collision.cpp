#include"pch.h"
#include"Collision.h"

const bool SphereCollision::CheckHit(const SphereCollision& Collision)
{
	//2点の位置を原点からベクトルにする
	float x = Collision.mPos.x - mPos.x;
	float y = Collision.mPos.y - mPos.y;
	float z = Collision.mPos.z - mPos.z;

	//ベクトルの長さを計算
	float l = (x * x) + (y * y) + (z * z);

	//半径の合計を取得
	float circleLen = mRadius + Collision.mRadius;

	//半径の合計を2乗する(sqrtは処理が重いため使わないための処置)
	circleLen *= circleLen;

	//ベクトルが2つの円の半径より短ければ当たっている
	if (l <= circleLen)
	{
		return true;
	}

	//当たっていない
	return false;
}