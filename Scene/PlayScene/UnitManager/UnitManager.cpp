#include"pch.h"
#include"UnitManager.h"

#include"Unit/Unit.h"
#include"../Player/Player.h"

//���j�b�g�̐�
const int MAX_UNIT_NUM(60);

//�R���X�g���N�^
UnitManager::UnitManager()
	:mpUnit{}
	,mpPlayer(nullptr)
{

}

//�f�X�g���N�^
UnitManager::~UnitManager()
{

}

//������
//�����FEnemy�̊Ǘ��ҁE�e�̊Ǘ��ҁE�G�t�F�N�g�̊Ǘ���
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

//�X�V
void UnitManager::Update()
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		//�A�N�e�B�u�Ȃ�X�V
		if (mpUnit[i]->GetActive() == true)
		{
			mpUnit[i]->Update();
			UnitPowerUp(mpUnit[i].get());
		}
	}
}

//�`��
void UnitManager::Draw()
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		//�A�N�e�B�u�Ȃ�`��
		if (mpUnit[i]->GetActive() == true)
		{
			mpUnit[i]->Draw();
		}
	}
}

//Unit�̃G�t�F�N�g�̕`��
void UnitManager::EffectDraw()
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		//�A�N�e�B�u�Ȃ�`��
		if (mpUnit[i]->GetActive() == true)
		{
			mpUnit[i]->EffectDraw();
		}
	}
}

//�X�|�[��
//�����F�Ăяo�����W�E���j�b�g�̃^�C�v
const TILE_DATA UnitManager::Spawn(
	const DirectX::SimpleMath::Vector3& pos
	, const UNIT_TYPE& type)
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		//�A�N�e�B�u�Ȃ����
		if (mpUnit[i]->GetActive() == false)
		{
			mpUnit[i]->Spawn(pos, type);
			
			break;
		}
	}

	return UnitTypeData(type);
}

//Unit�̃��x���̐ݒ�
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

//�������̃t���O��Ԃ�
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

//�U����
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

//���j�b�g�̍폜
//�����F���j�b�g�̍��W
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

			//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
			mpPlayer->SetTileNum(posx, posy
				, TILE_DATA::Unit_Scaffolding
				, UNIT_LEVEL::NONE);

			Release_power_ups();

			break;
		}
	}
}

//�p���[�A�b�v�̉���
void UnitManager::Release_power_ups()
{
	for (size_t i = 0; i < mpUnit.size(); i++)
	{
		//�A�N�e�B�u�Ȃ�X�V
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

//Unit�̃p���[�A�b�v
void UnitManager::UnitPowerUp(Unit* pUnit)
{
	if (pUnit->GetUnitType() == UNIT_TYPE::SHOGUN)
	{
		for (size_t i = 0; i < mpUnit.size(); i++)
		{
			//�A�N�e�B�u�Ȃ�X�V
			if (mpUnit[i]->GetActive() == true)
			{
				if (mpUnit[i]->GetUnitType() != UNIT_TYPE::SHOGUN)
				{
					//Unit���p���[�A�b�v������
					mpUnit[i]->PowerUp(pUnit->GetCollision(), pUnit->GetUnitLevel());
				}
			}
		}
	}
}

//Unit�̎�ނ���tile�f�[�^��Ԃ�
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