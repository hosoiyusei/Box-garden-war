#pragma once
#include"../../Collision/Capsule.h"
#include"ObjectType.h"

class Object
{
private:

	//Capsuleの当たり判定
	Capsule mCapsule;

	//オブジェクトの座標
	DirectX::SimpleMath::Vector3 mPos;

	//オブジェクトの種類
	OBJECT_TYPE mType;

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

public:

	//コンストラクタ
	Object();
	//デストラクタ
	~Object();

	//初期化
	void Initialize(int stagetilenum);

	//描画
	void Draw();

	//座標の設定
	void SetPos(
		const float& x
		, const float& z);

	//オブジェクトが当たっているかどうか
	const bool& CheckHitCollision(const Capsule& playerCollision)
	{

		return mCapsule.HitCheck_Capsule2Capsule(
			mCapsule, playerCollision);
	}

	//オブジェクトの座標を返す
	const DirectX::SimpleMath::Vector3& GetPos();

	//オブジェクトの種類を返す
	const OBJECT_TYPE& GetType()
	{
		return mType;
	}
};