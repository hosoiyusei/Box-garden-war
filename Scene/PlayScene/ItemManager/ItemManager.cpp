#include"pch.h"
#include"ItemManager.h"
#include"Item/Item.h"
#include"../BulletManager/Bullet/BulletType.h"
#include"../EnemyManager/Enemy/Enemy.h"
#include"../UnitManager/Unit/UnitLevel.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�A�C�e���̐�
const int ItemNum(5);

//�R���X�g���N�^
ItemManager::ItemManager()
{

}

//�f�X�g���N�^
ItemManager::~ItemManager()
{

}

//������
void ItemManager::Initialize(Player* pPlayer)
{
	for (int i = 0; i < ItemNum; i++)
	{
		mpItem.push_back(std::make_unique<Item>());
		mpItem[i]->Initialize(pPlayer);
	}
}

//�X�V
void ItemManager::Update()
{
	for (int i = 0; i < mpItem.size(); i++)
	{
		if (mpItem[i]->GetActive() == true)
		{
			mpItem[i]->Update();
		}
	}
}

//�`��
void ItemManager::Draw()
{
	for (int i = 0; i < mpItem.size(); i++)
	{
		if (mpItem[i]->GetActive() == true)
		{
			mpItem[i]->Draw();
		}
	}
}

//Spawn
void ItemManager::Spawn(const Vector3& pos)
{
	for (int i = 0; i < mpItem.size(); i++)
	{
		if (mpItem[i]->GetActive() == false)
		{
			mpItem[i]->Spawn(pos);
			break;
		}
	}
}

//Capsule�̓����蔻���Ԃ�
void ItemManager::CheckHitCapsule(const Capsule& capsule)
{
	for (int i = 0; i < mpItem.size(); i++)
	{
		if (mpItem[i]->GetActive() == true&&mpItem[i]->GetUseFlag()==false)
		{
			mpItem[i]->CheckHitCapsule(capsule);
			break;
		}
	}
}

void ItemManager::Use(const DirectX::SimpleMath::Vector3& pos, const ITEM_TYPE& type)
{
	for (int i = 0; i < mpItem.size(); i++)
	{
		if (mpItem[i]->GetActive() == false && mpItem[i]->GetUseFlag() == false)
		{
			mpItem[i]->Use(pos, type);
			break;
		}
	}
}

void ItemManager::CheckHitCollision(Enemy* pEnemy)
{
	for (int i = 0; i < mpItem.size(); i++)
	{
		if (mpItem[i]->GetActive() == true)
		{
			if (pEnemy->GetCollision().CheckHit(
				mpItem[i]->GetCollision()) == true && mpItem[i]->GetUseFlag() == true)
			{

				//����������_���[�W��^����
				pEnemy->Damage(10000, BULLET_TYPE::NONE, UNIT_LEVEL::NONE);
			}
		}
	}
}