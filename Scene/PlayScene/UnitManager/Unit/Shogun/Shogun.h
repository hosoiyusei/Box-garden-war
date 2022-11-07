#pragma once
#include"../UnitTypeBase.h"
#include"../UnitLevel.h"
#include"Shogun_Param.h"

class Shogun :public UnitTypeBase
{
private:

	//手の位置
	DirectX::SimpleMath::Vector3 mLeftHandPos, mRightHandPos;

	//Unitの向き
	float mAngle;

	//敵が近くにいるかどうかのフラグ
	bool mEnemyApproachingFlag;

	//強化中のフラグ
	bool mReinforcementFlag;

	//強化のタイマー
	int mReinforcementTimer;

	//エフェクトを発生させるタイマー
	int mEffectTimer;

	//一時提示中の強化のタイマー
	int mEnhanced_timer_during_pause;

	//通常アニメーションタイマー
	float mNormal_animation_timer;

	//Unitのレベル
	UNIT_LEVEL mLevel;

	//当たり判定
	SphereCollision mSphereCollision;

	DirectX::SimpleMath::Vector3 mColor;

	Shogun_Param mParam;

public:

	//コンストラクタ
	Shogun();
	//デストラクタ
	~Shogun();

	//出現したとき
	void Spawn(const DirectX::SimpleMath::Vector3& pos)override;

	//レベルの設定
	void SetLevel(const UNIT_LEVEL& mlevel)override;

	//更新
	void Update(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager, const DirectX::SimpleMath::Vector3& pos)override;

	//描画
	void Draw(const DirectX::SimpleMath::Vector3& pos)override;

	//Unitのエフェクトの描画
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)override;

	//強化中のフラグを返す
	const bool GetReinforcementFlag()override { return mReinforcementFlag; }

	//当たり判定を返す
	const SphereCollision& GetCollision()override { return mSphereCollision; }

	//Unitのパワーアップ
	void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)override {
		UNREFERENCED_PARAMETER(GetCollision); UNREFERENCED_PARAMETER(level);
	};

	//パワーアップの解除
	void Release_power_ups()override {}

	//色の設定
	void SetColor(const DirectX::SimpleMath::Vector3& color)override { mColor = color; }

	//攻撃力
	const int GetPower()override { return 0; }

private:

	//レベルアップにかかる時間
	const int LevelUpTime();

	//攻撃力の設定
	const int GetOffensivePower();

	void Normal_animation();
};