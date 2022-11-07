#pragma once
#include"../UnitTypeBase.h"
#include"../UnitLevel.h"
#include"Gunner_Param.h"

class Gunner:public UnitTypeBase
{
private:

	//手の位置
	DirectX::SimpleMath::Vector3 mLeftHandPos, mRightHandPos;

	//銃の回転
	float mGunAngle_Y;
	float mGunAngle_X;
	float mGunAngle_Z;

	//攻撃モーションのタイマー
	int mAttackMoveTimer;

	//Unitの向き
	float mAngle;

	//攻撃間隔
	int mAttackTimer;

	//攻撃可能かどうかのフラグ
	bool mAttackFlag;

	//敵が近くにいるかどうかのフラグ
	bool mEnemyApproachingFlag;

	//強化中のフラグ
	bool mReinforcementFlag;

	//強化のタイマー
	int mReinforcementTimer;

	//パワーアップのフラグ
	bool mPowerUpFlag;

	//エフェクトを発生させるタイマー
	int mEffectTimer;

	//一時提示中の強化のタイマー
	int mEnhanced_timer_during_pause;

	//通常アニメーションタイマー
	float mNormal_animation_timer;

	//パワーアップのレベル
	UNIT_LEVEL mPowerUpLevel;

	//Unitのレベル
	UNIT_LEVEL mLevel;

	//当たり判定
	SphereCollision mSphereCollision;

	Gunner_Param mParam;

	DirectX::SimpleMath::Vector3 mColor;

public:

	//コンストラクタ
	Gunner();
	//デストラクタ
	~Gunner();

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
	void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)override;

	//パワーアップの解除
	void Release_power_ups()override { mPowerUpLevel = UNIT_LEVEL::NONE; mPowerUpFlag = false; }

	//色の設定
	void SetColor(const DirectX::SimpleMath::Vector3& color)override { mColor = color; }

	//攻撃力
	const int GetPower()override { return GetOffensivePower() + PowerUpLevel(); }

private:

	//攻撃
	void Attack(EnemyManager* pEnemyManager, BulletManager* pBulletManager, const DirectX::SimpleMath::Vector3& pos);

	//攻撃するときのアニメーション
	void AttackAnimation();

	//レベルアップにかかる時間
	const int LevelUpTime();

	//攻撃力の設定
	const int GetOffensivePower();

	//パワーアップするレベル
	const int PowerUpLevel();
};