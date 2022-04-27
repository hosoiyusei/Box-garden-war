#pragma once
#include"EnemyTypeBase.h"
#include"EnemyLevel.h"

class Boss :public EnemyTypeBase
{
private:

	//レベル
	ENEMY_LEVEL mLevel;

	//EnemyのHP
	int mHP;

	//鈍足状態のフラグ
	bool mSlowFootFlag;

	//鈍足状態のタイマー
	int mSlowFootTimer;

	//Enemyの速さ
	float mSpeed;

	//エフェクトのポインタ
	EffectManager* mpEffectManager;

	//プレイヤーのポインタ
	Player* mpPlayer;

public:

	//コンストラクタ
	Boss();
	//デストラクタ
	~Boss();

	//Enemyを出現させる
	void Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)override;

	//移動の速さ
	const float& Speed()override { return mSpeed; }

	//エフェクトの色の設定
	const DirectX::SimpleMath::Vector3 GetEffectColor()override { return DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f); }

	//更新
	void Update()override;

	//描画
	void Draw(const DirectX::SimpleMath::Vector3& pos, const float& angle)override;

	//エフェクトの描画
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos)override;

	//ダメージを受ける
	const bool& Damage(const DirectX::SimpleMath::Vector3& pos, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)override;

	//死んでいるかどうか
	const bool& Whetherdead() { return false; };

private:

	//鈍足状態
	void SlowFoot();

	//HPの設定
	const int& SetHP();

	//金
	const int& GetMoney();
};