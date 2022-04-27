#pragma once
#include<vector>
#include"Enemy/EnemyType.h"
#include"Enemy/EnemyLevel.h"

//前方宣言
class Enemy;
class StageRead;
class BulletManager;
class EnemySpawnInformation;
class EffectManager;
class Player;
class ItemManager;

class EnemyManager final
{
private:

	//Enemyの配列
	std::vector<std::unique_ptr<Enemy>> mpEnemy;

	//Enemyがいるかどうか
	bool mEnemyActive;

	//弾の管理者のポインタ
	BulletManager* mpBulletManager;

	//スポーン情報のポインタ
	std::unique_ptr<EnemySpawnInformation> mpEnemySpawnInformation;

	//Enemyの管理者のポインタ
	EnemyManager* mpEnemyManager;

	//Playerのポインタ
	Player* mpPlayer;

	ItemManager* mpItemManager;

public:

	//コンストラクタ
	EnemyManager();
	//デストラクタ
	~EnemyManager();

	//初期化
	void Initialize(
		StageRead* pStageRead
		, BulletManager* pBulletManager
		, EffectManager* pEffectManager
		, EnemyManager* pEnemyManager
		, Player* pPlayer
		, ItemManager* pItemManager);

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクトの描画
	void EffectDraw();

	//Enemyの当たり判定
	void CheckHitEnemy();

	//Enemyがいるかどうか
	const bool& GetEnemyActive() { return mEnemyActive; }

	//一番近いEnemyの座標
	const DirectX::SimpleMath::Vector3& ClosestPos(
		const DirectX::SimpleMath::Vector3& pos);

	//一番近いEnemyの種類
	const ENEMY_TYPE& ClosestPosEnemyType(
		const DirectX::SimpleMath::Vector3& pos);

	//Enemyのスポーン
	void EnemySpawn(
		const int& startnum
		, const ENEMY_TYPE& type
		, const ENEMY_LEVEL& level);
};