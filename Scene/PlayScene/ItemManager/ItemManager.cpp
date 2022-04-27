#include"pch.h"
#include"ItemManager.h"
#include"Item/Item.h"
#include"../BulletManager/Bullet/BulletType.h"
#include"../EnemyManager/Enemy/Enemy.h"
#include"../UnitManager/Unit/UnitLevel.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//アイテムの数
const int ItemNum(5);

//コンストラクタ
ItemManager::ItemManager()
{

}

//デストラクタ
ItemManager::~ItemManager()
{

}

//初期化
void ItemManager::Initialize(Player* pPlayer)
{
	for (int i = 0; i < ItemNum; i++)
	{
		mpItem.push_back(std::make_unique<Item>());
		mpItem[i]->Initialize(pPlayer);
	}
}

//更新
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

//描画
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

//Capsuleの当たり判定を返す
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

				//当たったらダメージを与える
				pEnemy->Damage(10000, BULLET_TYPE::NONE, UNIT_LEVEL::NONE);
			}
		}
	}
}