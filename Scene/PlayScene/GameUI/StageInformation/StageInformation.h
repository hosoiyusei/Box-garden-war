#pragma once
#include"../../Player/StageTileData.h"
#include"../../Player/StageTileData.h"

class Player;
class UnitManager;

class StageInformation
{
private:

	UnitManager* mpUnitManager;

public:

	//コンストラクタ
	StageInformation();
	//デストラクタ
	~StageInformation() = default;

	void Initialize(UnitManager* pUnitManager);

	//描画
	void Draw(Player* pPlayer);

private:

	//レベルをintで返す
	const int GetLevel(const UNIT_LEVEL& level);

	void UnitType(const TILE_DATA data);

	void Placeable_area();
};