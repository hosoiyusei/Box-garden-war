#include"pch.h"
#include"Cannon.h"
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

//�R���X�g���N�^
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

//�f�X�g���N�^
Cannon::~Cannon()
{

}

//�o�������Ƃ�
void Cannon::Spawn(const Vector3& pos)
{
	//�����蔻��̍��W�̐ݒ�
	mSphereCollision.mPos = pos;

	mSphereCollision.mRadius = 0.5f;
}

//���x���̐ݒ�
void Cannon::SetLevel(const UNIT_LEVEL& level)
{
	mLevel = level;

	mEnemyApproachingFlag = false;
	mReinforcementFlag = true;
}

//�G�t�F�N�g�̐F�̐ݒ�
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
void Cannon::Draw(const Vector3& pos)
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
	barrel = Matrix::CreateScale(0.4f, 0.7f, 0.4f);
	barrel *= Matrix::CreateRotationX(1.57f);
	barrel *= Matrix::CreateRotationY(mAngle + 1.57f);
	barrel *= Matrix::CreateTranslation(pos.x, pos.y + 0.3f, pos.z);

	pObject.GetGeometry()->Draw(barrel, SHAPE::CYLINDER,Colors::Black);

	//�e��
	muzzle = Matrix::CreateScale(1.0f,0.7f,1.0f);
	muzzle *= Matrix::CreateRotationY(1.57f);
	muzzle *= Matrix::CreateTranslation(0.0f, -0.5f, 0.0f);
	muzzle *= barrel;

	pObject.GetGeometry()->DrawSetColor(muzzle, SHAPE::TORUS, Color(GetEffectColor() * setcolor));

	//���ԗ�
	leftWheel = Matrix::CreateScale(0.6f, 1.3f, 0.6f);
	leftWheel *= Matrix::CreateRotationY(1.57f);
	leftWheel *= Matrix::CreateRotationZ(1.57f);
	leftWheel *= Matrix::CreateTranslation(0.7f, 0.2f, 0.0f);
	leftWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(leftWheel, SHAPE::TORUS, Color(GetEffectColor() * setcolor));

	//�E�ԗ�
	rightWheel = Matrix::CreateScale(0.6f, 1.3f, 0.6f);
	rightWheel *= Matrix::CreateRotationY(1.57f);
	rightWheel *= Matrix::CreateRotationZ(1.57f);
	rightWheel *= Matrix::CreateTranslation(-0.7f, 0.2f, 0.0f);
	rightWheel *= barrel;

	pObject.GetGeometry()->DrawSetColor(rightWheel, SHAPE::TORUS, Color(GetEffectColor() * setcolor));
}

//Unit�̃G�t�F�N�g�̕`��
void Cannon::EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)
{
	if (mEnemyApproachingFlag == true)
	{
		DrawManager& pObject = DrawManager::GetInstance();

		//���ˊԊu�̃Q�[�W��`��
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
	, const DirectX::SimpleMath::Vector3& pos)
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	//�G�̍��W
	Vector3 EnemyPos = pEnemyManager->ClosestPos(pos);

	//Enemy�Ƃ̋������擾
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
		//�G�����Ȃ���Δ��˂��Ȃ�
		if (pEnemyManager->GetEnemyActive() == false)
		{
			mEnemyApproachingFlag = false;
			return;
		}

		//�������߂���Δ���
		if (Len.Length() <= SearchDistance)
		{
			mEnemyApproachingFlag = true;
			ENEMY_TYPE enemytype = pEnemyManager->ClosestPosEnemyType(pos);

			//�߂�Enemy�̕���������
			if (enemytype != ENEMY_TYPE::Witch)//���@�g���łȂ����
			{
				mAngle = -atan2f(pos.z - EnemyPos.z, pos.x - EnemyPos.x);
			}

			//�e�𔭎�
			if (enemytype != ENEMY_TYPE::Witch)//���@�g���łȂ����
			{
				pBulletManager->Shot(pos, EnemyPos, BULLET_TYPE::CANNONBALL, GetOffensivePower() + PowerUpLevel(), mLevel);

				//�U����SE�̍Đ�
				soundmanager.SE_Run(SOUND_SE::SE_CANNON, SE_RUN::PLAY);
			}
		}
		else
		{
			mEnemyApproachingFlag = false;
		}
	}
}

//���x���A�b�v�ɂ����鎞��
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

//�U���͂̐ݒ�
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

//�p���[�A�b�v���郌�x��
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