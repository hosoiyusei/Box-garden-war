#pragma once
#include"../ItemBase.h"
#include"../../../Collision/Capsule.h"
#include"../../../Collision/Collision.h"

class Money :public ItemBase
{
private:

	DirectX::SimpleMath::Vector3 mPos;

	float mFloating;

	bool mUse;

	Capsule mCapsule;

	SphereCollision mSphereCollision;

public:

	//コンストラクタ
	Money();
	//デストラクタ
	~Money();

	//初期化
	void Initialize()override;

	//更新
	void Update()override;

	//描画
	void Draw()override;

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos) override;

	//Capsuleの当たり判定を返す
	const bool& CheckHitCapsule(const Capsule& capsule)override;

	void Use(const DirectX::SimpleMath::Vector3& pos)override {};

	const SphereCollision& GetCollision()override { return mSphereCollision; }

	const bool& GetUseFlag()override { return false; }

	void SetUseFlag()override {}
};