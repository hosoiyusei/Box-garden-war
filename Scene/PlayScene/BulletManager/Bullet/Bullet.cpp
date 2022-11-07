#include"pch.h"
#include"Bullet.h"
#include"../../EffectManager/EffectManager.h"

#include"Slashing.h"
#include"Shoot.h"
#include"Shooting.h"
#include"CannonBall.h"
#include"Magic.h"
#include"../../DoubleSpeed/DoubleSpeed.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Bullet::Bullet()
	:mActive(false)
	, mWorld()
	, mPos()
	, mTargetPos()
	, mCollision()
	, mVel()
	, mInitialPos()
	, mpEffectManager(nullptr)
	, mType(BULLET_TYPE::NONE)
{

}

//�f�X�g���N�^
Bullet::~Bullet()
{

}

//������
void Bullet::Initialize(EffectManager* pEffectManager)
{
	//�|�C���^�̎擾
	mpEffectManager = pEffectManager;

	//�����A������̑傫����ݒ�
	mCollision.mRadius = 0.2f;
}

//�X�V
void Bullet::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	//�e�̈ړ�
	mPos += mVel * mpDoubleSpeed.GetSpeed();

	Vector3 len = mPos - mInitialPos;
	
	//�e���͈͊O�ɏo����폜
	if (len.Length() >= mpBulletType->GetLen())
	{
		mActive = false;
	}

	//�e�̎�ނɂ��X�V
	mpBulletType->Update(mpEffectManager);
	
	//�����蔻��̍��W��ݒ�
	mCollision.mPos = mPos;
}

//�`��
void Bullet::Draw()
{
	mpBulletType->Draw(mPos);
}

//�e�𔭎�
void Bullet::Shot(
	const Vector3& pos
	, const Vector3& target
	, const BULLET_TYPE& type
	, const int& power
	, const UNIT_LEVEL& level
	, DirectX::SimpleMath::Color color)
{
	//��Ԃ�ݒ�
	SetState(type);

	mPos = pos;

	mCollision.mPos = pos;

	mInitialPos = pos;

	float angle = atan2f(
		target.z - mPos.z, target.x - mPos.x);

	//����
	mpBulletType->Shot(power, angle, color,level);

	mVel.z = static_cast<float>(mpBulletType->GetSpeed() * sin(angle));
	mVel.x = static_cast<float>(mpBulletType->GetSpeed() * cos(angle));

	mActive = true;
}

const int Bullet::Hit()
{
	mActive = false;

	if (mpBulletType->GetType() == BULLET_TYPE::CANNONBALL)
	{
		mpEffectManager->Play(mPos, Vector3(1.0f, 0.0f, 0.0f), 10, TEXTURE3D::SHADOW);
		mpEffectManager->Play(mPos, Vector3(1.0f, 0.5f, 0.0f), 10, TEXTURE3D::SHADOW, 0.003f, 0.15f);
		mpEffectManager->Play(mPos, Vector3(0.5f, 0.5f, 0.5f), 20, TEXTURE3D::SHADOW, 0.003f, 0.1f);
	}


	return mpBulletType->GetOffensivePower();
}

const UNIT_LEVEL Bullet::GetLevel()
{
	return mpBulletType->GetLevel();
}

/****************************************************************************/

void Bullet::SetState(const BULLET_TYPE& type)
{
	mpBulletType.reset(nullptr);

	switch (type)
	{
		case BULLET_TYPE::SLASHING:
		{
			mpBulletType = std::make_unique<Slashing>();
			mType = BULLET_TYPE::SLASHING;
			break;
		}
		case BULLET_TYPE::SHOOT:
		{
			mpBulletType = std::make_unique<Shoot>();
			mType = BULLET_TYPE::SHOOT;
			break;
		}
		case BULLET_TYPE::SHOOTING:
		{
			mpBulletType = std::make_unique<Shooting>();
			mType = BULLET_TYPE::SHOOTING;
			break;
		}
		case BULLET_TYPE::CANNONBALL:
		{
			mpBulletType = std::make_unique<CannonBall>();
			mType = BULLET_TYPE::CANNONBALL;
			break;
		}
		case BULLET_TYPE::MAGIC:
		{
			mpBulletType = std::make_unique<Magic>();
			mType = BULLET_TYPE::MAGIC;
			break;
		}
		default:
			break;
	}
}