#pragma once
#include"../ItemBase.h"
#include"../../../Collision/Capsule.h"
#include"../../../Collision/Collision.h"

class Pit :public ItemBase
{
private:

	DirectX::SimpleMath::Vector3 mPos;

	float mFloating;

	bool mUse;

	Capsule mCapsule;

	SphereCollision mSphereCollision;

public:

	//コンストラクタ
	Pit();
	//デストラクタ
	~Pit();

	//初期化
	void Initialize()override;

	//更新
	void Update()override;

	//描画
	void Draw()override;

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3 & pos) override;

	//Capsuleの当たり判定を返す
	const bool&  CheckHitCapsule(const Capsule& capsule)override ;

	void Use(const DirectX::SimpleMath::Vector3& pos)override;

	const SphereCollision& GetCollision() { return mSphereCollision; }

	const bool& GetUseFlag()override { return mUse; }

	void SetUseFlag()override { mUse = false; }
};