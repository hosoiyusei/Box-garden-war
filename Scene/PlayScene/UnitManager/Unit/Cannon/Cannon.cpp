#include"pch.h"
#include"Cannon.h"
#include"../../../DoubleSpeed/DoubleSpeed.h"
#include"../../../EnemyManager/EnemyManager.h"
#include"../../../BulletManager/BulletManager.h"
#include"../../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Cannon::Cannon()
	: mLevel(UNIT_LEVEL::LEVEL_1)
	, mAngle(1.57f)
	, mAttackTimer(0)
	, mEnemyApproachingFlag(false)
	, mReinforcementFlag(false)
	, mReinforcementTimer(0)
	, mSphereCollision()
	, mPowerUpLevel(UNIT_LEVEL::NONE)
	, mPowerUpFlag(false)
	, mEffectTimer(0)
	, mEnhanced_timer_during_pause(0)
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

	mSphereCollision.mRadius = mParam.mHit_test_size;
}

//レベルの設定
void Cannon::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
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
		DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

		//一時停止中なら戻る
		if (mpDoubleSpeed.GetExecutionFlag() == false)
		{
			mEnhanced_timer_during_pause++;
			return;
		}
		mEnhanced_timer_during_pause = 0;
		mReinforcementTimer++;

		//強化を終了させる
		if (mReinforcementTimer >= LevelUpTime())
		{
			mReinforcementFlag = false;
			mReinforcementTimer = 0;

			pEffectManager->Play_2(Vector3(pos.x, pos.y - mParam.mShift_the_coordinates_of_the_effect, pos.z), mColor, mParam.mNumber_of_effects_generated, TEXTURE3D::SHADOW);
		}
	}
}

//描画
void Cannon::Draw(const Vector3& pos)
{
	//モデルの描画
	if (mReinforcementFlag == true)
	{
		DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

		//強化中は点滅させる
		int Reinforcement = mReinforcementTimer;

		//一時停止中なら戻る
		if (mpDoubleSpeed.GetExecutionFlag() == false)
		{
			Reinforcement = mEnhanced_timer_during_pause;
		}

		Reinforcement %= mParam.mBlinkinginterval;

		if (Reinforcement == 0)return;
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
	barrel = Matrix::CreateScale(mParam.mGun_tube_size);
	barrel *= Matrix::CreateRotationX(mParam.mGun_tube_x_axis_rotation);
	barrel *= Matrix::CreateRotationY(mAngle + mParam.mGun_tube_y_axis_rotation);
	barrel *= Matrix::CreateTranslation(pos.x, pos.y + mParam.mGun_tube_coordinate_adjustment, pos.z);

	pObject.GetGeometry()->Draw(barrel, SHAPE::CYLINDER,Colors::Black);

	//銃口
	muzzle = Matrix::CreateScale(mParam.mMuzzle_size);
	muzzle *= Matrix::CreateRotationY(mParam.mMuzzle_y_axis_rotation);
	muzzle *= Matrix::CreateTranslation(mParam.mMuzzle_coordinate);
	muzzle *= barrel;

	pObject.GetGeometry()->DrawSetColor(muzzle, SHAPE::TORUS, Color(mColor * setcolor));

	//左車輪
	leftWheel = Matrix::CreateScale(mParam.mWheel_size);
	leftWheel *= Matrix::CreateRotationY(mParam.mWheel_y_axis_rotation_angle);
	leftWheel *= Matrix::CreateRotationZ(mParam.mWheel_z_axis_rotation_angle);
	leftWheel *= Matrix::CreateTranslation(mParam.mLeft_wheel_coordinate);
	leftWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(leftWheel, SHAPE::TORUS, Color(mColor * setcolor));

	//右車輪
	rightWheel = Matrix::CreateScale(mParam.mWheel_size);
	rightWheel *= Matrix::CreateRotationY(mParam.mWheel_y_axis_rotation_angle);
	rightWheel *= Matrix::CreateRotationZ(mParam.mWheel_y_axis_rotation_angle);
	rightWheel *= Matrix::CreateTranslation(mParam.mRight_wheel_coordinate);
	rightWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(rightWheel, SHAPE::TORUS, Color(mColor * setcolor));
}

//Unitのエフェクトの描画
void Cannon::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
{
	if (mEnemyApproachingFlag == true)
	{
		DrawManager& pObject = DrawManager::GetInstance();

		//発射間隔のゲージを描画
		float length = ((static_cast<float>(mParam.mAttack_interval - mAttackTimer) / static_cast<float>(mParam.mAttack_interval))) * 0.8f;

		Matrix world = Matrix::Identity;
		pObject.GetTexture3D()->DrawBillboard(world);
		world *= Matrix::CreateScale(mParam.Attack_interval_gauge_size(length));
		world *= Matrix::CreateTranslation(mParam.Attack_interval_gauge_position(pos));
		pObject.GetTexture3D()->SetColor(mParam.mAttack_interval_gauge_color);
		pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);
	}

	if (mPowerUpFlag == true)
	{
		++mEffectTimer %= mParam.mPower_up_effect_timer;

		if (mEffectTimer == 0)
		{
			pEffectManager->Play_3(mParam.Effect_coordinate(pos), mParam.mEffect_color_preference, mParam.mEffect_generation_number, TEXTURE3D::POWER_UP_EFFECT, mParam.mPower_up_effect_speed, mParam.mPower_up_effect_size);
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
	, const Vector3& pos)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	//一時停止中なら戻る
	if (mpDoubleSpeed.GetExecutionFlag() == false)return;

	SoundManager& soundmanager = SoundManager::GetInstance();

	//敵の座標
	Vector3 EnemyPos = pEnemyManager->ClosestPos(pos, ENEMY_TYPE::Witch);

	//Enemyとの距離を取得
	Vector3 Len = pos - EnemyPos;

	for (int i = 0; i < mpDoubleSpeed.GetSpeed(); i++)
	{
		++mAttackTimer %= mParam.mAttack_interval;

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
		if (Len.Length() <= mParam.mAttack_range)
		{
			//敵のほうを向く
			if (Len.Length() <= mParam.mAttack_range)
				mAngle = -atan2f(pos.z - EnemyPos.z, pos.x - EnemyPos.x);

			mEnemyApproachingFlag = true;

			//弾を発射
			pBulletManager->Shot(
				pos
				, EnemyPos
				, BULLET_TYPE::CANNONBALL
				, GetOffensivePower() + PowerUpLevel()
				, mLevel
				, Color(mColor));

			//攻撃のSEの再生
			soundmanager.SE_Run(SOUND_SE::SE_CANNON, SE_RUN::PLAY);
		}
		else
		{
			mEnemyApproachingFlag = false;
		}
	}
}

//レベルアップにかかる時間
const int Cannon::LevelUpTime()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_2: {return mParam.mLevelUpTime_Level_2; break; }
		case UNIT_LEVEL::LEVEL_3: {return mParam.mLevelUpTime_Level_3; break; }
		case UNIT_LEVEL::LEVEL_4: {return mParam.mLevelUpTime_Level_4; break; }
		case UNIT_LEVEL::LEVEL_5: {return mParam.mLevelUpTime_Level_5; break; }
		default:break;
	}

	return 0;
}

//攻撃力の設定
const int Cannon::GetOffensivePower()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return mParam.mAttack_power_when_level_1; break; }
		case UNIT_LEVEL::LEVEL_2: {return mParam.mAttack_power_when_level_2; break; }
		case UNIT_LEVEL::LEVEL_3: {return mParam.mAttack_power_when_level_3; break; }
		case UNIT_LEVEL::LEVEL_4: {return mParam.mAttack_power_when_level_4; break; }
		case UNIT_LEVEL::LEVEL_5: {return mParam.mAttack_power_when_level_5; break; }
		default:break;
	}

	return 0;
}

//パワーアップするレベル
const int Cannon::PowerUpLevel()
{
	switch (mPowerUpLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return mParam.mAttack_power_ascend_in_power_up_1; break; }
		case UNIT_LEVEL::LEVEL_2: {return mParam.mAttack_power_ascend_in_power_up_2; break; }
		case UNIT_LEVEL::LEVEL_3: {return mParam.mAttack_power_ascend_in_power_up_3; break; }
		case UNIT_LEVEL::LEVEL_4: {return mParam.mAttack_power_ascend_in_power_up_4; break; }
		case UNIT_LEVEL::LEVEL_5: {return mParam.mAttack_power_ascend_in_power_up_5; break; }
		case UNIT_LEVEL::NONE: {return 0; break; }
		default:break;
	}

	return 0;
}