#include"pch.h"
#include"Unit.h"

#include"Swordfighter/Swordfighter.h"

#include"Archer/Archer.h"

#include"Gunner/Gunner.h"

#include"Cannon/Cannon.h"

#include"Wizard/Wizard.h"

#include"Shogun/Shogun.h"

#include"../../EnemyManager/EnemyManager.h"
#include"../../BulletManager/BulletManager.h"
#include"../../EffectManager/EffectManager.h"
#include"../../DoubleSpeed/DoubleSpeed.h"

#include"Common/SoundManager/Adx2.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Unit::Unit()
	: mActive(false)
	, mPos()
	, mpEnemyManager(nullptr)
	, mpBulletManager(nullptr)
	, mpEffectManager(nullptr)
	, mType(UNIT_TYPE::NONE)
	, mLevel(UNIT_LEVEL::NONE)
{

}

//�f�X�g���N�^
Unit::~Unit()
{

}

//������
void Unit::Initialize(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager)
{
	//Enemy�̊Ǘ��҂̃|�C���^�̎擾
	mpEnemyManager = pEnemyManager;

	//�e�̊Ǘ��҂̃|�C���^�̎擾
	mpBulletManager = pBulletManager;

	//Effect�̊Ǘ��҂̃|�C���^�̎擾
	mpEffectManager = pEffectManager;
}

//�X�V
void Unit::Update()
{
	//Unit�̎�ނ��Ƃ̍X�V
	mpUnitTypeBase->Update(mpEnemyManager, mpBulletManager, mpEffectManager, mPos);
}

//�`��
void Unit::Draw()
{
	mpUnitTypeBase->Draw(mPos);
}

//Unit�̃G�t�F�N�g�̕`��
void Unit::EffectDraw()
{
	mpUnitTypeBase->EffectDraw(mPos, mpEffectManager);
}

//�X�|�[��
void Unit::Spawn(const Vector3& pos, const UNIT_TYPE& type)
{
	//��Ԃ�ݒ�
	SetType(type);

	mType = type;

	mLevel = UNIT_LEVEL::LEVEL_1;

	//���W�̐ݒ�
	mPos = pos;
	mPos.y = 1.0f;

	//Unit�̏����ݒ�
	mpUnitTypeBase->Spawn(mPos);

	//�A�N�e�B�u�ɂ���
	mActive = true;

	//�G�t�F�N�g�̎��s
	mpEffectManager->Play_2(Vector3(mPos.x, mPos.y - 0.3f, mPos.z), GetEffectColor(), 10, TEXTURE3D::SHADOW);

	mpUnitTypeBase->SetColor(GetEffectColor());
}

//Unit�̃��x���̐ݒ�
void Unit::SetUnitLevel(const UNIT_LEVEL& level)
{
	mLevel = level;
	mpUnitTypeBase->SetLevel(level);
	mpUnitTypeBase->SetColor(GetEffectColor());
}

//���j�b�g�̏��O
void Unit::Delete()
{
	mPos = Vector3(0.0f, 0.0f, 0.0f);
	mActive = false;
}

//�������̃t���O��Ԃ�
const bool Unit::GetReinforcementFlag(){return mpUnitTypeBase->GetReinforcementFlag();}

//�����蔻���Ԃ�
const SphereCollision Unit::GetCollision() { return mpUnitTypeBase->GetCollision(); }

//Unit�̃p���[�A�b�v
void Unit::PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level) { mpUnitTypeBase->PowerUp(GetCollision, level); }

//�p���[�A�b�v�̉���
void Unit::Release_power_ups() { mpUnitTypeBase->Release_power_ups(); }

//�U����
const int Unit::GetPower() { return mpUnitTypeBase->GetPower(); }

/**********************************************************************************/

//��Ԃ�ݒ�
void Unit::SetType(const UNIT_TYPE& type)
{
	mpUnitTypeBase.reset(false);

	//��Ԃ�ݒ�
	switch (type)
	{
		case UNIT_TYPE::SWORDFIGHTER:	{mpUnitTypeBase = std::make_unique<Swordfighter>();	break; }
		case UNIT_TYPE::ARCHER:			{mpUnitTypeBase = std::make_unique<Archer>();		break; }
		case UNIT_TYPE::GUNNER:			{mpUnitTypeBase = std::make_unique<Gunner>();		break; }
		case UNIT_TYPE::CANNON:			{mpUnitTypeBase = std::make_unique<Cannon>();		break; }
		case UNIT_TYPE::SHOGUN:			{mpUnitTypeBase = std::make_unique<Shogun>();		break; }
		default:break;
	}
}

//�G�t�F�N�g�̐F�̐ݒ�
const Vector3 Unit::GetEffectColor()
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

	return Vector3();
}