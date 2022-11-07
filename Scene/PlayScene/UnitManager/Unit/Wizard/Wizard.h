#pragma once
#include"../UnitTypeBase.h"
#include<SimpleMath.h>
#include"../UnitLevel.h"

//class Wizard :public UnitTypeBase
//{
//private:
//
//	//手の位置
//	DirectX::SimpleMath::Vector3 mLeftHandPos, mRightHandPos;
//
//	//杖の回転
//	float mWandAngle;
//
//	float mWandLight;
//
//	//攻撃モーションのタイマー
//	int mAttackMoveTimer;
//
//	//Unitの向き
//	float mAngle;
//
//	//攻撃間隔
//	int mAttackTimer;
//
//	//攻撃可能かどうかのフラグ
//	bool mAttackFlag;
//
//	//敵が近くにいるかどうかのフラグ
//	bool mEnemyApproachingFlag;
//
//	//強化中のフラグ
//	bool mReinforcementFlag;
//
//	//強化のタイマー
//	int mReinforcementTimer;
//
//	//パワーアップのフラグ
//	bool mPowerUpFlag;
//
//	//エフェクトを発生させるタイマー
//	int mEffectTimer;
//
//	//パワーアップのレベル
//	UNIT_LEVEL mPowerUpLevel;
//
//	//Unitのレベル
//	UNIT_LEVEL mLevel;
//
//	//当たり判定
//	SphereCollision mSphereCollision;
//
//public:
//
//	//コンストラクタ
//	Wizard();
//	//デストラクタ
//	~Wizard();
//
//	//出現したとき
//	void Spawn(const DirectX::SimpleMath::Vector3& pos)override;
//
//	//エフェクトの色の設定
//	const DirectX::SimpleMath::Vector3 GetEffectColor()override;
//
//	//レベルの設定
//	void SetLevel(const UNIT_LEVEL& level)override;
//
//	//更新
//	void Update(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager, const DirectX::SimpleMath::Vector3& pos)override;
//
//	//描画
//	void Draw(const DirectX::SimpleMath::Vector3& pos)override;
//
//	//Unitのエフェクトの描画
//	void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)override;
//
//	//強化中のフラグを返す
//	const bool& GetReinforcementFlag()override { return mReinforcementFlag; }
//
//	//当たり判定を返す
//	const SphereCollision& GetCollision()override { return mSphereCollision; }
//
//	//Unitのパワーアップ
//	void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)override;
//
//private:
//
//	//攻撃
//	void Attack(EnemyManager* pEnemyManager, BulletManager* pBulletManager, const DirectX::SimpleMath::Vector3& pos);
//
//	//攻撃するときのアニメーション
//	void AttackAnimation();
//
//	//レベルアップにかかる時間
//	const int& LevelUpTime();
//
//	//攻撃力の設定
//	const int GetOffensivePower();
//
//	//パワーアップするレベル
//	const int& PowerUpLevel();
//};