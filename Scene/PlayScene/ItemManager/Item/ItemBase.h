#pragma once
#include"../../Collision/Capsule.h"
#include"../../Collision/Collision.h"

class ItemBase
{
public:

	//デストラクタ
	virtual ~ItemBase() = default;

	//初期化
	virtual void Initialize() = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//Spawn
	virtual void Spawn(const DirectX::SimpleMath::Vector3& pos) = 0;

	//Capsuleの当たり判定を返す
	virtual const bool&  CheckHitCapsule(const Capsule& capsule) = 0;

	virtual void Use(const DirectX::SimpleMath::Vector3& pos) = 0;

	virtual const SphereCollision& GetCollision() = 0;

	virtual const bool& GetUseFlag() = 0;

	virtual void SetUseFlag() = 0;
};