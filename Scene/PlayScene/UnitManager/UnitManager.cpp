#include"pch.h"
#include"UnitManager.h"

#include"Unit/Unit.h"

//ユニットの数
const int MAX_UNIT_NUM(150);

//コンストラクタ
UnitManager::UnitManager()
	:mpUnit{}
{

}

//デストラクタ
UnitManager::~UnitManager()
{

}

//初期化
//引数：Enemyの管理者・弾の管理者・エフェクトの管理者
void UnitManager::Initialize(
	EnemyManager* pEnemyManager
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager)
{
	for (int i = 0; i < MAX_UNIT_NUM; i++)
	{
		mpUnit.push_back(std::make_unique<Unit>());
		mpUnit[i]->Initialize(
			pEnemyManager, pBulletManager, pEffectManager);
	}
}

//更新
void UnitManager::Update()
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		//アクティブなら更新
		if (mpUnit[i]->GetActive() == true)
		{
			mpUnit[i]->Update();

			UnitPowerUp(mpUnit[i].get());
		}	
	}
}

//描画
void UnitManager::Draw()
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		//アクティブなら描画
		if (mpUnit[i]->GetActive() == true)
		{
			mpUnit[i]->Draw();
		}
	}
}

//Unitのエフェクトの描画
void UnitManager::EffectDraw()
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		//アクティブなら描画
		if (mpUnit[i]->GetActive() == true)
		{
			mpUnit[i]->EffectDraw();
		}
	}
}

//スポーン
//引数：呼び出す座標・ユニットのタイプ
const TILE_DATA UnitManager::Spawn(
	const DirectX::SimpleMath::Vector3& pos
	, const UNIT_TYPE& type)
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		//アクティブなければ
		if (mpUnit[i]->GetActive() == false)
		{
			mpUnit[i]->Spawn(pos, type);
			break;
		}
	}

	return UnitTypeData(type);
}

//Unitのレベルの設定
void UnitManager::SetUnitLevel(const DirectX::SimpleMath::Vector3& pos, const UNIT_LEVEL& level)
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		if (mpUnit[i]->GetActive() == true)
		{
			if (mpUnit[i]->GetPos().x == pos.x &&
				mpUnit[i]->GetPos().z == pos.z)
			{
				mpUnit[i]->SetUnitLevel(level);

				break;
			}
		}
	}
}

//ユニットの削除
//引数：ユニットの座標
void UnitManager::Delete(const DirectX::SimpleMath::Vector3& pos)
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		if (mpUnit[i]->GetActive() == true)
		{
			if (mpUnit[i]->GetPos().x == pos.x&&
				mpUnit[i]->GetPos().z == pos.z)
			{
				mpUnit[i]->Delete();
				break;
			}
		}
	}
}

//強化中のフラグを返す
const bool& UnitManager::GetReinforcementFlag(const DirectX::SimpleMath::Vector3& pos)
{
	for (int i = 0; i < mpUnit.size(); i++)
	{
		if (mpUnit[i]->GetActive() == true)
		{
			if (mpUnit[i]->GetPos().x == pos.x &&
				mpUnit[i]->GetPos().z == pos.z)
			{
				return mpUnit[i]->GetReinforcementFlag();

				break;
			}
		}
	}
}

/******************************************************************************/

//Unitのパワーアップ
void UnitManager::UnitPowerUp(Unit* pUnit)
{
	if (pUnit->GetUnitType() == UNIT_TYPE::SHOGUN)
	{
		for (int i = 0; i < mpUnit.size(); i++)
		{
			//アクティブなら更新
			if (mpUnit[i]->GetActive() == true)
			{
				if (mpUnit[i]->GetUnitType() != UNIT_TYPE::SHOGUN)
				{
					//Unitをパワーアップさせる
					mpUnit[i]->PowerUp(pUnit->GetCollision(), pUnit->GetUnitLevel());
				}
			}
		}
	}
}

//Unitの種類からtileデータを返す
const TILE_DATA& UnitManager::UnitTypeData(const UNIT_TYPE& unitType)
{
	switch (unitType)
	{		
		case UNIT_TYPE::SWORDFIGHTER:	{return TILE_DATA::Swordfighter;	break; }
		case UNIT_TYPE::ARCHER:			{return TILE_DATA::Archer;			break; }
		case UNIT_TYPE::GUNNER:			{return TILE_DATA::Gunner;			break; }
		case UNIT_TYPE::CANNON:			{return TILE_DATA::Cannon;			break; }
		case UNIT_TYPE::WIZARD:			{return TILE_DATA::Wizard;			break; }
		case UNIT_TYPE::SHOGUN:			{return TILE_DATA::Shogun;			break; }
		default:break;
	}
}