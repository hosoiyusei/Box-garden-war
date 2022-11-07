#include"pch.h"
#include"UnitManager.h"

#include"Unit/Unit.h"
#include"../Player/Player.h"

//ユニットの数
const int MAX_UNIT_NUM(60);

//コンストラクタ
UnitManager::UnitManager()
	:mpUnit{}
	,mpPlayer(nullptr)
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
	, EffectManager* pEffectManager
	, Player* pPlayer)
{
	mpPlayer = pPlayer;

	for (size_t i = 0; i < MAX_UNIT_NUM; i++)
	{
		mpUnit.push_back(std::make_unique<Unit>());
		mpUnit[i]->Initialize(
			pEnemyManager, pBulletManager, pEffectManager);
	}
}

//更新
void UnitManager::Update()
{
	for (size_t i = 0; i < mpUnit.size(); i++)
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
	for (size_t i = 0; i < mpUnit.size(); i++)
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
	for (size_t i = 0; i < mpUnit.size(); i++)
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
	for (size_t i = 0; i < mpUnit.size(); i++)
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
	for (size_t i = 0; i < mpUnit.size(); i++)
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

//強化中のフラグを返す
const bool UnitManager::GetReinforcementFlag(const DirectX::SimpleMath::Vector3& pos)
{
	for (size_t i = 0; i < mpUnit.size(); i++)
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

	return false;
}

//攻撃力
const int UnitManager::GetPower(const DirectX::SimpleMath::Vector3& pos)
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		if (mpUnit[i]->GetActive() == true)
		{
			if (mpUnit[i]->GetPos().x == pos.x &&
				mpUnit[i]->GetPos().z == pos.z)
			{
				return mpUnit[i]->GetPower();

				break;
			}
		}
	}

	return 0;
}

//ユニットの削除
//引数：ユニットの座標
void UnitManager::Delete(const DirectX::SimpleMath::Vector3& pos)
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		if (mpUnit[i]->GetActive() == true&&
			mpUnit[i]->GetPos().x == pos.x &&
			mpUnit[i]->GetPos().z == pos.z)
		{
			mpUnit[i]->Delete();

			const int posx = static_cast<int>(pos.x);
			const int posy = static_cast<int>(pos.z);

			//Unitのスポーンとステージデータの書き換え
			mpPlayer->SetTileNum(posx, posy
				, TILE_DATA::Unit_Scaffolding
				, UNIT_LEVEL::NONE);

			Release_power_ups();

			break;
		}
	}
}

//パワーアップの解除
void UnitManager::Release_power_ups()
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		//アクティブなら更新
		if (mpUnit[i]->GetActive() == true)
		{
			if (mpUnit[i]->GetUnitType() != UNIT_TYPE::SHOGUN)
			{
				mpUnit[i]->Release_power_ups();
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
		for (size_t i = 0; i < mpUnit.size(); i++)
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
const TILE_DATA UnitManager::UnitTypeData(const UNIT_TYPE& unitType)
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

	return TILE_DATA::NONE;
}