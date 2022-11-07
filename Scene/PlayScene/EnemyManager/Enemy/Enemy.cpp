#include"pch.h"
#include"Enemy.h"
#include"../../EffectManager/EffectManager.h"
#include"../../Player/Player.h"
#include"../../ItemManager/ItemManager.h"

#include"SpearSoldier.h"
#include"Witch.h"
#include"Ninja.h"
#include"ArmoredSoldier.h"
#include"Boss.h"
#include"../../DoubleSpeed/DoubleSpeed.h"
#include<random>
#include"../../AStar/AStar.h"
#include"../EnemyManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float Enemy_Speed(0.015f);

//コンストラクタ
Enemy::Enemy()
	: mPos()
	, mCollision()
	, mActive(false)
	, mSpeed(0.025f)
	, mpEffectManager(nullptr)
	, mDeath(false)
	, mpPlayer(nullptr)
	, mDestination()
	, mAngle(0.0f)
	, mpItemManager(nullptr)
	, mEnemyType(ENEMY_TYPE::NONE)
	, mGoal(false)
	, mRandom_height(0.0f)
	, mRandom_rotation(0.0f)
	, mRandom_rotation2(0.0f)
	, mFade_out(1.0f)
{

}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化
void Enemy::Initialize(
	EnemyManager* pEnemyManager
	, StageRead* pStageRead
	, EffectManager* pEffectManager
	, Player* pPlayer
	, ItemManager* pItemManager)
{
	// エフェクトの管理者のポインタの取得
	mpEffectManager = pEffectManager;
	mpEnemyManager = pEnemyManager;

	//Playerのポインタの取得
	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	mCollision.mPos = mPos;
	mCollision.mRadius = 0.5f;

	mpAStar = std::make_unique<AStar>();

	mpAStar->Initialize(pStageRead);
}

//更新
void Enemy::Update()
{
	if (mDeath == true)
	{
		if (mPos.y > -mRandom_height)
		{
			mPos.y -= 0.06f;
			mPos.z += mRandom_rotation;

			mPos.x += mRandom_rotation2;
			mAngle += mRandom_height * 0.01f;
		}
		else if (mFade_out > 0.0f)
		{
			mPos.y -= 0.06f;
			mPos.z += mRandom_rotation;

			mPos.x += mRandom_rotation2;
			mAngle += mRandom_height * 0.01f;

			mFade_out -= 0.01f;
		}
		else
		{
			mFade_out = 0.0f;
		}
			
		return;
	}

	//移動
	Move();

	//当たり判定の移動
	mCollision.mPos = mPos;

	//種類ごとの更新
	mpEnemyTypeBase->Update();

	mActive = mpEnemyTypeBase->Whetherdead();

	mSpeed = mpEnemyTypeBase->Speed();

	if (mActive == false)
	{
		mpEnemyManager->SetNumber_of_remaining_Enemy();
		mDeath = true;
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(0, 100);
		
		if (dist(mt) < 5)
		{
			mpItemManager->Spawn(mPos);
		}
	}
}

//描画
void Enemy::Draw()
{
	if (mFade_out != 0.0f)
		mpEnemyTypeBase->Draw(mPos, mAngle, mFade_out);
}

//エフェクトの描画
void Enemy::EffectDraw()
{
	if (mDeath == false)
		mpEnemyTypeBase->EffectDraw(mPos);
}

//Enemyのスポーン
void Enemy::Spawn(const int& startnum
	, const ENEMY_TYPE& type
	, const ENEMY_LEVEL& level)
{
	//状態の設定
	SetType(type);

	mpEnemyTypeBase->Spawn(mpEffectManager, mpPlayer, level);

	//種類ごとの更新
	mpEnemyTypeBase->Update();

	//A*で経路探索
	mPos = mpAStar->_tmain(startnum);

	mSpeed = mpEnemyTypeBase->Speed();

	//Enemyを有向化する
	mActive = true;

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(60, 80);

	mRandom_height = static_cast<float>(dist(mt)) * 0.1f;

	std::uniform_int_distribution<int> dist2(-100, 100);

	mRandom_rotation = dist2(mt) * 0.00035f;
	mRandom_rotation2 = dist2(mt) * 0.00035f;
}

//Damageの処理
void Enemy::Damage(const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL level)
{
	mpEnemyTypeBase->Damage(mPos, damage, type, level);
}

/**********************************************************************/

//Enemyを動かす
void Enemy::Move()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	if (mPos.x <= mpAStar->GetPos().mX + Enemy_Speed &&
		mPos.x >= mpAStar->GetPos().mX - Enemy_Speed &&
		mPos.z <= mpAStar->GetPos().mY + Enemy_Speed &&
		mPos.z >= mpAStar->GetPos().mY - Enemy_Speed)
	{
		mPos.x = static_cast<float>(mpAStar->GetPos().mX);
		mPos.z = static_cast<float>(mpAStar->GetPos().mY);
		mAngle = mpAStar->Move();

		//ゴールについたら消す
		if (mpAStar->CheckGoal() == true)
		{
			mActive = false;
			mDeath = true;
			mGoal = true;
			
			if (mpPlayer->GetClear() == false)
			{
				//プレイヤーにダメージを与える
				mpPlayer->LifeDamage();

				mpEnemyManager->SetNumber_of_remaining_Enemy();
			}
		}
	}
	
	if (mpAStar->GetPos().mX > mPos.x)
	{
		mPos.x += mSpeed * mpDoubleSpeed.GetSpeed();
	}
	else if (mpAStar->GetPos().mX < mPos.x)
	{
		mPos.x -= mSpeed * mpDoubleSpeed.GetSpeed();
	}
	else if (mpAStar->GetPos().mY > mPos.z)
	{
		mPos.z += mSpeed * mpDoubleSpeed.GetSpeed();
	}
	else if (mpAStar->GetPos().mY < mPos.z)
	{
		mPos.z -= mSpeed * mpDoubleSpeed.GetSpeed();
	}
}

//Enemyの種類の取得
void Enemy::SetType(const ENEMY_TYPE& type)
{
	//状態の初期化
	mpEnemyTypeBase.reset(nullptr);

	//状態の設定
	switch (type)
	{
		case ENEMY_TYPE::SpearSoldier:
		{
			mEnemyType = type;
			mpEnemyTypeBase = std::make_unique<SpearSoldier>();
			break;
		}
		case ENEMY_TYPE::Witch:
		{
			mEnemyType = type;
			mpEnemyTypeBase = std::make_unique<Witch>();
			break;
		}
		case ENEMY_TYPE::Ninja:
		{
			mEnemyType = type;
			mpEnemyTypeBase = std::make_unique<Ninja>();
			break;
		}
		case ENEMY_TYPE::ArmoredSoldier:
		{
			mEnemyType = type;
			mpEnemyTypeBase = std::make_unique<ArmoredSoldier>();
			break;
		}
		case ENEMY_TYPE::Boss:
		{
			mEnemyType = type;
			mpEnemyTypeBase = std::make_unique<Boss>();
			break;
		}
		default:
			break;
	}
}