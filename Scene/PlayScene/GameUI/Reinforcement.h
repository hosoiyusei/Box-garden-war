#pragma once
#include"../UnitManager/Unit/UnitLevel.h"
#include"../Player/StageTileData.h"

class Player;
class Button;

class Reinforcement
{
private:

	UNIT_LEVEL mLevel;

	TILE_DATA mType;

	int mWindowPosX;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

public:

	Reinforcement();
	~Reinforcement();

	void Initialize();

	void Update(Player* mpPlayer);

	void Draw(Player* mpPlayer);

private:

	int RequestedAmount(STAGE_DATA data);

	int LevelRequestedAmount(STAGE_DATA data);
};