#include"pch.h"
#include"Cannon.h"
#include"../../../DoubleSpeed/DoubleSpeed.h"
#include"../../../EnemyManager/EnemyManager.h"
#include"../../../BulletManager/BulletManager.h"
#include"../../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
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

//�f�X�g���N�^
Cannon::~Cannon()
{

}

//�o�������Ƃ�
void Cannon::Spawn(const Vector3& pos)
{
	//�����蔻��̍��W�̐ݒ�
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = mParam.mHit_test_size;
}

//���x���̐ݒ�
void Cannon::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//�X�V
void Cannon::Update(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	//�������łȂ���΍X�V
	if (mReinforcementFlag == false)
	{
		Attack(pEnemyManager, pBulletManager, pos);
	}
	else
	{
		DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

		//�ꎞ��~���Ȃ�߂�
		if (mpDoubleSpeed.GetExecutionFlag() == false)
		{
			mEnhanced_timer_during_pause++;
			return;
		}
		mEnhanced_timer_during_pause = 0;
		mReinforcementTimer++;

		//�������I��������
		if (mReinforcementTimer >= LevelUpTime())
		{
			mReinforcementFlag = false;
			mReinforcementTimer = 0;

			pEffectManager->Play_2(Vector3(pos.x, pos.y - mParam.mShift_the_coordinates_of_the_effect, pos.z), mColor, mParam.mNumber_of_effects_generated, TEXTURE3D::SHADOW);
		}
	}
}

//�`��
void Cannon::Draw(const Vector3& pos)
{
	//���f���̕`��
	if (mReinforcementFlag == true)
	{
		DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

		//�������͓_�ł�����
		int Reinforcement = mReinforcementTimer;

		//�ꎞ��~���Ȃ�߂�
		if (mpDoubleSpeed.GetExecutionFlag() == false)
		{
			Reinforcement = mEnhanced_timer_during_pause;
		}

		Reinforcement %= mParam.mBlinkinginterval;

		if (Reinforcement == 0)return;
	}

	DrawManager& pObject = DrawManager::GetInstance();

	//�F�̐ݒ�
	float setcolor = 0.7f;

	Matrix barrel		//�C�g
		, muzzle		//�e��
		, leftWheel		//���ԗ�
		, rightWheel;	//�E�ԗ�

	//���[���h�̏�����
	barrel = Matrix::Identity;
	muzzle = Matrix::Identity;
	leftWheel = Matrix::Identity;
	rightWheel = Matrix::Identity;

	//�C�g
	barrel = Matrix::CreateScale(mParam.mGun_tube_size);
	barrel *= Matrix::CreateRotationX(mParam.mGun_tube_x_axis_rotation);
	barrel *= Matrix::CreateRotationY(mAngle + mParam.mGun_tube_y_axis_rotation);
	barrel *= Matrix::CreateTranslation(pos.x, pos.y + mParam.mGun_tube_coordinate_adjustment, pos.z);

	pObject.GetGeometry()->Draw(barrel, SHAPE::CYLINDER,Colors::Black);

	//�e��
	muzzle = Matrix::CreateScale(mParam.mMuzzle_size);
	muzzle *= Matrix::CreateRotationY(mParam.mMuzzle_y_axis_rotation);
	muzzle *= Matrix::CreateTranslation(mParam.mMuzzle_coordinate);
	muzzle *= barrel;

	pObject.GetGeometry()->DrawSetColor(muzzle, SHAPE::TORUS, Color(mColor * setcolor));

	//���ԗ�
	leftWheel = Matrix::CreateScale(mParam.mWheel_size);
	leftWheel *= Matrix::CreateRotationY(mParam.mWheel_y_axis_rotation_angle);
	leftWheel *= Matrix::CreateRotationZ(mParam.mWheel_z_axis_rotation_angle);
	leftWheel *= Matrix::CreateTranslation(mParam.mLeft_wheel_coordinate);
	leftWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(leftWheel, SHAPE::TORUS, Color(mColor * setcolor));

	//�E�ԗ�
	rightWheel = Matrix::CreateScale(mParam.mWheel_size);
	rightWheel *= Matrix::CreateRotationY(mParam.mWheel_y_axis_rotation_angle);
	rightWheel *= Matrix::CreateRotationZ(mParam.mWheel_y_axis_rotation_angle);
	rightWheel *= Matrix::CreateTranslation(mParam.mRight_wheel_coordinate);
	rightWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(rightWheel, SHAPE::TORUS, Color(mColor * setcolor));
}

//Unit�̃G�t�F�N�g�̕`��
void Cannon::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
{
	if (mEnemyApproachingFlag == true)
	{
		DrawManager& pObject = DrawManager::GetInstance();

		//���ˊԊu�̃Q�[�W��`��
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

//Unit�̃p���[�A�b�v
void Cannon::PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)
{
	if (mSphereCollision.CheckHit(GetCollision) == true)
	{
		mPowerUpFlag = true;
		mPowerUpLevel = level;
	}
}

/***********************************************************************************************************************************************************/

//�U��
void Cannon::Attack(EnemyManager* pEnemyManager, BulletManager* pBulletManager
	, const Vector3& pos)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	//�ꎞ��~���Ȃ�߂�
	if (mpDoubleSpeed.GetExecutionFlag() == false)return;

	SoundManager& soundmanager = SoundManager::GetInstance();

	//�G�̍��W
	Vector3 EnemyPos = pEnemyManager->ClosestPos(pos, ENEMY_TYPE::Witch);

	//Enemy�Ƃ̋������擾
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
		//�G�����Ȃ���Δ��˂��Ȃ�
		if (pEnemyManager->GetEnemyActive() == false)
		{
			mEnemyApproachingFlag = false;
			return;
		}

		//�������߂���Δ���
		if (Len.Length() <= mParam.mAttack_range)
		{
			//�G�̂ق�������
			if (Len.Length() <= mParam.mAttack_range)
				mAngle = -atan2f(pos.z - EnemyPos.z, pos.x - EnemyPos.x);

			mEnemyApproachingFlag = true;

			//�e�𔭎�
			pBulletManager->Shot(
				pos
				, EnemyPos
				, BULLET_TYPE::CANNONBALL
				, GetOffensivePower() + PowerUpLevel()
				, mLevel
				, Color(mColor));

			//�U����SE�̍Đ�
			soundmanager.SE_Run(SOUND_SE::SE_CANNON, SE_RUN::PLAY);
		}
		else
		{
			mEnemyApproachingFlag = false;
		}
	}
}

//���x���A�b�v�ɂ����鎞��
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

//�U���͂̐ݒ�
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

//�p���[�A�b�v���郌�x��
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