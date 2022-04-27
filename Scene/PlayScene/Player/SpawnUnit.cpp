#include"pch.h"
#include"SpawnUnit.h"

#include"../UnitManager/UnitManager.h"
#include"Player.h"
#include"../UnitManager/Unit/UnitLevel.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Spawn������Ƃ��̋�
const int SWORDFIGHTER_COST(-10);
const int ARCHER_COST(-20);
const int GUNNER_COST(-30);
const int CANNON_COST(-40);
const int SHOGUN_COST(-50);

//���x���グ��Ƃ��̋�
const int LEVEL_UP_COST_2(10);
const int LEVEL_UP_COST_3(20);
const int LEVEL_UP_COST_4(30);
const int LEVEL_UP_COST_5(40);

//Unit�̎�ޖ��̃��x���グ��Ƃ��̋�
const int LEVEL_UP_COST_SWORDFIGHTER(10);
const int LEVEL_UP_COST_ARCHER(20);
const int LEVEL_UP_COST_GUNNER(30);
const int LEVEL_UP_COST_CANNON(40);
const int LEVEL_UP_COST_SHOGUN(50);

//�R���X�g���N�^
SpawnUnit::SpawnUnit()
	: mpUnitManager(nullptr)
	, mpPlayer(nullptr)
	, mUnitSelectFlag(false)
	, mUnitReinforcementFlag(false)
	, mInputMousePosX(0)
	, mInputMousePosY(0)
	, mSpawnFlag(false)
{

}

//�f�X�g���N�^
SpawnUnit::~SpawnUnit()
{

}

//������
void SpawnUnit::Initialize(UnitManager* pUnitManager, Player* pPlayer)
{
	//�|�C���^���擾
	mpUnitManager = pUnitManager;
	mpPlayer = pPlayer;
}

//Unit�̌Ăяo��
const bool& SpawnUnit::Spawn(const float& stageTilePosX	, const float& stageTilePosY)
{
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	//�X�e�[�W�f�[�^�̎擾
	STAGE_DATA tiledata = mpPlayer->GetStageData(static_cast<int>(stageTilePosX), static_cast<int>(stageTilePosY));

	Vector3 pos = { stageTilePosX, 0.0f, stageTilePosY };

	//�Ăяo��Unit�̑I��
	if (mUnitSelectFlag == true)
	{
		SpawnUnitSelect(pos);

		mSpawnFlag = false;
	}
	//Unit�̋���
	else if (mUnitReinforcementFlag == true)
	{
		UnitReinforcement(pos);

		mSpawnFlag = false;
	}
	//Unit���Ăяo����悤�ɂ���
	else if (tiledata.tileData == TILE_DATA::Unit_Scaffolding)
	{
		//�������u�Ԃ̃}�E�X�̍��W
		mInputMousePosX = inputManager.GetMouseState().x;
		mInputMousePosY = inputManager.GetMouseState().y;

		mUnitSelectFlag = true;
		mSpawnFlag = true;
	}
	//��������Unit�̑I��
	else if (
		tiledata.tileData != TILE_DATA::Unit_Scaffolding &&
		tiledata.tileData != TILE_DATA::EnemyStart &&
		tiledata.tileData != TILE_DATA::Goal &&
		tiledata.tileData != TILE_DATA::Road &&
		tiledata.tileData != TILE_DATA::NONE &&
		tiledata.tileData != TILE_DATA::Wall
		)
	{
		//�������u�Ԃ̃}�E�X�̍��W
		mInputMousePosX = inputManager.GetMouseState().x;
		mInputMousePosY = inputManager.GetMouseState().y;

		mUnitReinforcementFlag = true;
		mSpawnFlag = true;

		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
	}

	return mSpawnFlag;
}

/*****************************************************************************************************/

//Unit�̌Ăяo��
void SpawnUnit::SpawnUnitSelect(const Vector3& pos)
{
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	int posx = static_cast<int>(pos.x);
	int posy = static_cast<int>(pos.z);

	//�X�e�[�W�f�[�^�̎擾
	STAGE_DATA tiledata = mpPlayer->GetStageData(posx, posy);

	if (mUnitSelectFlag == true)
	{//1400,100,1500,200
		if (1400 <= mouseX && 100 <= mouseY && 1500 >= mouseX && 200 >= mouseY &&
			mpPlayer->GetMoney()+ SWORDFIGHTER_COST >= 0)
		{
			//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
			mpPlayer->SetTileNum(posx, posy
				, mpUnitManager->Spawn(pos, UNIT_TYPE::SWORDFIGHTER)
				, UNIT_LEVEL::LEVEL_1);//���m���o��

			UnitCost(UNIT_TYPE::SWORDFIGHTER);

			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else if (1400 <= mouseX && 210 <= mouseY && 1500 >= mouseX && 310 >= mouseY &&
			mpPlayer->GetMoney()+ ARCHER_COST >= 0)
		{
			//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
			mpPlayer->SetTileNum(posx, posy
				, mpUnitManager->Spawn(pos, UNIT_TYPE::ARCHER)
				, UNIT_LEVEL::LEVEL_1);//�|�����o��

			UnitCost(UNIT_TYPE::ARCHER);

			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else if (1400 <= mouseX && 320 <= mouseY && 1500 >= mouseX && 420 >= mouseY &&
			mpPlayer->GetMoney()+ GUNNER_COST >= 0)
		{
			//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
			mpPlayer->SetTileNum(posx, posy
				, mpUnitManager->Spawn(pos, UNIT_TYPE::GUNNER)
				, UNIT_LEVEL::LEVEL_1);//�S�C���o��

			UnitCost(UNIT_TYPE::GUNNER);

			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else if (1400 <= mouseX && 430 <= mouseY &&1500 >= mouseX && 530 >= mouseY &&
			mpPlayer->GetMoney()+ CANNON_COST >= 0)
		{
			//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
			mpPlayer->SetTileNum(posx, posy
				, mpUnitManager->Spawn(pos, UNIT_TYPE::CANNON)
				, UNIT_LEVEL::LEVEL_1);//��C���o��

			UnitCost(UNIT_TYPE::CANNON);

			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else if (1400 <= mouseX && 540 <= mouseY && 1500 >= mouseX && 640 >= mouseY &&
			mpPlayer->GetMoney()+ SHOGUN_COST >= 0)
		{
			//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
			mpPlayer->SetTileNum(posx, posy
				, mpUnitManager->Spawn(pos, UNIT_TYPE::SHOGUN)
				, UNIT_LEVEL::LEVEL_1);//��C���o��

			UnitCost(UNIT_TYPE::SHOGUN);

			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else
		{
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON2, SE_RUN::PLAY);
		}
	}

	mUnitSelectFlag = false;
}

//Unit�̋���
void SpawnUnit::UnitReinforcement(const Vector3& pos)
{
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mUnitReinforcementFlag == true)
	{
		if (//1400+100,100+100,1500+100,200+100 
			1400 <= inputManager.GetMouseState().x &&
			1500 >= inputManager.GetMouseState().x &&
			100 <= inputManager.GetMouseState().y &&
			200 >= inputManager.GetMouseState().y &&
			mpUnitManager->GetReinforcementFlag(pos) == false
			)
		{
			//Unit�̋���
			Reinforcement(mpPlayer->GetStageData(static_cast<int>(pos.x), static_cast<int>(pos.z)).tileData, pos);
		}
		else
		{
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON2, SE_RUN::PLAY);
		}
	}

	mUnitReinforcementFlag = false;
}

//����
void SpawnUnit::Reinforcement(const TILE_DATA& tileData, const Vector3& pos)
{
	switch (tileData)
	{
		case TILE_DATA::Swordfighter: {SetLevelData(pos); break; }
		case TILE_DATA::Archer: {SetLevelData(pos);	break; }
		case TILE_DATA::Gunner: {SetLevelData(pos);	break; }
		case TILE_DATA::Cannon: {SetLevelData(pos);	break; }
		case TILE_DATA::Shogun: {SetLevelData(pos);	break; }
		default:			break;
	}
}

//Unit�̃��x���f�[�^�̕ύX
void SpawnUnit::SetLevelData(const Vector3& pos)
{
	//�X�e�[�W�f�[�^�̎擾
	STAGE_DATA tiledata = mpPlayer->GetStageData(static_cast<int>(pos.x), static_cast<int>(pos.z));

	switch (tiledata.unit_Level)
	{
		case UNIT_LEVEL::LEVEL_1:
		{
			if (UnitReinforcementCost(tiledata.tileData, LEVEL_UP_COST_2) == true)
			{
				//Unit�̃��x���A�b�v
				mpUnitManager->SetUnitLevel(pos, UNIT_LEVEL::LEVEL_2);

				//���x���f�[�^�̏�������
				mpPlayer->SetTileNum(static_cast<int>(pos.x), static_cast<int>(pos.z), tiledata.tileData, UNIT_LEVEL::LEVEL_2);
			}

			break;
		}
		case UNIT_LEVEL::LEVEL_2:
		{
			if (UnitReinforcementCost(tiledata.tileData, LEVEL_UP_COST_3) == true)
			{
				//Unit�̃��x���A�b�v
				mpUnitManager->SetUnitLevel(pos, UNIT_LEVEL::LEVEL_3);

				//���x���f�[�^�̏�������
				mpPlayer->SetTileNum(static_cast<int>(pos.x), static_cast<int>(pos.z), tiledata.tileData, UNIT_LEVEL::LEVEL_3);
			}

			break;
		}
		case UNIT_LEVEL::LEVEL_3:
		{
			if (UnitReinforcementCost(tiledata.tileData, LEVEL_UP_COST_4) == true)
			{
				//Unit�̃��x���A�b�v
				mpUnitManager->SetUnitLevel(pos, UNIT_LEVEL::LEVEL_4);

				//���x���f�[�^�̏�������
				mpPlayer->SetTileNum(static_cast<int>(pos.x), static_cast<int>(pos.z), tiledata.tileData, UNIT_LEVEL::LEVEL_4);
			}

			break;
		}
		case UNIT_LEVEL::LEVEL_4:
		{
			if (UnitReinforcementCost(tiledata.tileData, LEVEL_UP_COST_5) == true)
			{
				//Unit�̃��x���A�b�v
				mpUnitManager->SetUnitLevel(pos, UNIT_LEVEL::LEVEL_5);

				//���x���f�[�^�̏�������
				mpPlayer->SetTileNum(static_cast<int>(pos.x), static_cast<int>(pos.z), tiledata.tileData, UNIT_LEVEL::LEVEL_5);
			}

			break;
		}
		default:
			break;
	}
}

//Unit���o���Ƃ��̋�
void SpawnUnit::UnitCost(const UNIT_TYPE& type)
{
	switch (type)
	{
		case UNIT_TYPE::SWORDFIGHTER:	{mpPlayer->SetMoney(SWORDFIGHTER_COST); break; }
		case UNIT_TYPE::ARCHER:			{mpPlayer->SetMoney(ARCHER_COST); break; }
		case UNIT_TYPE::GUNNER:			{mpPlayer->SetMoney(GUNNER_COST); break; }
		case UNIT_TYPE::CANNON:			{mpPlayer->SetMoney(CANNON_COST); break; }
		case UNIT_TYPE::SHOGUN:			{mpPlayer->SetMoney(SHOGUN_COST); break; }
		default:break;
	}
}

//Unit�̋����̃R�X�g
const bool& SpawnUnit::UnitReinforcementCost(const TILE_DATA& type, const int& money)
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	switch (type)
	{
		case TILE_DATA::Swordfighter:
		{
			if (mpPlayer->GetMoney() >= LEVEL_UP_COST_SWORDFIGHTER + money)
			{
				mpPlayer->SetMoney(-LEVEL_UP_COST_SWORDFIGHTER - money);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				return true;
			}

			break;
		}
		case TILE_DATA::Archer:
		{
			if (mpPlayer->GetMoney() >= LEVEL_UP_COST_ARCHER + money)
			{
				mpPlayer->SetMoney(-LEVEL_UP_COST_ARCHER - money);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				return true;
			}

			break;
		}
		case TILE_DATA::Gunner:
		{
			if (mpPlayer->GetMoney() >= LEVEL_UP_COST_GUNNER + money)
			{
				mpPlayer->SetMoney(-LEVEL_UP_COST_GUNNER - money);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				return true;
			}

			break;
		}
		case TILE_DATA::Cannon:
		{
			if (mpPlayer->GetMoney() >= LEVEL_UP_COST_CANNON + money)
			{
				mpPlayer->SetMoney(-LEVEL_UP_COST_CANNON - money);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				return true;
			}

			break;
		}
		case TILE_DATA::Shogun:
		{
			if (mpPlayer->GetMoney() >= LEVEL_UP_COST_SHOGUN + money)
			{
				mpPlayer->SetMoney(-LEVEL_UP_COST_SHOGUN - money);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				return true;
			}

			break;
		}
		default:break;
	}

	return false;
}