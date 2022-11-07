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
class Tutorial;

class EnemyManager final
{
private:

	//残りの敵の数
	int mNumber_of_remaining_Enemy;

	//Enemyの配列
	std::vector<std::unique_ptr<Enemy>> mpEnemy;

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
		, ItemManager* pItemManager
		, Tutorial* pTutorial);

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクトの描画
	void EffectDraw();

	//Enemyの当たり判定
	void CheckHitEnemy();

	//Enemyがいるかどうか
	const bool GetEnemyActive();

	//一番近いEnemyの座標
	const DirectX::SimpleMath::Vector3 ClosestPos(
		const DirectX::SimpleMath::Vector3& pos
		, const ENEMY_TYPE& type = ENEMY_TYPE::NONE);

	//一番近いEnemyの種類
	const ENEMY_TYPE ClosestPosEnemyType(
		const DirectX::SimpleMath::Vector3& pos);

	//Enemyのスポーン
	void EnemySpawn(
		const int& startnum
		, const ENEMY_TYPE& type
		, const ENEMY_LEVEL& level);

	//敵の残りの数
	const int GetNumber_of_remaining_Enemy() { return mNumber_of_remaining_Enemy; }

	//敵の数を減らす
	void SetNumber_of_remaining_Enemy() { mNumber_of_remaining_Enemy--; }
};