#include"pch.h"
#include"Cannon.h"
#include"../../../DoubleSpeed/DoubleSpeed.h"
#include"../../../EnemyManager/EnemyManager.h"
#include"../../../BulletManager/BulletManager.h"
#include"../../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//攻撃の間隔
const int AttackInterval(120);
//索敵距離
const float SearchDistance(8.0f);

//レベルアップにかかる時間
const int LevelUpTime_Level_2(60);
const int LevelUpTime_Level_3(120);
const int LevelUpTime_Level_4(180);
const int LevelUpTime_Level_5(240);

//コンストラクタ
Cannon::Cannon()
	: mLevel(UNIT_LEVEL::LEVEL_1)
	, mAngle(0.0f)
	, mAttackTimer(0)
	, mEnemyApproachingFlag(false)
	, mReinforcementFlag(false)
	, mReinforcementTimer(0)
	, mSphereCollision()
	, mPowerUpLevel(UNIT_LEVEL::NONE)
	, mPowerUpFlag(false)
	, mEffectTimer(0)
{

}

//デストラクタ
Cannon::~Cannon()
{

}

//出現したとき
void Cannon::Spawn(const Vector3& pos)
{
	//当たり判定の座標の設定
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = 0.5f;
}

//レベルの設定
void Cannon::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//エフェクトの色の設定
const Vector3 Cannon::GetEffectColor()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return Vector3(0.0f, 0.0f, 1.0f); break; }
		case UNIT_LEVEL::LEVEL_2: {return Vector3(0.0f, 1.0f, 0.0f); break; }
		case UNIT_LEVEL::LEVEL_3: {return Vector3(1.0f, 0.0f, 0.0f); break; }
		case UNIT_LEVEL::LEVEL_4: {return Vector3(1.0f, 1.0f, 0.0f); break; }
		case UNIT_LEVEL::LEVEL_5: {return Vector3(1.0f, 0.5f, 0.0f); break; }
		default:break;
	}
}

//更新
void Cannon::Update(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	//強化中でなければ更新
	if (mReinforcementFlag == false)
	{
		Attack(pEnemyManager, pBulletManager, pos);
	}
	else
	{
		mReinforcementTimer++;

		//強化を終了させる
		if (mReinforcementTimer >= LevelUpTime())
		{
			mReinforcementFlag = false;
			mReinforcementTimer = 0;

			pEffectManager->Play_2(Vector3(pos.x, pos.y - 0.3f, pos.z), GetEffectColor(), 10, TEXTURE3D::SHADOW);
		}
	}
}

//描画
void Cannon::Draw(const Vector3& pos)
{
	//モデルの描画
	if (mReinforcementFlag == true)
	{
		//強化中は点滅させる
		int Reinforcement = mReinforcementTimer;
		Reinforcement %= 2;
		if (Reinforcement == 0)
		{
			return;
		}
	}

	DrawManager& pObject = DrawManager::GetInstance();

	//色の設定
	float setcolor = 0.7f;

	Matrix barrel		//砲身
		, muzzle		//銃口
		, leftWheel		//左車輪
		, rightWheel;	//右車輪

	//ワールドの初期化
	barrel = Matrix::Identity;
	muzzle = Matrix::Identity;
	leftWheel = Matrix::Identity;
	rightWheel = Matrix::Identity;

	//砲身
	barrel = Matrix::CreateScale(0.4f, 0.7f, 0.4f);
	barrel *= Matrix::CreateRotationX(1.57f);
	barrel *= Matrix::CreateRotationY(mAngle + 1.57f);
	barrel *= Matrix::CreateTranslation(pos.x, pos.y + 0.3f, pos.z);

	pObject.GetGeometry()->Draw(barrel, SHAPE::CYLINDER,Colors::Black);

	//銃口
	muzzle = Matrix::CreateScale(1.0f,0.7f,1.0f);
	muzzle *= Matrix::CreateRotationY(1.57f);
	muzzle *= Matrix::CreateTranslation(0.0f, -0.5f, 0.0f);
	muzzle *= barrel;

	pObject.GetGeometry()->DrawSetColor(muzzle, SHAPE::TORUS, Color(GetEffectColor() * setcolor));

	//左車輪
	leftWheel = Matrix::CreateScale(0.6f, 1.3f, 0.6f);
	leftWheel *= Matrix::CreateRotationY(1.57f);
	leftWheel *= Matrix::CreateRotationZ(1.57f);
	leftWheel *= Matrix::CreateTranslation(0.7f, 0.2f, 0.0f);
	leftWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(leftWheel, SHAPE::TORUS, Color(GetEffectColor() * setcolor));

	//右車輪
	rightWheel = Matrix::CreateScale(0.6f, 1.3f, 0.6f);
	rightWheel *= Matrix::CreateRotationY(1.57f);
	rightWheel *= Matrix::CreateRotationZ(1.57f);
	rightWheel *= Matrix::CreateTranslation(-0.7f, 0.2f, 0.0f);
	rightWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(rightWheel, SHAPE::TORUS, Color(GetEffectColor() * setcolor));
}

//Unitのエフェクトの描画
void Cannon::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
{
	if (mEnemyApproachingFlag == true)
	{
		DrawManager& pObject = DrawManager::GetInstance();

		//発射間隔のゲージを描画
		float length = ((static_cast<float>(AttackInterval - mAttackTimer) / static_cast<float>(AttackInterval))) * 0.8f;

		Matrix world = Matrix::Identity;
		pObject.GetTexture3D()->DrawBillboard(world);
		world *= Matrix::CreateScale(length, 0.1f, 0.1f);
		world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y + 0.7f, pos.z - 0.2f));
		pObject.GetTexture3D()->SetColor(1.0f);
		pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);
	}

	if (mPowerUpFlag == true)
	{
		++mEffectTimer %= 60;

		if (mEffectTimer == 0)
		{
			pEffectManager->Play_3(Vector3(pos.x, pos.y - 0.5f, pos.z), Vector3(0.0f, 1.0f, 0.0f), 1, TEXTURE3D::POWER_UP_EFFECT, 0.05f, 1.0f);
		}
	}
}

//Unitのパワーアップ
void Cannon::PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)
{
	if (mSphereCollision.CheckHit(GetCollision) == true)
	{
		mPowerUpFlag = true;
		mPowerUpLevel = level;
	}
}

/***********************************************************************************************************************************************************/

//攻撃
void Cannon::Attack(EnemyManager* pEnemyManager, BulletManager* pBulletManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	//敵の座標
	Vector3 EnemyPos = pEnemyManager->ClosestPos(pos);

	//Enemyとの距離を取得
	Vector3 Len = pos - EnemyPos;

	for (int i = 0; i < mpDoubleSpeed.GetSpeed(); i++)
	{
		++mAttackTimer %= AttackInterval;

		if (mAttackTimer == 0)
		{
			break;
		}
	}

	if (mAttackTimer == 0)
	{
		//敵がいなければ発射しない
		if (pEnemyManager->GetEnemyActive() == false)
		{
			mEnemyApproachingFlag = false;
			return;
		}

		//距離が近ければ発射
		if (Len.Length() <= SearchDistance)
		{
			mEnemyApproachingFlag = true;
			ENEMY_TYPE enemytype = pEnemyManager->ClosestPosEnemyType(pos);

			//近いEnemyの方向を向く
			if (enemytype != ENEMY_TYPE::Witch)//魔法使いでなければ
			{
				mAngle = -atan2f(pos.z - EnemyPos.z, pos.x - EnemyPos.x);
			}

			//弾を発射
			if (enemytype != ENEMY_TYPE::Witch)//魔法使いでなければ
			{
				pBulletManager->Shot(pos, EnemyPos, BULLET_TYPE::CANNONBALL, GetOffensivePower() + PowerUpLevel(), mLevel);

				//攻撃のSEの再生
				soundmanager.SE_Run(SOUND_SE::SE_CANNON, SE_RUN::PLAY);
			}
		}
		else
		{
			mEnemyApproachingFlag = false;
		}
	}
}

//レベルアップにかかる時間
const int& Cannon::LevelUpTime()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_2: {return LevelUpTime_Level_2; break; }
		case UNIT_LEVEL::LEVEL_3: {return LevelUpTime_Level_3; break; }
		case UNIT_LEVEL::LEVEL_4: {return LevelUpTime_Level_4; break; }
		case UNIT_LEVEL::LEVEL_5: {return LevelUpTime_Level_5; break; }
		default:break;
	}
}

//攻撃力の設定
const int Cannon::GetOffensivePower()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return 5; break; }
		case UNIT_LEVEL::LEVEL_2: {return 9; break; }
		case UNIT_LEVEL::LEVEL_3: {return 13; break; }
		case UNIT_LEVEL::LEVEL_4: {return 17; break; }
		case UNIT_LEVEL::LEVEL_5: {return 21; break; }
		default:break;
	}
}

//パワーアップするレベル
const int& Cannon::PowerUpLevel()
{
	switch (mPowerUpLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return 1; break; }
		case UNIT_LEVEL::LEVEL_2: {return 2; break; }
		case UNIT_LEVEL::LEVEL_3: {return 3; break; }
		case UNIT_LEVEL::LEVEL_4: {return 4; break; }
		case UNIT_LEVEL::LEVEL_5: {return 5; break; }
		case UNIT_LEVEL::NONE: {return 0; break; }
		default:break;
	}
}