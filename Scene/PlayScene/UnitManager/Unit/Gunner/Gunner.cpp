#include"pch.h"
#include"Gunner.h"
#include"../../../DoubleSpeed/DoubleSpeed.h"
#include"../../../EnemyManager/EnemyManager.h"
#include"../../../BulletManager/BulletManager.h"
#include"../../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Gunner::Gunner()
	: mLevel(UNIT_LEVEL::LEVEL_1)
	, mLeftHandPos()
	, mRightHandPos()
	, mGunAngle_X(0.0f)
	, mAttackMoveTimer(0)
	, mGunAngle_Y(0.0f)
	, mGunAngle_Z(0.0f)
	, mAngle(1.57f)
	, mAttackTimer(0)
	, mAttackFlag(false)
	, mEnemyApproachingFlag(false)
	, mReinforcementFlag(false)
	, mReinforcementTimer(0)
	, mSphereCollision()
	, mPowerUpLevel(UNIT_LEVEL::NONE)
	, mPowerUpFlag(false)
	, mEffectTimer(0)
	, mParam()
	, mEnhanced_timer_during_pause(0)
	, mNormal_animation_timer(0.0f)
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

	mSphereCollision.mRadius = mParam.mHit_test_size;
}

//レベルの設定
void Gunner::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
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

			pEffectManager->Play_2(Vector3(pos.x, pos.y - mParam.mShift_the_coordinates_of_the_effect, pos.z), mColor, 10, TEXTURE3D::SHADOW);
		}
	}
}

//描画
void Gunner::Draw(const Vector3& pos)
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

	Matrix body			//胴体
		, head			//頭
		, rightHand		//右手	
		, leftHand		//左手
		, gun		//剣
		, gunhat;

	//ワールドの初期化
	body = Matrix::Identity;
	head = Matrix::Identity;
	rightHand = Matrix::Identity;
	leftHand = Matrix::Identity;
	gun = Matrix::Identity;
	gunhat = Matrix::Identity;

	//胴
	body = Matrix::CreateScale(mParam.mTorso_size);
	body *= Matrix::CreateRotationY(mAngle);
	body *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.5f, pos.z));

	pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(mColor));

	//頭
	head = Matrix::CreateScale(mParam.mHead_size);
	head *= Matrix::CreateTranslation(mParam.mHead_coordinates);
	head *= body;

	pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Colors::BurlyWood);

	gunhat *= Matrix::CreateScale(0.0055f);
	gunhat *= Matrix::CreateTranslation(0.0f, 0.3f, 0.0f);
	gunhat *= Matrix::CreateRotationY(XMConvertToRadians(180.0f));
	gunhat *= head;
	pObject.GetModel()->Draw(gunhat, MODEL_NAME::GUNHAT);

	//右手
	rightHand = Matrix::CreateScale(mParam.mRight_hand_size);
	rightHand *= Matrix::CreateTranslation(mRightHandPos);
	rightHand *= body;

	pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood);

	//左手
	leftHand = Matrix::CreateScale(mParam.mLeft_hand_size);
	leftHand *= Matrix::CreateTranslation(mLeftHandPos);
	leftHand *= body;

	pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood);

	//銃
	gun = Matrix::CreateScale(mParam.mGun_size);
	gun *= Matrix::CreateRotationY(mGunAngle_Y);
	gun *= Matrix::CreateRotationX(mGunAngle_X);
	gun *= Matrix::CreateRotationZ(mGunAngle_Z);
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
		float length = ((static_cast<float>(mParam.mAttack_interval - mAttackTimer) / static_cast<float>(mParam.mAttack_interval))) * mParam.mAttack_interval_gauge_drawing;

		Matrix world = Matrix::Identity;
		pObject.GetTexture3D()->DrawBillboard(world);
		world *= Matrix::CreateScale(mParam.Attack_interval_gauge_size(length));
		world *= Matrix::CreateTranslation(mParam.Attack_interval_gauge_position(pos));
		pObject.GetTexture3D()->SetColor(mParam.mAttack_interval_gauge_color);
		pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);
	}

	//王に強化されているときのエフェクト
	if (mPowerUpFlag == true)
	{
		++mEffectTimer %= mParam.mPower_up_effect_timer;

		if (mEffectTimer == 0)
		{
			pEffectManager->Play_3(
				mParam.Effect_coordinate(pos)
				, mParam.mEffect_color_preference
				, mParam.mEffect_generation_number
				, TEXTURE3D::POWER_UP_EFFECT
				, mParam.mPower_up_effect_speed
				, mParam.mPower_up_effect_size);
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

	//一時停止中なら戻る
	if (mpDoubleSpeed.GetExecutionFlag() == false)return;

	SoundManager& soundmanager = SoundManager::GetInstance();

	//敵の座標
	Vector3 EnemyPos = pEnemyManager->ClosestPos(pos);
	pEnemyManager->GetEnemyActive();

	//Enemyとの距離を取得
	Vector3 Len = pos - EnemyPos;

	for (int i = 0; i < mpDoubleSpeed.GetSpeed(); i++)
	{
		++mAttackTimer %= mParam.mAttack_interval;

		if (mAttackTimer == mParam.mZero_got_moment_attack)
		{
			break;
		}
	}

	if (mAttackTimer == mParam.mZero_got_moment_attack)
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
		mAttackMoveTimer = mParam.mAttack_motion_timer_zero_time;
		mNormal_animation_timer += 0.1f;
		mLeftHandPos = mParam.mNormal_when_left_hand_coordinate;
		mLeftHandPos.y = mParam.mNormal_when_left_hand_coordinate.y * static_cast<float>(sin(mNormal_animation_timer) * 0.3f);
		mRightHandPos = mParam.mNormal_when_right_hand_coordinate;
		mRightHandPos.y = mParam.mNormal_when_right_hand_coordinate.y * static_cast<float>(sin(mNormal_animation_timer) * 0.3f);
		mGunAngle_Y = mParam.mGun_y_axis_rotation_angle_initial_angle;
		mGunAngle_X = mParam.mGun_x_axis_rotation_angle_initial_angle;
		mGunAngle_Z = mParam.mGun_z_axis_rotation_angle_initial_angle;
	}
	//攻撃時
	else
	{
		DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
		//一時停止中なら戻る
		if (mpDoubleSpeed.GetExecutionFlag() == false)return;

		if (mAttackMoveTimer == mParam.mAttack_motion_timer_zero_time)
		{
			mLeftHandPos = mParam.mLeft_hand_coordinate_at_attack_start;
			mRightHandPos = mParam.mRight_hand_coordinate_at_attack_start;
			mGunAngle_Y = mParam.mAttack_start_when_gun_y_axis_initial_rotation_angle;
			mGunAngle_X = mParam.mAttack_start_when_gun_x_axis_initial_rotation_angle;
		}
		else if (mAttackMoveTimer < mParam.mAttack_animation_time)
		{
			mLeftHandPos += mParam.mLeft_hand_move_at_attack;
			mGunAngle_Z -= mParam.mAttack_when_gun_z_axis_rotation;
		}
		else
		{
			mAttackFlag = false;
		}

		if (mpDoubleSpeed.GetExecutionFlag() == true)
			mAttackMoveTimer++;
	}
}

//レベルアップにかかる時間
const int Gunner::LevelUpTime()
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
const int Gunner::GetOffensivePower()
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
const int Gunner::PowerUpLevel()
{
	switch (mPowerUpLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return mParam.mAttack_power_ascend_in_power_up_1; break; }
		case UNIT_LEVEL::LEVEL_2: {return mParam.mAttack_power_ascend_in_power_up_2; break; }
		case UNIT_LEVEL::LEVEL_3: {return mParam.mAttack_power_ascend_in_power_up_3; break; }
		case UNIT_LEVEL::LEVEL_4: {return mParam.mAttack_power_ascend_in_power_up_4; break; }
		case UNIT_LEVEL::LEVEL_5: {return mParam.mAttack_power_ascend_in_power_up_5; break; }
		case  UNIT_LEVEL::NONE: {return 0; break; }
		default:break;
	}

	return 0;
}