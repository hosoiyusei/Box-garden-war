#pragma once
#include"../../Player/StageTileData.h"
#include"../../Player/StageTileData.h"

class Player;

class StageInformation
{
private:

public:

	//�R���X�g���N�^
	StageInformation();
	//�f�X�g���N�^
	~StageInformation();

	//�`��
	void Draw(Player* pPlayer);

private:

	//���x����int�ŕԂ�
	const int& GetLevel(const UNIT_LEVEL& level);

	void UnitType(const TILE_DATA data);
};