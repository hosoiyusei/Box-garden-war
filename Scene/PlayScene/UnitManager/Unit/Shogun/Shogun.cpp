#include"pch.h"
#include"Shogun.h"
#include"../../../DoubleSpeed/DoubleSpeed.h"
#include"../../../EnemyManager/EnemyManager.h"
#include"../../../BulletManager/BulletManager.h"
#include"../../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

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
	, mNormal_animation_timer(0.0f)
	, mEnhanced_timer_during_pause(0)
{

}

Shogun::~Shogun()
{

}

//�o�������Ƃ�
void Shogun::Spawn(const Vector3& pos)
{
	//�����蔻��̍��W�̐ݒ�
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = mParam.mHit_test_size;

	mLeftHandPos = mParam.mNormal_when_left_hand_coordinate;
	mRightHandPos = mParam.mNormal_when_right_hand_coordinate;
}

//���x���̐ݒ�
void Shogun::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//�X�V
void Shogun::Update(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	UNREFERENCED_PARAMETER(pBulletManager);
	UNREFERENCED_PARAMETER(pEnemyManager);

	//�������łȂ���΍X�V
	if (mReinforcementFlag == true)
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
void Shogun::Draw(const Vector3& pos)
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

	Matrix body			//����
		, head			//��
		, rightHand		//�E��	
		, leftHand		//����
		, Crown;		//����

	//���[���h�̏�����
	body = Matrix::Identity;
	head = Matrix::Identity;
	rightHand = Matrix::Identity;
	leftHand = Matrix::Identity;
	Crown = Matrix::Identity;

	//��
	body = Matrix::CreateScale(mParam.mTorso_size);
	body *= Matrix::CreateRotationY(mAngle);
	body *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.5f, pos.z));

	pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(mColor));

	//��
	head = Matrix::CreateScale(mParam.mHead_size);
	head *= Matrix::CreateTranslation(mParam.mHead_coordinates);
	head *= body;

	pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Colors::BurlyWood);

	//�E��
	rightHand = Matrix::CreateScale(mParam.mRight_hand_size);
	rightHand *= Matrix::CreateTranslation(mRightHandPos);
	rightHand *= body;

	pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood);

	//����
	leftHand = Matrix::CreateScale(mParam.mLeft_hand_size);
	leftHand *= Matrix::CreateTranslation(mLeftHandPos);
	leftHand *= body;

	pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood);

	//����
	Crown = Matrix::CreateScale(mParam.mCrown_size��);
	Crown *= Matrix::CreateTranslation(mParam.mCrown_coordinate);
	Crown *= body;
	
	pObject.GetModel()->Draw(Crown,MODEL_NAME::CROWN);
}

//Unit�̃G�t�F�N�g�̕`��
void Shogun::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
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

/***********************************************************************************************************************************************************/

//���x���A�b�v�ɂ����鎞��
const int Shogun::LevelUpTime()
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
const int Shogun::GetOffensivePower()
{
	return 0;
}

void Shogun::Normal_animation()
{
	mNormal_animation_timer += 0.1f;
	mLeftHandPos = mParam.mNormal_when_left_hand_coordinate;
	mLeftHandPos.y = mParam.mNormal_when_left_hand_coordinate.y * static_cast<float>(sin(mNormal_animation_timer) * 0.3f);
	mRightHandPos = mParam.mNormal_when_right_hand_coordinate;
	mRightHandPos.y = mParam.mNormal_when_right_hand_coordinate.y * static_cast<float>(sin(mNormal_animation_timer) * 0.3f);
}