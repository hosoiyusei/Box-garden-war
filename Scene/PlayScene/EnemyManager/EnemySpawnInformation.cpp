#include"pch.h"
#include"EnemySpawnInformation.h"

#include"EnemyManager.h"
#include"Enemy/EnemyLevel.h"
#include"../DoubleSpeed/DoubleSpeed.h"

//コンストラクタ
EnemySpawnInformation::EnemySpawnInformation()
	: mEnemySpawnTimer(0)
	, mSpawnInterval(120)
	, mSpawnCount(0)
	, mClear(false)
{

}

//デストラクタ
EnemySpawnInformation::~EnemySpawnInformation()
{

}

void EnemySpawnInformation::Spawn(EnemyManager* pEnemyManager)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	if(mSpawnCount>=120)
	{
		//EnemyがいなかったらCLEAR
		if (pEnemyManager->GetEnemyActive() == false)
		{
			mClear = true;
		}
	}

	//倍速の時はタイマーを加速
	for (int i = 0; i < static_cast<int>(mpDoubleSpeed.GetSpeed()); i++)
	{
		++mEnemySpawnTimer %= mSpawnInterval;

			if (mEnemySpawnTimer == 0)
			{
				break;
			}
	}
	

	//一定時間ごとに敵を出す
	if (mEnemySpawnTimer == 0)
	{
		mSpawnInterval = 120;
		mSpawnCount++;
		if (mSpawnCount <= 10)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL1);
			if (mSpawnCount == 10)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 20)
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL1);
			if (mSpawnCount == 20)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 30)
		{
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL2);
			if (mSpawnCount == 30)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 40)
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL1);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL1);
			if (mSpawnCount == 40)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 50)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL2);
			if (mSpawnCount == 50)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 60)
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL1);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL2);
			if (mSpawnCount == 60)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 70)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::Ninja, ENEMY_LEVEL::LEVEL3);
			if (mSpawnCount == 70)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount <= 80)
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL2);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::Ninja, ENEMY_LEVEL::LEVEL2);
			if (mSpawnCount == 80)
			{
				mSpawnInterval = 720;
			}
		}
		else if (mSpawnCount == 90)
		{
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL2);
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL3);
		}
		else if (mSpawnCount == 100)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL3);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL3);
		}
		else if (mSpawnCount <= 110)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL5);
		}
		else if (mSpawnCount <= 120)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL4);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL3);
		}
		else if (mSpawnCount <= 130)
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL5);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL5);
		}
	}
}