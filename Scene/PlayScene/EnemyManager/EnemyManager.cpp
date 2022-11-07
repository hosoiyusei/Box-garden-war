#include"pch.h"
#include"EnemyManager.h"

#include"Enemy/Enemy.h"
#include"../BulletManager/BulletManager.h"
#include"EnemySpawnInformation.h"
#include"../Player/Player.h"
#include"../ItemManager/ItemManager.h"
#include"../Stage/StageNum.h"

//Enemyを作る数
const int ENEMY_NUM(170);

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
EnemyManager::EnemyManager()
	: mpEnemy()
	, mpBulletManager(nullptr)
	, mpEnemyManager(nullptr)
	, mpPlayer(nullptr)
	, mpItemManager(nullptr)
	, mNumber_of_remaining_Enemy(0)
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
	, ItemManager* pItemManager
	, Tutorial* pTutorial)
{
	//弾の管理者のポインタの取得
	mpBulletManager = pBulletManager;

	//スポーン情報のポインタの作成
	mpEnemySpawnInformation = std::make_unique<EnemySpawnInformation>();

	mpEnemySpawnInformation->Initialize(pPlayer, pTutorial);

	//Enemyの管理者のポインタの取得
	mpEnemyManager = pEnemyManager;

	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mpEnemy.push_back(std::make_unique<Enemy>());
		mpEnemy[i]->Initialize(
			pEnemyManager
			, pStageRead
			, pEffectManager
			, pPlayer
			, pItemManager);
	}

	StageNum& setstage = StageNum::GetInstance();

	if (setstage.GetStageNum() != STAGE_NUM::TUTORIAL)
	{
		mNumber_of_remaining_Enemy = 170;
	}
	else
	{
		mNumber_of_remaining_Enemy = 50;
	}
}

//更新
void EnemyManager::Update()
{
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		//アクティブだったら更新
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true ||
			mpEnemy[i]->GetDeath() == true && mpEnemy[i]->GetGoal() != true)
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
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		//アクティブだったら描画
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true||
			mpEnemy[i]->GetDeath() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->Draw();
		}
	}
}

//エフェクトの描画
void EnemyManager::EffectDraw()
{
	for (size_t i = 0; i < mpEnemy.size(); i++)
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
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true &&
			mpEnemy[i]->GetDeath() == false)
		{
			mpBulletManager->CheckHitCollision(mpEnemy[i].get());

			mpItemManager->CheckHitCollision(mpEnemy[i].get());
		}
	}
}

//Enemyがいるかどうか
const bool EnemyManager::GetEnemyActive()
{
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetDeath() == false)
		{
			return true;
		}
	}

	return false;
}

//一番近いEnemyの座標
const Vector3 EnemyManager::ClosestPos(const Vector3& pos
	, const ENEMY_TYPE& type)
{
	Vector3 len1, len2, target;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	target = Vector3(1000.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetDeath() == false)
		{
			if (mpEnemy[i]->GetEnemyType() != type)
			{
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
	}

	//一番近いEnemyの座標
	return target;
}

//一番近いEnemyの種類
const ENEMY_TYPE EnemyManager::ClosestPosEnemyType(const Vector3& pos)
{
	Vector3 len1, len2;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	//Enemyの種類
	ENEMY_TYPE target = ENEMY_TYPE::NONE;

	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetDeath() == false)
		{
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
	for (size_t i = 0; i < mpEnemy.size(); i++)
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