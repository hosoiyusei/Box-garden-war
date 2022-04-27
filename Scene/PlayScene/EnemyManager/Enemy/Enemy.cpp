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

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float Enemy_Speed(0.015);

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
{

}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化
void Enemy::Initialize(
	StageRead* pStageRead
	, EffectManager* pEffectManager
	, Player* pPlayer
	, ItemManager* pItemManager)
{
	// エフェクトの管理者のポインタの取得
	mpEffectManager = pEffectManager;

	//Playerのポインタの取得
	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	mCollision.mPos = mPos;
	mCollision.mRadius = 0.5f;

	AStar::Initialize(pStageRead);
}

//更新
void Enemy::Update()
{
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
	mpEnemyTypeBase->Draw(mPos, mAngle);
}

//エフェクトの描画
void Enemy::EffectDraw()
{
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

	//A*で経路探索
	mPos = AStar::_tmain(startnum);

	mSpeed = mpEnemyTypeBase->Speed();

	//Enemyを有向化する
	mActive = true;
}

//Damageの処理
void Enemy::Damage(const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL level)
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	mActive = mpEnemyTypeBase->Damage(mPos, damage,type,level);

	if (mActive == false)
	{
		mDeath = true;
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(0, 100);
		if (dist(mt) < 5)
		{
			mpItemManager->Spawn(mPos);
		}
	}
}

/**********************************************************************/

//Enemyを動かす
void Enemy::Move()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	if (mPos.x <= AStar::GetPos().mX + Enemy_Speed &&
		mPos.x >= AStar::GetPos().mX - Enemy_Speed &&
		mPos.z <= AStar::GetPos().mY + Enemy_Speed &&
		mPos.z >= AStar::GetPos().mY - Enemy_Speed)
	{
		mPos.x = static_cast<float>(AStar::GetPos().mX);
		mPos.z = static_cast<float>(AStar::GetPos().mY);
		mAngle = AStar::Move();

		//ゴールについたら消す
		if (AStar::CheckGoal() == true)
		{
			mActive = false;
			mDeath = true;
			mGoal = true;
			
			if (mpPlayer->GetClear() == false)
			{
				//プレイヤーにダメージを与える
				mpPlayer->LifeDamage();
			}
		}
	}
	
	if (AStar::GetPos().mX > mPos.x)
	{
		mPos.x += mSpeed * mpDoubleSpeed.GetSpeed();
	}
	else if (AStar::GetPos().mX < mPos.x)
	{
		mPos.x -= mSpeed * mpDoubleSpeed.GetSpeed();
	}
	else if (AStar::GetPos().mY > mPos.z)
	{
		mPos.z += mSpeed * mpDoubleSpeed.GetSpeed();
	}
	else if (AStar::GetPos().mY < mPos.z)
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