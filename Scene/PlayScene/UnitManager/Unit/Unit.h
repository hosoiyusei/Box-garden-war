#pragma once
#include<SimpleMath.h>
#include"UnitType.h"
#include"UnitLevel.h"
#include"../../Collision/Collision.h"

//前方宣言
class EnemyManager;
class BulletManager;
class UnitTypeBase;
class EffectManager;

class Unit
{
private:

	//座標　一番近いEnemyの座標　Enemyとの距離
	DirectX::SimpleMath::Vector3 mPos;

	//アクティブかどうかのフラグ
	bool mActive;

	//Unitの種類
	UNIT_TYPE mType;

	//Unitのレベル
	UNIT_LEVEL mLevel;

	//Enemyの管理者のポインタ
	EnemyManager* mpEnemyManager;

	//弾の管理者のポインタ
	BulletManager* mpBulletManager;

	//ユニットの状態
	std::unique_ptr<UnitTypeBase> mpUnitTypeBase;

	//エフェクトの管理者のポインタ
	EffectManager* mpEffectManager;

public:

	//コンストラクタ
	Unit();
	//デストラクタ
	~Unit();

	//初期化
	void Initialize(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager);

	//更新
	void Update();

	//描画
	void Draw();

	//Unitのエフェクトの描画
	void EffectDraw();

	//スポーン
	void Spawn(const DirectX::SimpleMath::Vector3& pos, const UNIT_TYPE& type);

	//Unitのレベルの設定
	void SetUnitLevel(const UNIT_LEVEL& level);

	//アクティブフラグの取得
	const bool& GetActive() { return mActive; }

	//ユニットの座標を取得
	const DirectX::SimpleMath::Vector3& GetPos() { return mPos; }

	//Unitの削除
	void Delete();

	//強化中のフラグを返す
	const bool& GetReinforcementFlag();

	//当たり判定を返す
	const SphereCollision& GetCollision();

	//Unitの種類を返す
	const UNIT_TYPE& GetUnitType() { return mType; }

	//Unitのレベルを返す
	const UNIT_LEVEL& GetUnitLevel() { return mLevel; }

	//Unitのパワーアップ
	void PowerUp(const SphereCollision& GetCollision,const UNIT_LEVEL& level);

private:

	//状態の設定
	void SetType(const UNIT_TYPE& type);
};