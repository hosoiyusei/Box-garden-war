#include"pch.h"
#include"SpawnUnit.h"

#include"../UnitManager/UnitManager.h"
#include"Player.h"
#include"../UnitManager/Unit/UnitLevel.h"
#include"../GameUI/GameUI.h"

#include"../../TitleScene/Button/Button.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Spawn������Ƃ��̋�
const int SWORDFIGHTER_COST(10);
const int ARCHER_COST(20);
const int GUNNER_COST(30);
const int CANNON_COST(40);
const int SHOGUN_COST(50);

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
	, mSpawnFlag(false)
	, mpGameUI(nullptr)
{

}

//�f�X�g���N�^
SpawnUnit::~SpawnUnit()
{

}

//������
void SpawnUnit::Initialize(UnitManager* pUnitManager, Player* pPlayer, GameUI* pGameUI)
{
	//�|�C���^���擾
	mpUnitManager = pUnitManager;
	mpPlayer = pPlayer;
	mpGameUI = pGameUI;
}

//Unit�̌Ăяo��
const bool SpawnUnit::Spawn(const float& stageTilePosX	, const float& stageTilePosY)
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	//�X�e�[�W�f�[�^�̎擾
	STAGE_DATA tiledata = mpPlayer->GetStageData(static_cast<int>(stageTilePosX), static_cast<int>(stageTilePosY));

	Vector3 pos = { stageTilePosX, 0.0f, stageTilePosY };

	//�Ăяo��Unit�̑I��
	if (mUnitSelectFlag == true)
	{
		SpawnUnitSelect(pos);

		//if (inputManager.GetMouseState().x < 1300)
			//mSpawnFlag = false;
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

	const int posx = static_cast<int>(pos.x);
	const int posy = static_cast<int>(pos.z);

	//�X�e�[�W�f�[�^�̎擾
	STAGE_DATA tiledata = mpPlayer->GetStageData(posx, posy);

	if (mUnitSelectFlag == true)
	{
		if (mpPlayer->GetMoney() >= SWORDFIGHTER_COST&&
			mpGameUI->Summon_Unit_Button(UNIT_TYPE::SWORDFIGHTER)->When_the_mouse_cursor_enters_the_range() == true)
		{
			Unit_Spawn_Type(UNIT_TYPE::SWORDFIGHTER, pos);
		}
		else if (mpPlayer->GetMoney() >= ARCHER_COST &&
			mpGameUI->Summon_Unit_Button(UNIT_TYPE::ARCHER)->When_the_mouse_cursor_enters_the_range() == true)
		{
			Unit_Spawn_Type(UNIT_TYPE::ARCHER, pos);
		}
		else if (mpPlayer->GetMoney() >= GUNNER_COST  &&
			mpGameUI->Summon_Unit_Button(UNIT_TYPE::GUNNER)->When_the_mouse_cursor_enters_the_range() == true)
		{
			Unit_Spawn_Type(UNIT_TYPE::GUNNER, pos);
		}
		else if (mpPlayer->GetMoney() >= CANNON_COST  &&
			mpGameUI->Summon_Unit_Button(UNIT_TYPE::CANNON)->When_the_mouse_cursor_enters_the_range() == true)
		{
			Unit_Spawn_Type(UNIT_TYPE::CANNON, pos);
		}
		else if (mpPlayer->GetMoney() >= SHOGUN_COST  &&
			mpGameUI->Summon_Unit_Button(UNIT_TYPE::SHOGUN)->When_the_mouse_cursor_enters_the_range() == true)
		{
			Unit_Spawn_Type(UNIT_TYPE::SHOGUN, pos);
		}
		else if (mpPlayer->Stage_Target_Duplicate() == true)
		{
			When_the_targets_overlap(pos);
		}
		else if (inputManager.GetMouseState().x < 1300)
		{
			mUnitSelectFlag = false;
			mSpawnFlag = false;
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON2, SE_RUN::PLAY);
		}
	}
}

//Unit�̋���
void SpawnUnit::UnitReinforcement(const Vector3& pos)
{
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mUnitReinforcementFlag == true)
	{
		if (
			1400 <= inputManager.GetMouseState().x &&
			1500 >= inputManager.GetMouseState().x &&
			100 <= inputManager.GetMouseState().y &&
			200 >= inputManager.GetMouseState().y || 
			mpPlayer->Stage_Target_Duplicate() == true)
		{
			//Unit�̋���
			if (mpUnitManager->GetReinforcementFlag(pos) == false)
				Reinforcement(mpPlayer->GetStageData(static_cast<int>(pos.x), static_cast<int>(pos.z)).tileData, pos);
		}
		else if (1400 <= inputManager.GetMouseState().x &&
			1500 >= inputManager.GetMouseState().x &&
			300 <= inputManager.GetMouseState().y &&
			400 >= inputManager.GetMouseState().y)
		{
			DeleteUnit();//���j�b�g�̍폜
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
		case UNIT_TYPE::SWORDFIGHTER:	{mpPlayer->SetMoney(-SWORDFIGHTER_COST); break; }
		case UNIT_TYPE::ARCHER:			{mpPlayer->SetMoney(-ARCHER_COST); break; }
		case UNIT_TYPE::GUNNER:			{mpPlayer->SetMoney(-GUNNER_COST); break; }
		case UNIT_TYPE::CANNON:			{mpPlayer->SetMoney(-CANNON_COST); break; }
		case UNIT_TYPE::SHOGUN:			{mpPlayer->SetMoney(-SHOGUN_COST); break; }
		default:break;
	}
}

//Unit�̋����̃R�X�g
const bool SpawnUnit::UnitReinforcementCost(const TILE_DATA& type, const int& money)
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

void SpawnUnit::Unit_Spawn_Type(
	const UNIT_TYPE& type
	, const Vector3& pos)
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	const int posx = static_cast<int>(pos.x);
	const int posy = static_cast<int>(pos.z);

	//Unit�̃X�|�[���ƃX�e�[�W�f�[�^�̏�������
	mpPlayer->SetTileNum(posx, posy
		, mpUnitManager->Spawn(pos, type)
		, UNIT_LEVEL::LEVEL_1);//���m���o��

	UnitCost(type);
	mUnitSelectFlag = false;
	mSpawnFlag = false;
	soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
}

void SpawnUnit::When_the_targets_overlap(const Vector3& pos)
{
	InputManager& inputManager = InputManager::GetInstance();

	if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		if (inputManager.GetMouseState().scrollWheelValue == 0 &&
			mpPlayer->GetMoney() >= SWORDFIGHTER_COST)
		{
			Unit_Spawn_Type(UNIT_TYPE::SWORDFIGHTER, pos);
		}
		else if (inputManager.GetMouseState().scrollWheelValue == -120 &&
			mpPlayer->GetMoney() >= ARCHER_COST ||
			inputManager.GetMouseState().scrollWheelValue == 480 &&
			mpPlayer->GetMoney() >= ARCHER_COST)
		{
			Unit_Spawn_Type(UNIT_TYPE::ARCHER, pos);
		}
		else if (inputManager.GetMouseState().scrollWheelValue == -240 &&
			mpPlayer->GetMoney() >= GUNNER_COST ||
			inputManager.GetMouseState().scrollWheelValue == 360 &&
			mpPlayer->GetMoney() >= GUNNER_COST)
		{
			Unit_Spawn_Type(UNIT_TYPE::GUNNER, pos);
		}
		else if (inputManager.GetMouseState().scrollWheelValue == -360 &&
			mpPlayer->GetMoney() >= CANNON_COST||
			inputManager.GetMouseState().scrollWheelValue == 240 &&
			mpPlayer->GetMoney() >= CANNON_COST)
		{
			Unit_Spawn_Type(UNIT_TYPE::CANNON, pos);
		}
		else if (inputManager.GetMouseState().scrollWheelValue == -480 &&
			mpPlayer->GetMoney() >= SHOGUN_COST ||
			inputManager.GetMouseState().scrollWheelValue == 120 &&
			mpPlayer->GetMoney() >= SHOGUN_COST)
		{
			Unit_Spawn_Type(UNIT_TYPE::SHOGUN, pos);
		}
	}
}

//���j�b�g�̍폜
void SpawnUnit::DeleteUnit()
{
	mpUnitManager->Delete(mpPlayer->GetPlayerPos());
}