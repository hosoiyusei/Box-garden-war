#include"pch.h"
#include"BulletManager.h"
#include"../EnemyManager/Enemy/Enemy.h"

#include"Bullet/Bullet.h"

//弾の数
const int BULLET_NUM(150);

//コンストラクタ
BulletManager::BulletManager()
{

}

//デストラクタ
BulletManager::~BulletManager()
{

}

//初期化
void BulletManager::Initialize(EffectManager* pEffectManager)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		mpBullet.push_back(std::make_unique<Bullet>());
		mpBullet[i]->Initialize(pEffectManager);
	}
}

//更新
void BulletManager::Update()
{
	for (int i = 0; i < static_cast<int>(mpBullet.size()); i++)
	{
		//アクティブだったら更新
		if (mpBullet[i]->GetActive() == true)
		{
			mpBullet[i]->Update();
		}
	}
}

//描画
void BulletManager::Draw()
{
	for (int i = 0; i < static_cast<int>(mpBullet.size()); i++)
	{
		//アクティブだったら描画
		if (mpBullet[i]->GetActive() == true)
		{
			mpBullet[i]->Draw();
		}
	}
}

//弾を発射する
void BulletManager::Shot(
	const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& target
	, const BULLET_TYPE& type
	, const int& power
	, const UNIT_LEVEL& level
	, DirectX::SimpleMath::Color color)
{
	for (int i = 0; i < static_cast<int>(mpBullet.size()); i++)
	{
		if (mpBullet[i]->GetActive() == false)
		{
			mpBullet[i]->Shot(pos, target, type, power,level, color);
			break;
		}
	}
}

//弾の当たり判定
bool BulletManager::CheckHitCollision(
	 Enemy* pEnemy)
{
	for (int i = 0; i < static_cast<int>(mpBullet.size()); i++)
	{
		if (mpBullet[i]->GetActive() == true)
		{
			if(pEnemy->GetCollision().CheckHit(
				mpBullet[i]->GetCollision())==true)
			{
				
				//当たったらダメージを与える
				pEnemy->Damage(mpBullet[i]->Hit(), mpBullet[i]->GetBulletType(),mpBullet[i]->GetLevel());

				return true;
			}
		}
	}

	return false;
}