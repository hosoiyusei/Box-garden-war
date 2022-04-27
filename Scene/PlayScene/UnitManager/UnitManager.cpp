#include"pch.h"
#include"UnitManager.h"

#include"Unit/Unit.h"

//���j�b�g�̐�
const int MAX_UNIT_NUM(150);

//�R���X�g���N�^
UnitManager::UnitManager()
	:mpUnit{}
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
	, EffectManager* pEffectManager)
{
	for (int i = 0; i < MAX_UNIT_NUM; i++)
	{
		mpUnit.push_back(std::make_unique<Unit>());
		mpUnit[i]->Initialize(
			pEnemyManager, pBulletManager, pEffectManager);
	}
}

//�X�V
void UnitManager::Update()
{
	for (int i = 0; i < mpUnit.size(); i++)
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
	for (int i = 0; i < mpUnit.size(); i++)
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
	for (int i = 0; i < mpUnit.size(); i++)
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
	for (int i = 0; i < mpUnit.size(); i++)
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

//���j�b�g�̍폜
//�����F���j�b�g�̍��W
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

//�������̃t���O��Ԃ�
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

//Unit�̃p���[�A�b�v
void UnitManager::UnitPowerUp(Unit* pUnit)
{
	if (pUnit->GetUnitType() == UNIT_TYPE::SHOGUN)
	{
		for (int i = 0; i < mpUnit.size(); i++)
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