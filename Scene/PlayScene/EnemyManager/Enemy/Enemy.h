#pragma once
#include<SimpleMath.h>
#include"../../Collision/Collision.h"
#include"../../../Utility.h"
#include"../../AStar/AStar.h"
#include"../EnemyManager.h"
#include"EnemyLevel.h"
#include"../../BulletManager/Bullet/BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//前方宣言
class StageRead;
class EnemyTypeBase;
class EffectManager;
class Player;
class ItemManager;
class AStar;
class EnemyManager;

class Enemy
{
private:

	//Enemyの当たり判定
	SphereCollision mCollision;

	//Enemyの座標
	DirectX::SimpleMath::Vector3 mPos;

	//目的地
	DirectX::SimpleMath::Vector3 mDestination;

	//アクティブフラグ
	bool mActive;

	//生きてるかどうかのフラグ
	bool mDeath;

	//Enemyのスピード
	float mSpeed;

	//Enemyの向き
	float mAngle;

	bool mGoal;

	float mRandom_height;

	float mRandom_rotation, mRandom_rotation2;
	
	float mFade_out;

	ENEMY_TYPE mEnemyType;

	//Enemyの状態
	std::unique_ptr<EnemyTypeBase> mpEnemyTypeBase;

	//エフェクトの管理者のポインタ
	EffectManager* mpEffectManager;

	//Playerのポインタ
	Player* mpPlayer;

	//アイテムの管理者のポインタ
	ItemManager* mpItemManager;

	std::unique_ptr<AStar> mpAStar;

	EnemyManager* mpEnemyManager;

public:

	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();

	//初期化
	void Initialize(
		EnemyManager* pEnemyManager
		, StageRead* pStageRead
		, EffectManager* pEffectManager
		, Player* pPlayer
		, ItemManager* pItemManager);

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクトの描画
	void EffectDraw();

	//Enemyをスポーン
	void Spawn(
		const int& startnum
		, const ENEMY_TYPE& type
		, const ENEMY_LEVEL& level);

	//Enemyの座標の取得
	const DirectX::SimpleMath::Vector3& GetPos() { return mPos; }

	//当たり判定を返す
	SphereCollision& GetCollision() { return mCollision; }

	//ダメージを受ける
	void Damage(const int& damage, const BULLET_TYPE& type,const UNIT_LEVEL level);

	//アクティブかどうかのフラグ
	const bool GetActive() { return mActive; }

	//死亡しているかどうかのフラグ
	const bool GetDeath() { return mDeath; }

	//Enemyの種類を取得
	const ENEMY_TYPE& GetEnemyType() { return mEnemyType; }

	const bool GetGoal() { return mGoal; }

private:

	//Enemyの移動
	void Move();

	//状態の設定
	void SetType(const ENEMY_TYPE& type);
};