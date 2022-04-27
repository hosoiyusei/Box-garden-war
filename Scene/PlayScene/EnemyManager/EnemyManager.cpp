#include"pch.h"
#include"EnemyManager.h"

#include"Enemy/Enemy.h"
#include"../BulletManager/BulletManager.h"
#include"EnemySpawnInformation.h"
#include"../Player/Player.h"
#include"../ItemManager/ItemManager.h"

//Enemyを作る数
const int ENEMY_NUM(500);

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
EnemyManager::EnemyManager()
	: mpEnemy()
	, mpBulletManager(nullptr)
	, mEnemyActive(false)
	, mpEnemyManager(nullptr)
	, mpPlayer(nullptr)
{

}

//デストラクタ
EnemyManager::~EnemyManager()
{

}

//初期化
void EnemyManager::Initialize(
	StageRead* pStageRead
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, EnemyManager* pEnemyManager
	, Player* pPlayer
, ItemManager* pItemManager)
{
	//弾の管理者のポインタの取得
	mpBulletManager = pBulletManager;

	//スポーン情報のポインタの作成
	mpEnemySpawnInformation = std::make_unique<EnemySpawnInformation>();

	//Enemyの管理者のポインタの取得
	mpEnemyManager = pEnemyManager;

	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mpEnemy.push_back(std::make_unique<Enemy>());
		mpEnemy[i]->Initialize(
			pStageRead
			, pEffectManager
			, pPlayer
			, pItemManager);
	}
}

//更新
void EnemyManager::Update()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//アクティブだったら更新
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->Update();
		}
	}

	mpEnemySpawnInformation->Spawn(mpEnemyManager);

	mpPlayer->SetClear(mpEnemySpawnInformation->GetClear());
}

//描画
void EnemyManager::Draw()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//アクティブだったら描画
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->Draw();
		}
	}
}

//エフェクトの描画
void EnemyManager::EffectDraw()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//アクティブだったら描画
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->EffectDraw();
		}
	}
}

//Enemyの当たり判定
void EnemyManager::CheckHitEnemy()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true)
		{
			mpBulletManager->CheckHitCollision(
				mpEnemy[i].get());

			mpItemManager->CheckHitCollision(mpEnemy[i].get());
		}
	}
}

//一番近いEnemyの座標
const DirectX::SimpleMath::Vector3& EnemyManager::ClosestPos(const DirectX::SimpleMath::Vector3& pos)
{
	DirectX::SimpleMath::Vector3 len1, len2, target;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	mEnemyActive = false;

	for (int i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true)
		{
			mEnemyActive = true;

			//Enemyとの距離
			len1 = pos - mpEnemy[i]->GetPos();
			if (len2.Length() > len1.Length() ||
				len2 == Vector3(0.0f, 0.0f, 0.0f))
			{
				len2 = len1;
				//一番近いEnemyの座標を取得
	 			target = mpEnemy[i]->GetPos();
			}
		}
	}

	//一番近いEnemyの座標
	return target;
}

//一番近いEnemyの種類
const ENEMY_TYPE& EnemyManager::ClosestPosEnemyType(const DirectX::SimpleMath::Vector3& pos)
{
	DirectX::SimpleMath::Vector3 len1, len2;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	//Enemyの種類
	ENEMY_TYPE target;

	mEnemyActive = false;

	for (int i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true)
		{
			mEnemyActive = true;

			//Enemyとの距離
			len1 = pos - mpEnemy[i]->GetPos();
			if (len2.Length() > len1.Length() ||
				len2 == Vector3(0.0f, 0.0f, 0.0f))
			{
				len2 = len1;
				//一番近いEnemyの座標を取得
				target = mpEnemy[i]->GetEnemyType();
			}
		}
	}

	//一番近いEnemyの座標
	return target;
}

//Enemyを呼び出す
void EnemyManager::EnemySpawn(
	const int& startnum
	, const ENEMY_TYPE& type
	, const ENEMY_LEVEL& level)
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//Enemyが使われていなかったらスポーン
		if (mpEnemy[i]->GetActive() == false &&
			mpEnemy[i]->GetDeath() == false)
		{
			mpEnemy[i]->Spawn(startnum, type, level);
			break;
		}
	}
}