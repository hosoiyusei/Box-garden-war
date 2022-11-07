#include"pch.h"
#include"Boss.h"
#include"../../EffectManager/EffectManager.h"
#include"../../Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Enemy�̊�b�̑���
const float ENEMY_SPEED(0.01f);

//�R���X�g���N�^
Boss::Boss()
	:mLevel(ENEMY_LEVEL::NONE)
	, mHP(0)
	, mSlowFootFlag(false)
	, mSlowFootTimer(0)
	, mSpeed(0.0f)
	, mpEffectManager(nullptr)
	, mpPlayer(nullptr)
{

}

//�f�X�g���N�^
Boss::~Boss()
{

}

//Enemy���o��������
void Boss::Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)
{
	mpEffectManager = pEffectManager;
	mpPlayer = pPlayer;

	mLevel = level;

	mHP = SetHP();

	mSpeed = ENEMY_SPEED;
}

//�X�V
void Boss::Update()
{
	//�ݑ���Ԃ̎�
	if (mSlowFootFlag == true)
	{
		mSlowFootTimer++;
	}

	//�ݑ���Ԃ�����
	if (mSlowFootTimer >= 180)
	{
		mSlowFootTimer = 0;
		mSlowFootFlag = false;
		mSpeed = ENEMY_SPEED;
	}
}

//�`��
void Boss::Draw(const Vector3& pos
	, const float& angle, const float& fade)
{
	UNREFERENCED_PARAMETER(pos);
	UNREFERENCED_PARAMETER(angle);
}

//�G�t�F�N�g�̕`��
void Boss::EffectDraw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();
	pObject.GetTexture3D()->SetColor();

	//�e�̕`��
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(1.0f);
	world *= Matrix::CreateRotationX(-1.57f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.4f, pos.z));
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::SHADOW);


	//HP�Q�[�W�̕`��
	pObject.GetTexture3D()->SetColor(0.0f, 1.0f);

	world = Matrix::Identity;
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale((static_cast<float>(mHP) / static_cast<float>(SetHP())), 0.1f, 0.1f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y + 0.8f, pos.z - 0.3f));

	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);
}

//Damage�̏���
const bool Boss::Damage(const DirectX::SimpleMath::Vector3& pos
	, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)
{
	UNREFERENCED_PARAMETER(level);
	SoundManager& soundmanager = SoundManager::GetInstance();

	//Enemy�����G�łȂ��Ȃ�
	mHP -= damage;
	soundmanager.SE_Run(SOUND_SE::SE_DAMAGE, SE_RUN::PLAY);

	//���������U�������@��������
	if (type == BULLET_TYPE::MAGIC)
	{
		SlowFoot();
	}

	//HP��0�����ɂȂ�����E��
	if (mHP <= 0)
	{
		mHP = 0;

		//�G�t�F�N�g�̎��s
		mpEffectManager->Play(pos, GetEffectColor(), 20, TEXTURE3D::SHADOW);

		//���𑝂₷
		mpPlayer->SetMoney(GetMoney());

		return false;
	}

	return true;
}

/***************************************************************************************************************************************************************/

//�ݑ����
void Boss::SlowFoot()
{
	mSlowFootFlag = true;
	mSlowFootTimer = 0;
	mSpeed = ENEMY_SPEED * 0.5f;
}

//HP�̐ݒ�
const int Boss::SetHP()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 20; break; }
		case ENEMY_LEVEL::LEVEL2: {return 40; break; }
		case ENEMY_LEVEL::LEVEL3: {return 60; break; }
		case ENEMY_LEVEL::LEVEL4: {return 80; break; }
		case ENEMY_LEVEL::LEVEL5: { return 100; break; }
		default:break;
	}

	return 0;
}

//��
const int Boss::GetMoney()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 7; break; }
		case ENEMY_LEVEL::LEVEL2: {return 8; break; }
		case ENEMY_LEVEL::LEVEL3: {return 9; break; }
		case ENEMY_LEVEL::LEVEL4: {return 10; break; }
		case ENEMY_LEVEL::LEVEL5: {return 11; break; }
		default:break;
	}

	return 0;
}