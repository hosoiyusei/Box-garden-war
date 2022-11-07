#include"pch.h"
#include"Witch.h"

#include"../../DoubleSpeed/DoubleSpeed.h"

#include"../../EffectManager/EffectManager.h"
#include"../../Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Enemy�̊�b�̑���
const float ENEMY_SPEED(0.01f);

//�R���X�g���N�^
Witch::Witch()
	:mLevel(ENEMY_LEVEL::NONE)
	, mSpearAngle(0.0f)
	, mLeftHandPos()
	, mRightHandPos()
	, mHandAngle(0.0f)
	, mFloating(0.0f)
	, mHP(0)
	, mSlowFootTimer(0)
	, mSpeed(0.0f)
	, mpEffectManager(nullptr)
	, mpPlayer(nullptr)
	, mEnemy_Status(Enemy_Status::generally)
	, mEnemy_Status2(Enemy_Status::generally)
	, mCombustionTimer(0)
	, mPos()
	, mPos2()
{

}

//�f�X�g���N�^
Witch::~Witch()
{

}

//�G�t�F�N�g�̐F�̐ݒ�
const Vector3 Witch::GetEffectColor()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return Vector3(1.0f, 0.0f, 0.0f); break; }
		case ENEMY_LEVEL::LEVEL2: {return Vector3(1.0f, 1.0f, 0.0f); break; }
		case ENEMY_LEVEL::LEVEL3: {return Vector3(1.0f, 0.0f, 1.0f); break; }
		case ENEMY_LEVEL::LEVEL4: {return Vector3(0.0f, 1.0f, 1.0f); break; }
		case ENEMY_LEVEL::LEVEL5: {return Vector3(0.0f, 1.0f, 0.0f); break; }
		default:break;
	}

	return Vector3();
}

//Enemy���o��������
void Witch::Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)
{
	mpEffectManager = pEffectManager;
	mpPlayer = pPlayer;

	mLevel = level;

	mHP = SetHP();

	mSpeed = ENEMY_SPEED;

	mLeftHandPos = Vector3(-0.5f, -0.5f, 0.0f);
	mRightHandPos = Vector3(-0.5f, -0.5f, -0.0f);
	mSpearAngle = 1.0f;
	mFloating += 0.1f;
}

//�X�V
void Witch::Update()
{
	Processingofeachstate();
	Processingofeachstate2();
}

//�`��
void Witch::Draw(const Vector3& pos
	, const float& angle, const float& fade)
{
	DrawManager& pObject = DrawManager::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	mPos = pos;

	Vector3 Pos = Vector3(pos.x, pos.y + 1.0f + (static_cast<float>(sin(mFloating)) * 0.5f), pos.z);

	mPos2 = Pos;

	Matrix body			//����
		, head			//��
		, leftHand		//����
		, rightHand		//�E��
		, Magichat		//�X�q
		, broom;		//�

	//��
	body = Matrix::CreateScale(0.8f);
	body *= Matrix::CreateRotationY(angle);
	if (mHP == 0)
	{
		body *= Matrix::CreateRotationX(angle);
		body *= Matrix::CreateRotationZ(angle);
	}
	body *= Matrix::CreateTranslation(Pos);

	pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(GetEffectColor())*fade);

	//��
	head = Matrix::CreateScale(0.5f);
	head *= Matrix::CreateTranslation(Vector3(0.0f, 0.5f, 0.0f));
	head *= body;

	pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Colors::BurlyWood * fade);

	//�E��
	rightHand = Matrix::CreateScale(0.3f);
	rightHand *= Matrix::CreateTranslation(mRightHandPos);
	rightHand *= Matrix::CreateRotationZ(XMConvertToRadians(static_cast<float>(sin(mHandAngle)) * 50.0f));
	rightHand *= body;

	pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood * fade);

	//����
	leftHand = Matrix::CreateScale(0.3f);
	leftHand *= Matrix::CreateTranslation(mLeftHandPos);
	leftHand *= Matrix::CreateRotationZ(XMConvertToRadians(-static_cast<float>(sin(mHandAngle)) * 50.0f));
	leftHand *= body;

	pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood * fade);

	broom = Matrix::CreateScale(0.5f);
	broom *= Matrix::CreateTranslation(Vector3(0.0f, 0.0f, -1.3f));
	broom *= Matrix::CreateRotationY(-1.57f);
	broom *= rightHand;
	
	Magichat *= Matrix::CreateScale(0.006f);
	Magichat *= Matrix::CreateRotationY(XMConvertToRadians(-70.0f));
	Magichat *= Matrix::CreateTranslation(Vector3(0.0f, 1.0f, 0.0f));
	Magichat *= head;

	if (fade == 1.0f)
	{
		pObject.GetModel()->Draw(broom, MODEL_NAME::BROOM);
		pObject.GetModel()->Draw(Magichat, MODEL_NAME::MAGICHAT);
	}
	else
	{
		static int fadetimer = 0;

		++fadetimer %= 2;

		if (fadetimer == 0)
		{
			pObject.GetModel()->Draw(broom, MODEL_NAME::BROOM);
			pObject.GetModel()->Draw(Magichat, MODEL_NAME::MAGICHAT);
		}
	}
}

//�G�t�F�N�g�̕`��
void Witch::EffectDraw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();
	pObject.GetTexture3D()->SetColor();

	const float ShadowSize = mFloating * 0.5f; 

	//�e�̕`��
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(abs(static_cast<float>(cos(ShadowSize))) + 0.2f);
	world *= Matrix::CreateRotationX(-1.57f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.9f, pos.z));
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::SHADOW);

	//HP�Q�[�W�̕`��
	pObject.GetTexture3D()->SetColor(0.0f, 1.0f);

	float HP = static_cast<float>(mHP);
	float MaxHP = static_cast<float>(SetHP());

	world = Matrix::Identity;
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale((HP / MaxHP), 0.1f, 0.1f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y + 2.4f, pos.z - 0.3f));

	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);

	switch (mEnemy_Status)
	{
		case Enemy_Status::combustion: {mpEffectManager->Play(mPos2, Vector3(1.0f, 0.0f, 0.0f), 1, TEXTURE3D::SHADOW, 0.003f, 0.1f); break; }
		case Enemy_Status::Slowfoot: {mpEffectManager->Play(mPos2, Vector3(1.0f, 0.0f, 1.0f), 1, TEXTURE3D::SHADOW, 0.003f, 0.1f); break; }
		case Enemy_Status::generally: {break; }
		default:break;
	}
}

//Damage�̏���
const bool Witch::Damage(const DirectX::SimpleMath::Vector3& pos
	, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)
{
	UNREFERENCED_PARAMETER(level);


	SoundManager& soundmanager = SoundManager::GetInstance();

	//Enemy�����G�łȂ��Ȃ�
	if (type != BULLET_TYPE::SHOOTING)
	{
		mHP -= damage;
	}
	else
	{
		mHP -= static_cast<int>(static_cast<float>(damage) * 0.5f);
	}

	soundmanager.SE_Run(SOUND_SE::SE_DAMAGE, SE_RUN::PLAY);

	//���������U��������������
	if (mEnemy_Status == Enemy_Status::generally)
	{
		if (type == BULLET_TYPE::SLASHING)
		{
			mEnemy_Status = Enemy_Status::Slowfoot;
			SlowFoot();
		}
		else if (type == BULLET_TYPE::SHOOT)
		{
			//�R��
			mEnemy_Status = Enemy_Status::combustion;
			Combustion();
		}
	}
	else if (mEnemy_Status2 == Enemy_Status::generally)
	{
		if (type == BULLET_TYPE::SLASHING)
		{
			mEnemy_Status2 = Enemy_Status::Slowfoot;
			SlowFoot();
		}
		else if (type == BULLET_TYPE::SHOOT)
		{
			//�R��
			mEnemy_Status2 = Enemy_Status::combustion;
			Combustion();
		}
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

//����ł��邩�ǂ���
const bool Witch::Whetherdead()
{
	//HP��0�����ɂȂ�����E��
	if (mHP <= 0)
	{
		mHP = 0;

		//�G�t�F�N�g�̎��s
		mpEffectManager->Play(mPos, GetEffectColor(), 15, TEXTURE3D::SHADOW);

		//���𑝂₷
		mpPlayer->SetMoney(GetMoney());

		return false;
	}

	return true;
}

/***************************************************************************************************************************************************************/

//�ݑ����
void Witch::SlowFoot()
{
	mSlowFootTimer = 0;
	mSpeed = ENEMY_SPEED * 0.6f;
}

//�R�ď��
void Witch::Combustion()
{
	mCombustionTimer = 0;
}

//HP�̐ݒ�
const int Witch::SetHP()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 2; break; }
		case ENEMY_LEVEL::LEVEL2: {return 6; break; }
		case ENEMY_LEVEL::LEVEL3: {return 25; break; }
		case ENEMY_LEVEL::LEVEL4: {return 40; break; }
		case ENEMY_LEVEL::LEVEL5: { return 50; break; }
		default:break;
	}

	return 0;
}

//��
const int Witch::GetMoney()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 8; break; }
		case ENEMY_LEVEL::LEVEL2: {return 9; break; }
		case ENEMY_LEVEL::LEVEL3: {return 10; break; }
		case ENEMY_LEVEL::LEVEL4: {return 11; break; }
		case ENEMY_LEVEL::LEVEL5: {return 12; break; }
		default:break;
	}

	return 0;
}

//��Ԃ��Ƃ̏���
void Witch::Processingofeachstate()
{
	switch (mEnemy_Status)
	{
		case Enemy_Status::combustion:
		{
			mCombustionTimer++;

			int time = mCombustionTimer;

			time %= 100;

			//�R�ă_���[�W��^����
			if (time == 0)
			{
				mHP -= 1;
			}

			if (mCombustionTimer >= 300)
			{
				mCombustionTimer = 0;
				mEnemy_Status = Enemy_Status::generally;

			}
			break;
		}
		case Enemy_Status::Slowfoot:
		{
			//�ݑ���Ԃ̎�
			mSlowFootTimer++;

			//�ݑ���Ԃ�����
			if (mSlowFootTimer >= 300)
			{
				mSlowFootTimer = 0;
				mSpeed = ENEMY_SPEED;
				mEnemy_Status = Enemy_Status::generally;
			}
			break;
		}
		case Enemy_Status::generally:
		{
			break;
		}
		default:break;
	}
}

//��Ԃ��Ƃ̏���
void Witch::Processingofeachstate2()
{
	switch (mEnemy_Status2)
	{
		case Enemy_Status::combustion:
		{
			//�R��
			mCombustionTimer++;

			int time = mCombustionTimer;

			time %= 100;

			//�R�ă_���[�W��^����
			if (time == 0)
			{
				mHP -= 1;
			}

			//�R�Ă�����
			if (mCombustionTimer >= 300)
			{
				mCombustionTimer = 0;
				mEnemy_Status2 = Enemy_Status::generally;

			}
			break;
		}
		case Enemy_Status::Slowfoot:
		{
			//�ݑ���Ԃ̎�
			mSlowFootTimer++;

			//�ݑ���Ԃ�����
			if (mSlowFootTimer >= 180)
			{
				mSlowFootTimer = 0;
				mSpeed = ENEMY_SPEED;
				mEnemy_Status2 = Enemy_Status::generally;
			}
			break;
		}
		case Enemy_Status::generally:
		{
			break;
		}
		default:break;
	}
}