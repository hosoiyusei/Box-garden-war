#pragma once
#include"../UnitManager/Unit/UnitLevel.h"
#include"../Player/StageTileData.h"
class Player;

class Reinforcement
{
private:

	UNIT_LEVEL mLevel;

	TILE_DATA mType;

	int mWindowPosX;

public:

	Reinforcement();
	~Reinforcement();

	void Draw(Player* mpPlayer);

private:

	int RequestedAmount(STAGE_DATA data);

	int LevelRequestedAmount(STAGE_DATA data);
};