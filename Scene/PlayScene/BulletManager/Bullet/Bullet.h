#pragma once
#include<SimpleMath.h>
#include"../../Collision/Collision.h"
#include"BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//前方宣言
class BulletTypeBase;
class EffectManager;

class Bullet
{
private:

	//弾の座標　ターゲット　進む方向
	DirectX::SimpleMath::Vector3
		mPos, mTargetPos, mVel, mInitialPos;

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

	//Actoveフラグ
	bool mActive;

	BULLET_TYPE mType;

	//弾の当たり判定
	SphereCollision mCollision;

	//弾の状態
	std::unique_ptr<BulletTypeBase> mpBulletType;

	//EffectManagerのポインタ
	EffectManager* mpEffectManager;

public:

	//コンストラクタ
	Bullet();
	//デストラクタ
	~Bullet();

	//初期化
	void Initialize(EffectManager* pEffectManager);

	//更新
	void Update();

	//描画
	void Draw();

	//弾を発射
	void Shot(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& target
		, const BULLET_TYPE& type
		, const int& power
		, const UNIT_LEVEL& level
		, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f));

	//弾が当たったとき
	const int& Hit();

	//アクティブフラグの取得
	const bool& GetActive() { return mActive; }

	//当たり判定を取得
	const SphereCollision& GetCollision() { return mCollision; }

	const BULLET_TYPE& GetBulletType() { return mType; }

	const UNIT_LEVEL& GetLevel();

private:

	//状態の設定
	void SetState(const BULLET_TYPE& type);
};