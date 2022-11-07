#pragma once
#include"EnemyTypeBase.h"
#include"EnemyLevel.h"
#include"EnemyType.h"

class ArmoredSoldier :public EnemyTypeBase
{
private:

	//レベル
	ENEMY_LEVEL mLevel;

	DirectX::SimpleMath::Vector3 mPos;

	//手の位置
	DirectX::SimpleMath::Vector3 mRightHandPos
		, mLeftHandPos;

	//槍の向き
	float mSpearAngle;

	//手の振り
	float mHandAngle;

	//EnemyのHP
	int mHP;

	//鈍足状態のタイマー
	int mSlowFootTimer;

	//燃焼時間
	int mCombustionTimer;

	//Enemyの速さ
	float mSpeed;

	//Enemyの状態
	Enemy_Status mEnemy_Status, mEnemy_Status2;

	//エフェクトのポインタ
	EffectManager* mpEffectManager;

	//プレイヤーのポインタ
	Player* mpPlayer;

	//装甲点
	bool mArmor_point;

public:

	//コンストラクタ
	ArmoredSoldier();
	//デストラクタ
	~ArmoredSoldier();

	//Enemyを出現させる
	void Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)override;

	//移動の速さ
	const float Speed()override { return mSpeed; }

	//エフェクトの色の設定
	const DirectX::SimpleMath::Vector3 GetEffectColor()override;

	//更新
	void Update()override;

	//描画
	void Draw(const DirectX::SimpleMath::Vector3& pos, const float& angle, const float& fade = 1.0f)override;

	//エフェクトの描画
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos)override;

	//ダメージを受ける
	const bool Damage(const DirectX::SimpleMath::Vector3& pos, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)override;

	//死んでいるかどうか
	const bool Whetherdead();

private:

	//鈍足状態
	void SlowFoot();

	//燃焼状態
	void Combustion();

	//HPの設定
	const int SetHP();

	//金
	const int GetMoney();

	//状態ごとの処理
	void Processingofeachstate();

	//状態ごとの処理
	void Processingofeachstate2();
};