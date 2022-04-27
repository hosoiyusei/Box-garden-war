#pragma once
#include"StageTileData.h"
#include"../UnitManager/Unit/UnitType.h"

//�O���錾
class UnitManager;
class Player;

class SpawnUnit
{
private:

	UnitManager* mpUnitManager;

	Player* mpPlayer;

	bool mUnitSelectFlag			//Unit�̑I���t���O
		, mUnitReinforcementFlag	//Unit�̋����t���O
		, mSpawnFlag;				//Unit�̌Ăяo���t���O

	//�}�E�X�̓��͎��̍��W
	int   mInputMousePosX, mInputMousePosY;

public:

	//�R���X�g���N�^
	SpawnUnit();
	//�f�X�g���N�^
	~SpawnUnit();

	//������
	void Initialize(UnitManager* pUnitManager, Player* pPlayer);

	//Unit���Ăяo��
	const bool& Spawn(const float& stageTilePosX, const float& stageTilePosY);

	//Unit�̑I���t���O��Ԃ�
	const bool& GetUnitSelectFlag() { return mUnitSelectFlag; }

	//Unit�̋����t���O��Ԃ�
	const bool& GetReinforcementFlag(){ return mUnitReinforcementFlag; }

	//�}�E�X��X���W��Ԃ�
	const int& GetInputMousePosX(){ return mInputMousePosX; }

	//�}�E�X��Y���W��Ԃ�
	const int& GetInputMousePosY() { return mInputMousePosY; }

private:

	//�Ăяo��Unit��I��
	void SpawnUnitSelect(const DirectX::SimpleMath::Vector3& pos);

	//Unit�̋���
	void UnitReinforcement(const DirectX::SimpleMath::Vector3& pos);

	//��������
	void Reinforcement(const TILE_DATA& tileDat, const DirectX::SimpleMath::Vector3& pos);

	//Unit�̃��x���f�[�^�̕ύX
	void SetLevelData(const DirectX::SimpleMath::Vector3& pos);

	//Unit���o���Ƃ��̋�
	void UnitCost(const UNIT_TYPE& type);

	//Unit�̋����̃R�X�g
	const bool& UnitReinforcementCost(const TILE_DATA& type, const int& money);
};