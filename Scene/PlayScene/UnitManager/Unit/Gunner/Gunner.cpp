#include"pch.h"
#include"Gunner.h"
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
Gunner::Gunner()
	: mLevel(UNIT_LEVEL::LEVEL_1)
	, mLeftHandPos()
	, mRightHandPos()
	, mGunAngle(0.0f)
	, mAttackMoveTimer(0)
	, mGunAngle2(0.0f)
	, mGunAngle3(0.0f)
	, mAngle(0.0f)
	, mAttackTimer(0)
	, mAttackFlag(false)
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
Gunner::~Gunner()
{

}

//出現したとき
void Gunner::Spawn(const Vector3& pos)
{
	//当たり判定の座標の設定
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = 0.5f;
}

//レベルの設定
void Gunner::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//エフェクトの色の設定
const Vector3 Gunner::GetEffectColor()
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
void Gunner::Update(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	AttackAnimation();

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
void Gunner::Draw(const Vector3& pos)
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

	Matrix body			//胴体
		, head			//頭
		, rightHand		//右手	
		, leftHand		//左手
		, gun;		//剣

	//ワールドの初期化
	body = Matrix::Identity;
	head = Matrix::Identity;
	rightHand = Matrix::Identity;
	leftHand = Matrix::Identity;
	gun = Matrix::Identity;

	//胴
	body = Matrix::CreateScale(0.8f);
	body *= Matrix::CreateRotationY(mAngle);
	body *= Matrix::CreateTranslation(pos);

	pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(GetEffectColor()));

	//頭
	head = Matrix::CreateScale(0.5f);
	head *= Matrix::CreateTranslation(Vector3(0.0f, 0.5f, 0.0f));
	head *= body;

	pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Colors::BurlyWood);

	//右手
	rightHand = Matrix::CreateScale(0.3f);
	rightHand *= Matrix::CreateTranslation(mRightHandPos);
	rightHand *= body;

	pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood);

	//左手
	leftHand = Matrix::CreateScale(0.3f);
	leftHand *= Matrix::CreateTranslation(mLeftHandPos);
	leftHand *= body;

	pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood);

	//銃
	gun = Matrix::CreateScale(0.45f);
	gun *= Matrix::CreateRotationY(mGunAngle);
	gun *= Matrix::CreateRotationX(mGunAngle2);
	gun *= Matrix::CreateRotationZ(mGunAngle3);
	gun *= rightHand;

	pObject.GetModel()->Draw(gun, MODEL_NAME::GUN);
}

//Unitのエフェクトの描画
void Gunner::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
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
void Gunner::PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)
{
	if (mSphereCollision.CheckHit(GetCollision) == true)
	{
		mPowerUpFlag = true;
		mPowerUpLevel = level;
	}
}

/***********************************************************************************************************************************************************/

//攻撃
void Gunner::Attack(EnemyManager* pEnemyManager, BulletManager* pBulletManager
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

			//近いEnemyの方向を向く
			mAngle = -atan2f(pos.z - EnemyPos.z, pos.x - EnemyPos.x);

			mAttackFlag = true;

			//弾を発射
			pBulletManager->Shot(pos, EnemyPos, BULLET_TYPE::SHOOTING, GetOffensivePower() + PowerUpLevel(), mLevel);

			//攻撃のSEの再生
			soundmanager.SE_Run(SOUND_SE::SE_GUN, SE_RUN::PLAY);
		}
		else
		{
			mEnemyApproachingFlag = false;
		}
	}
}

//攻撃するときのアニメーション
void Gunner::AttackAnimation()
{
	//通常
	if (mAttackFlag == false)
	{
		mAttackMoveTimer = 0;

		mLeftHandPos = Vector3(-0.3f, 0.0f, 0.5f);
		mRightHandPos = Vector3(-0.3f, -0.3f, -0.3f);
		mGunAngle = 3.14f;
		mGunAngle2 = -0.3f;
		mGunAngle3 = 0.0f;
	}
	//攻撃時
	else
	{
		if (mAttackMoveTimer == 0)
		{
			mLeftHandPos = Vector3(-0.7f, 0.0f, -0.2f);
			mRightHandPos = Vector3(0.0f, 0.0f, -0.2f);
			mGunAngle = 1.57f;
			mGunAngle2 = 0.0f;
		}
		else if (mAttackMoveTimer < 15)
		{
			mLeftHandPos.y += 0.015f;
			mGunAngle3 -= 0.02f;
		}
		else
		{
			mAttackFlag = false;
		}

		mAttackMoveTimer++;
	}
}

//レベルアップにかかる時間
const int& Gunner::LevelUpTime()
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
const int Gunner::GetOffensivePower()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return 3; break; }
		case UNIT_LEVEL::LEVEL_2: {return 6; break; }
		case UNIT_LEVEL::LEVEL_3: {return 9; break; }
		case UNIT_LEVEL::LEVEL_4: {return 12; break; }
		case UNIT_LEVEL::LEVEL_5: {return 15; break; }
		default:break;
	}
}

//パワーアップするレベル
const int& Gunner::PowerUpLevel()
{
	switch (mPowerUpLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return 1; break; }
		case UNIT_LEVEL::LEVEL_2: {return 2; break; }
		case UNIT_LEVEL::LEVEL_3: {return 3; break; }
		case UNIT_LEVEL::LEVEL_4: {return 4; break; }
		case UNIT_LEVEL::LEVEL_5: {return 500; break; }
		case UNIT_LEVEL::NONE: {return 0; break; }
		default:break;
	}
}