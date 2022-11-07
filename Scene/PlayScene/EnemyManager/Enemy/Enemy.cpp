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

//�R���X�g���N�^
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

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//������
void Enemy::Initialize(
	EnemyManager* pEnemyManager
	, StageRead* pStageRead
	, EffectManager* pEffectManager
	, Player* pPlayer
	, ItemManager* pItemManager)
{
	// �G�t�F�N�g�̊Ǘ��҂̃|�C���^�̎擾
	mpEffectManager = pEffectManager;
	mpEnemyManager = pEnemyManager;

	//Player�̃|�C���^�̎擾
	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	mCollision.mPos = mPos;
	mCollision.mRadius = 0.5f;

	mpAStar = std::make_unique<AStar>();

	mpAStar->Initialize(pStageRead);
}

//�X�V
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

	//�ړ�
	Move();

	//�����蔻��̈ړ�
	mCollision.mPos = mPos;

	//��ނ��Ƃ̍X�V
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

//�`��
void Enemy::Draw()
{
	if (mFade_out != 0.0f)
		mpEnemyTypeBase->Draw(mPos, mAngle, mFade_out);
}

//�G�t�F�N�g�̕`��
void Enemy::EffectDraw()
{
	if (mDeath == false)
		mpEnemyTypeBase->EffectDraw(mPos);
}

//Enemy�̃X�|�[��
void Enemy::Spawn(const int& startnum
	, const ENEMY_TYPE& type
	, const ENEMY_LEVEL& level)
{
	//��Ԃ̐ݒ�
	SetType(type);

	mpEnemyTypeBase->Spawn(mpEffectManager, mpPlayer, level);

	//��ނ��Ƃ̍X�V
	mpEnemyTypeBase->Update();

	//A*�Ōo�H�T��
	mPos = mpAStar->_tmain(startnum);

	mSpeed = mpEnemyTypeBase->Speed();

	//Enemy��L��������
	mActive = true;

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(60, 80);

	mRandom_height = static_cast<float>(dist(mt)) * 0.1f;

	std::uniform_int_distribution<int> dist2(-100, 100);

	mRandom_rotation = dist2(mt) * 0.00035f;
	mRandom_rotation2 = dist2(mt) * 0.00035f;
}

//Damage�̏���
void Enemy::Damage(const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL level)
{
	mpEnemyTypeBase->Damage(mPos, damage, type, level);
}

/**********************************************************************/

//Enemy�𓮂���
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

		//�S�[���ɂ��������
		if (mpAStar->CheckGoal() == true)
		{
			mActive = false;
			mDeath = true;
			mGoal = true;
			
			if (mpPlayer->GetClear() == false)
			{
				//�v���C���[�Ƀ_���[�W��^����
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

//Enemy�̎�ނ̎擾
void Enemy::SetType(const ENEMY_TYPE& type)
{
	//��Ԃ̏�����
	mpEnemyTypeBase.reset(nullptr);

	//��Ԃ̐ݒ�
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