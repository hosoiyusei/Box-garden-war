#include"pch.h"
#include"EnemySpawnInformation.h"

#include"EnemyManager.h"
#include"Enemy/EnemyLevel.h"
#include"../DoubleSpeed/DoubleSpeed.h"
#include"../Player/Player.h"
#include"../Stage/StageNum.h"
#include"../Tutorial/Tutorial.h"

//コンストラクタ
EnemySpawnInformation::EnemySpawnInformation()
	: mEnemySpawnTimer(0)
	, mSpawnInterval(120)
	, mSpawnCount(0)
	, mClear(false)
	, mpPlayer(nullptr)
	, mpTutorial(nullptr)
{

}

//初期化
void EnemySpawnInformation::Initialize(Player* pPlayer, Tutorial* pTutorial)
{
	mpPlayer = pPlayer;
	mpTutorial = pTutorial;
}

void EnemySpawnInformation::Spawn(EnemyManager* pEnemyManager)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	StageNum& setstage = StageNum::GetInstance();

	
	if (STAGE_NUM::TUTORIAL == setstage.GetStageNum())
	{
		Spawn_for_tutorial(pEnemyManager);
		return;
	}

	if (mSpawnCount >= 100)
	{
		//EnemyがいなかったらCLEAR
		if (pEnemyManager->GetEnemyActive() == false && mpPlayer->GetGameOver() == false)
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
	
	//敵出現のInterval
	int spawnintarval = 1000;

	//一定時間ごとに敵を出す
	if (mEnemySpawnTimer == 0)
	{
		mSpawnInterval = 120;
		mSpawnCount++;
		if (mSpawnCount <= 10)//10
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL1);
			if (mSpawnCount == 10)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 20)//20
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL2);
			if (mSpawnCount == 20)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 30)//30
		{
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::Ninja, ENEMY_LEVEL::LEVEL2);
			if (mSpawnCount == 30)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 40)//50
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::ArmoredSoldier, ENEMY_LEVEL::LEVEL2);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL3);
			if (mSpawnCount == 40)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 50)//60
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::ArmoredSoldier, ENEMY_LEVEL::LEVEL4);
			if (mSpawnCount == 50)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 60)//80
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL3);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL4);
			if (mSpawnCount == 60)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 70)//90
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::Ninja, ENEMY_LEVEL::LEVEL5);
			if (mSpawnCount == 70)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 80)//110
		{
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL3);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::ArmoredSoldier, ENEMY_LEVEL::LEVEL3);
			if (mSpawnCount == 80)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 90)//130
		{
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::ArmoredSoldier, ENEMY_LEVEL::LEVEL4);
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL4);
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL4);
			if (mSpawnCount == 90)
				mSpawnInterval = spawnintarval;
		}
		else if (mSpawnCount <= 100)//150
		{
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL5);
			pEnemyManager->EnemySpawn(4, ENEMY_TYPE::Ninja, ENEMY_LEVEL::LEVEL5);
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL5);
			if (mSpawnCount == 100)
				mSpawnInterval = spawnintarval;
		}
	}
}

//チュートリアル用のスポーン
void EnemySpawnInformation::Spawn_for_tutorial(EnemyManager* pEnemyManager)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	if (mSpawnCount >= 43)
	{
		//EnemyがいなかったらCLEAR
		if (pEnemyManager->GetEnemyActive() == false && mpPlayer->GetGameOver() == false)
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
		if (mSpawnCount <= 11)
		{
			if (mSpawnCount == 1)
			{
				mpDoubleSpeed.SetExecutionFlag(false);
				mpTutorial->SetmTutorial_event_number(mpTutorial->GetmTutorial_event_number() + 1);

				mSpawnCount++;
			}

			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL1);
			if (mSpawnCount == 11)
				mSpawnInterval = 720;
		}
		else if (mSpawnCount <= 22)
		{
			if (mSpawnCount == 13)
			{
				mpDoubleSpeed.SetExecutionFlag(false);
				mpTutorial->SetmTutorial_event_number(mpTutorial->GetmTutorial_event_number() + 1);
				
				mSpawnCount++;
			}
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::Witch, ENEMY_LEVEL::LEVEL1);
			if (mSpawnCount == 22)
				mSpawnInterval = 720;
		}
		else if (mSpawnCount <= 33)
		{
			if (mSpawnCount == 24)
			{
				mpDoubleSpeed.SetExecutionFlag(false);
				mpTutorial->SetmTutorial_event_number(mpTutorial->GetmTutorial_event_number() + 1);

				mSpawnCount++;
			}
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::Ninja, ENEMY_LEVEL::LEVEL1);

			if (mSpawnCount == 33)
				mSpawnInterval = 720;
		}
		else if (mSpawnCount <= 44)
		{
			if (mSpawnCount == 34)
			{
				mpDoubleSpeed.SetExecutionFlag(false);
				mpTutorial->SetmTutorial_event_number(mpTutorial->GetmTutorial_event_number() + 1);

				mSpawnCount++;
			}
			pEnemyManager->EnemySpawn(5, ENEMY_TYPE::SpearSoldier, ENEMY_LEVEL::LEVEL2);

			if (mSpawnCount == 44)
				mSpawnInterval = 720;
		}
		else if (mSpawnCount <= 55)
		{
			if (mSpawnCount == 45)
			{
				mpDoubleSpeed.SetExecutionFlag(false);
				mpTutorial->SetmTutorial_event_number(mpTutorial->GetmTutorial_event_number() + 1);

				mSpawnCount++;
			}
			pEnemyManager->EnemySpawn(3, ENEMY_TYPE::ArmoredSoldier, ENEMY_LEVEL::LEVEL1);
		}
	}
}