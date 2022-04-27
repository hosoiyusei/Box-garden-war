#include"pch.h"
#include"Shogun.h"
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

Shogun::Shogun()
	: mLevel(UNIT_LEVEL::LEVEL_1)
	, mLeftHandPos()
	, mRightHandPos()
	, mAngle(0.0f)
	, mEnemyApproachingFlag(false)
	, mReinforcementFlag(false)
	, mReinforcementTimer(0)
	, mSphereCollision()
	, mEffectTimer(0)
{

}

Shogun::~Shogun()
{

}

//出現したとき
void Shogun::Spawn(const Vector3& pos)
{
	//当たり判定の座標の設定
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = 1.3f;

	mLeftHandPos = Vector3(0.5f, 0.0f, 0.0f);
	mRightHandPos = Vector3(-0.5f, 0.0f, -0.0f);
}

//レベルの設定
void Shogun::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//エフェクトの色の設定
const Vector3 Shogun::GetEffectColor()
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
void Shogun::Update(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	//強化中でなければ更新
	if (mReinforcementFlag == false)
	{
		
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
void Shogun::Draw(const Vector3& pos)
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
		, Crown;		//王冠

	//ワールドの初期化
	body = Matrix::Identity;
	head = Matrix::Identity;
	rightHand = Matrix::Identity;
	leftHand = Matrix::Identity;
	Crown = Matrix::Identity;

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

	//左手
	Crown = Matrix::CreateScale(0.02f);
	Crown *= Matrix::CreateTranslation(Vector3(0.0f, 0.65f, 0.0f));
	Crown *= body;

	pObject.GetModel()->Draw(Crown,MODEL_NAME::CROWN);
}

//Unitのエフェクトの描画
void Shogun::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
{
	++mEffectTimer %= 60;

	if (mEffectTimer == 0)
	{
		pEffectManager->Play_3(Vector3(pos.x, pos.y - 0.5f, pos.z), Vector3(0.0f, 1.0f, 0.0f), 1, TEXTURE3D::POWER_UP_EFFECT, 0.05f, 1.0f);
	}
}

/***********************************************************************************************************************************************************/

//レベルアップにかかる時間
const int& Shogun::LevelUpTime()
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
const int Shogun::GetOffensivePower()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return 2; break; }
		case UNIT_LEVEL::LEVEL_2: {return 4; break; }
		case UNIT_LEVEL::LEVEL_3: {return 6; break; }
		case UNIT_LEVEL::LEVEL_4: {return 8; break; }
		case UNIT_LEVEL::LEVEL_5: {return 10; break; }
		default:break;
	}
}