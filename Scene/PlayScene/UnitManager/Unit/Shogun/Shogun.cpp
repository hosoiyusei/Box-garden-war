#include"pch.h"
#include"Shogun.h"
#include"../../../DoubleSpeed/DoubleSpeed.h"
#include"../../../EnemyManager/EnemyManager.h"
#include"../../../BulletManager/BulletManager.h"
#include"../../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�U���̊Ԋu
const int AttackInterval(120);
//���G����
const float SearchDistance(8.0f);

//���x���A�b�v�ɂ����鎞��
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

//�o�������Ƃ�
void Shogun::Spawn(const Vector3& pos)
{
	//�����蔻��̍��W�̐ݒ�
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = 1.3f;

	mLeftHandPos = Vector3(0.5f, 0.0f, 0.0f);
	mRightHandPos = Vector3(-0.5f, 0.0f, -0.0f);
}

//���x���̐ݒ�
void Shogun::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//�G�t�F�N�g�̐F�̐ݒ�
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

//�X�V
void Shogun::Update(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, const DirectX::SimpleMath::Vector3& pos)
{
	//�������łȂ���΍X�V
	if (mReinforcementFlag == false)
	{
		
	}
	else
	{
		mReinforcementTimer++;

		//�������I��������
		if (mReinforcementTimer >= LevelUpTime())
		{
			mReinforcementFlag = false;
			mReinforcementTimer = 0;

			pEffectManager->Play_2(Vector3(pos.x, pos.y - 0.3f, pos.z), GetEffectColor(), 10, TEXTURE3D::SHADOW);
		}
	}
}

//�`��
void Shogun::Draw(const Vector3& pos)
{
	//���f���̕`��
	if (mReinforcementFlag == true)
	{
		//�������͓_�ł�����
		int Reinforcement = mReinforcementTimer;
		Reinforcement %= 2;
		if (Reinforcement == 0)
		{
			return;
		}
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
	body = Matrix::CreateScale(0.8f);
	body *= Matrix::CreateRotationY(mAngle);
	body *= Matrix::CreateTranslation(pos);

	pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(GetEffectColor()));

	//��
	head = Matrix::CreateScale(0.5f);
	head *= Matrix::CreateTranslation(Vector3(0.0f, 0.5f, 0.0f));
	head *= body;

	pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Colors::BurlyWood);

	//�E��
	rightHand = Matrix::CreateScale(0.3f);
	rightHand *= Matrix::CreateTranslation(mRightHandPos);
	rightHand *= body;

	pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood);

	//����
	leftHand = Matrix::CreateScale(0.3f);
	leftHand *= Matrix::CreateTranslation(mLeftHandPos);
	leftHand *= body;

	pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood);

	//����
	Crown = Matrix::CreateScale(0.02f);
	Crown *= Matrix::CreateTranslation(Vector3(0.0f, 0.65f, 0.0f));
	Crown *= body;

	pObject.GetModel()->Draw(Crown,MODEL_NAME::CROWN);
}

//Unit�̃G�t�F�N�g�̕`��
void Shogun::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
{
	++mEffectTimer %= 60;

	if (mEffectTimer == 0)
	{
		pEffectManager->Play_3(Vector3(pos.x, pos.y - 0.5f, pos.z), Vector3(0.0f, 1.0f, 0.0f), 1, TEXTURE3D::POWER_UP_EFFECT, 0.05f, 1.0f);
	}
}

/***********************************************************************************************************************************************************/

//���x���A�b�v�ɂ����鎞��
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

//�U���͂̐ݒ�
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