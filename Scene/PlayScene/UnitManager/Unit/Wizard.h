#pragma once
#include"../UnitTypeBase.h"
#include<SimpleMath.h>
#include"../UnitLevel.h"

class Wizard :public UnitTypeBase
{
private:

	//手の位置
	DirectX::SimpleMath::Vector3
		mLeftHandPos
		, mRightHandPos;

	//剣の回転
	float mSwordAngle;

	//攻撃モーションのタイマー
	int mAttackMoveTimer;

	//Unitのレベル
	UNIT_LEVEL mLevel;

public:

	//コンストラクタ
	Wizard();
	//デストラクタ
	~Wizard();

	//索敵距離
	const float& SetLen()override { return 1.7f; }

	//弾の発射間隔
	const int& ShotInterval()override { return 60; }

	//発射する弾の種類
	const BULLET_TYPE& SetType() override { return BULLET_TYPE::SLASHING; }

	//エフェクトの色の設定
	const DirectX::SimpleMath::Vector3 GetEffectColor()override;

	//レベルの設定
	void SetLevel(const UNIT_LEVEL& level)override;

	//攻撃力の設定
	const int GetOffensivePower()override;

	//更新
	void Update(bool& attackFlag)override;

	//描画
	void Draw(
		const float& angle
		, const DirectX::SimpleMath::Vector3& pos)override;
};