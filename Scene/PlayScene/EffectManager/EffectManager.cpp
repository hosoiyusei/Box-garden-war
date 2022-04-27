#include"pch.h"
#include"EffectManager.h"

#include"Effect/Effect.h"

//Effect�̐�
const int  EFFECT_NUM(300);

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
EffectManager::EffectManager()
{

}

//�f�X�g���N�^
EffectManager::~EffectManager()
{

}

//������
void EffectManager::Initialize()
{
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		mpEffect.push_back(std::make_unique<Effect>());
		mpEffect[i]->Initialize();
	}
}

//�X�V
void EffectManager::Update()
{
	for (int i = 0; i < mpEffect.size(); i++)
	{
		//�A�N�e�B�u��������X�V
		if (mpEffect[i]->GetActive() == true)
		{
			mpEffect[i]->Update();
		}
	}
}

//�`��
void EffectManager::Draw()
{
	for (int i = 0; i < mpEffect.size(); i++)
	{
		//�A�N�e�B�u��������`��
		if (mpEffect[i]->GetActive() == true)
		{
			mpEffect[i]->Draw();
		}
	}
}

//�G�t�F�N�g�̎��s
void EffectManager::Play(
	const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& color
	, const int& number
	, const TEXTURE3D& texture
	, const float& speed
	, const float& size)
{
	//���s�񐔂̃J�E���g
	int count = 0;

	for (int i = 0; i < mpEffect.size(); i++)
	{
		//�A�N�e�B�u����������s
		if (mpEffect[i]->GetActive() == false)
		{
			count++;
			mpEffect[i]->Play(pos, color, texture, speed, size);
		}

		if (count >= number)
		{
			break;
		}
	}
}

//�G�t�F�N�g�̎��s
void EffectManager::Play_2(
	const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& color
	, const int& number
	, const TEXTURE3D& texture
	, const float& speed
	, const float& size)
{
	const float RAD = XM_PI * 2.0f;
	int num = 0;

	for (int i = 0; i < mpEffect.size(); i++)
	{
		if (mpEffect[i]->GetActive() == false)
		{
			float size = static_cast<float>(number);//(float)mpEffect.size();
			Vector3 vel = Vector3(cos(RAD * static_cast<float>(num) / size + XM_PI / 2.0f),
				0.0f, sin(RAD * num / size + XM_PI / 2.0f));
			vel *= 0.1f;
			mpEffect[i]->Play(pos, color, texture, speed, 0.3f);
			mpEffect[i]->SetMoveVector(vel);
			num++;

			if (num == number)
			{
				break;
			}
		}	
	}
}


//�G�t�F�N�g�̎��s
void EffectManager::Play_3(
	  const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& color
	, const int& number
	, const TEXTURE3D& texture
	, const float& speed
	, const float& size)
{
	//���s�񐔂̃J�E���g
	int count = 0;

	for (int i = 0; i < mpEffect.size(); i++)
	{
		//�A�N�e�B�u����������s
		if (mpEffect[i]->GetActive() == false)
		{
			count++;
			mpEffect[i]->Play(pos, color, texture, speed, size,true);
			mpEffect[i]->SetMoveVector(Vector3(0.0f, 0.1f, 0.0f));
		}

		if (count >= number)
		{
			break;
		}
	}
}