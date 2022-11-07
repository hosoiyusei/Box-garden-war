#include"pch.h"
#include"BulletManager.h"
#include"../EnemyManager/Enemy/Enemy.h"

#include"Bullet/Bullet.h"

//�e�̐�
const int BULLET_NUM(50);

//�R���X�g���N�^
BulletManager::BulletManager()
{

}

//�f�X�g���N�^
BulletManager::~BulletManager()
{

}

//������
void BulletManager::Initialize(EffectManager* pEffectManager)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		mpBullet.push_back(std::make_unique<Bullet>());
		mpBullet[i]->Initialize(pEffectManager);
	}
}

//�X�V
void BulletManager::Update()
{
	for (size_t i = 0; i < mpBullet.size(); i++)
	{
		//�A�N�e�B�u��������X�V
		if (mpBullet[i]->GetActive() == true)
		{
			mpBullet[i]->Update();
		}
	}
}

//�`��
void BulletManager::Draw()
{
	for (size_t i = 0; i < mpBullet.size(); i++)
	{
		//�A�N�e�B�u��������`��
		if (mpBullet[i]->GetActive() == true)
		{
			mpBullet[i]->Draw();
		}
	}
}

//�e�𔭎˂���
void BulletManager::Shot(
	const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& target
	, const BULLET_TYPE& type
	, const int& power
	, const UNIT_LEVEL& level
	, DirectX::SimpleMath::Color color)
{
	for (size_t i = 0; i < mpBullet.size(); i++)
	{
		if (mpBullet[i]->GetActive() == false)
		{
			mpBullet[i]->Shot(pos, target, type, power,level, color);
			break;
		}
	}
}

//�e�̓����蔻��
void BulletManager::CheckHitCollision(
	 Enemy* pEnemy)
{
	for (size_t i = 0; i < mpBullet.size(); i++)
	{
		if (mpBullet[i]->GetActive() == true)
		{
			if (pEnemy->GetCollision().CheckHit(
				mpBullet[i]->GetCollision()) == true)
			{
				//����������_���[�W��^����
				pEnemy->Damage(mpBullet[i]->Hit(), mpBullet[i]->GetBulletType(),mpBullet[i]->GetLevel());
			}
		}
	}
}