#pragma once
#include<SimpleMath.h>
#include<vector>
#include"Unit/UnitType.h"
#include"../Player/StageTileData.h"
#include"Unit/UnitLevel.h"

//前方宣言
class Unit;
class EnemyManager;
class BulletManager;
class EffectManager;
class Player;

class UnitManager
{
private:

	//ユニットの配列
	std::vector<std::unique_ptr<Unit>> mpUnit;

	Player* mpPlayer;

public:

	//コンストラクタ
	UnitManager();
	//デストラクタ
	~UnitManager();

	//初期化
	void Initialize(
		EnemyManager* pEnemyManager
		, BulletManager* pBulletManager
		, EffectManager* pEffectManager
		, Player* mpPlayer);

	//更新
	void Update();

	//描画
	void Draw();

	//Unitのエフェクトの描画
	void EffectDraw();

	//スポーン
	const TILE_DATA Spawn(
		const DirectX::SimpleMath::Vector3& pos
		,const UNIT_TYPE& type);

	//Unitのレベルの設定
	void SetUnitLevel(
		const DirectX::SimpleMath::Vector3& pos
		,const UNIT_LEVEL& level);

	//強化中のフラグを返す
	const bool GetReinforcementFlag(const DirectX::SimpleMath::Vector3& pos);

	//ユニットの削除
	void Delete(const DirectX::SimpleMath::Vector3& pos);

	//攻撃力
	const int GetPower(const DirectX::SimpleMath::Vector3& pos);

	//Unitのパワーアップ
	void UnitPowerUp(Unit* pUnit);

	//パワーアップの解除
	void Release_power_ups();

private:

	//Unitの種類からtileデータを返す
	const TILE_DATA UnitTypeData(const UNIT_TYPE& unitType);
};