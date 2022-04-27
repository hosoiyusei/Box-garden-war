#pragma once
#include"StageTileData.h"
#include"../UnitManager/Unit/UnitType.h"

//前方宣言
class UnitManager;
class Player;

class SpawnUnit
{
private:

	UnitManager* mpUnitManager;

	Player* mpPlayer;

	bool mUnitSelectFlag			//Unitの選択フラグ
		, mUnitReinforcementFlag	//Unitの強化フラグ
		, mSpawnFlag;				//Unitの呼び出しフラグ

	//マウスの入力時の座標
	int   mInputMousePosX, mInputMousePosY;

public:

	//コンストラクタ
	SpawnUnit();
	//デストラクタ
	~SpawnUnit();

	//初期化
	void Initialize(UnitManager* pUnitManager, Player* pPlayer);

	//Unitを呼び出す
	const bool& Spawn(const float& stageTilePosX, const float& stageTilePosY);

	//Unitの選択フラグを返す
	const bool& GetUnitSelectFlag() { return mUnitSelectFlag; }

	//Unitの強化フラグを返す
	const bool& GetReinforcementFlag(){ return mUnitReinforcementFlag; }

	//マウスのX座標を返す
	const int& GetInputMousePosX(){ return mInputMousePosX; }

	//マウスのY座標を返す
	const int& GetInputMousePosY() { return mInputMousePosY; }

private:

	//呼び出すUnitを選択
	void SpawnUnitSelect(const DirectX::SimpleMath::Vector3& pos);

	//Unitの強化
	void UnitReinforcement(const DirectX::SimpleMath::Vector3& pos);

	//強化する
	void Reinforcement(const TILE_DATA& tileDat, const DirectX::SimpleMath::Vector3& pos);

	//Unitのレベルデータの変更
	void SetLevelData(const DirectX::SimpleMath::Vector3& pos);

	//Unitを出すときの金
	void UnitCost(const UNIT_TYPE& type);

	//Unitの強化のコスト
	const bool& UnitReinforcementCost(const TILE_DATA& type, const int& money);
};