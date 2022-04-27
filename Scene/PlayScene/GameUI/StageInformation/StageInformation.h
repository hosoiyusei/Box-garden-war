#pragma once
#include"../../Player/StageTileData.h"
#include"../../Player/StageTileData.h"

class Player;

class StageInformation
{
private:

public:

	//コンストラクタ
	StageInformation();
	//デストラクタ
	~StageInformation();

	//描画
	void Draw(Player* pPlayer);

private:

	//レベルをintで返す
	const int& GetLevel(const UNIT_LEVEL& level);

	void UnitType(const TILE_DATA data);
};