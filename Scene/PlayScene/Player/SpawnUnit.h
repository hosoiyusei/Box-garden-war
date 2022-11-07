#pragma once
#include"StageTileData.h"
#include"../UnitManager/Unit/UnitType.h"

//前方宣言
class UnitManager;
class Player;
class GameUI;

class SpawnUnit
{
private:

	UnitManager* mpUnitManager;

	Player* mpPlayer;

	bool mUnitSelectFlag			//Unitの選択フラグ
		, mUnitReinforcementFlag	//Unitの強化フラグ
		, mSpawnFlag;				//Unitの呼び出しフラグ

	GameUI* mpGameUI;

public:

	//コンストラクタ
	SpawnUnit();
	//デストラクタ
	~SpawnUnit();

	//初期化
	void Initialize(UnitManager* pUnitManager, Player* pPlayer,GameUI* pGameUI);

	//Unitを呼び出す
	const bool Spawn(const float& stageTilePosX, const float& stageTilePosY);

	//Unitの選択フラグを返す
	const bool GetUnitSelectFlag() { return mUnitSelectFlag; }

	//Unitの強化フラグを返す
	const bool GetReinforcementFlag(){ return mUnitReinforcementFlag; }

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
	const bool UnitReinforcementCost(const TILE_DATA& type, const int& money);

	//SpawnするUnitの種類
	void Unit_Spawn_Type(
		const UNIT_TYPE& type
		, const DirectX::SimpleMath::Vector3& pos);

	//UnitのSpawn
	void When_the_targets_overlap(const DirectX::SimpleMath::Vector3& pos);

	//ユニットの削除
	void DeleteUnit();
};