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

class UnitManager
{
private:

	//ユニットの配列
	std::vector<std::unique_ptr<Unit>> mpUnit;

public:

	//コンストラクタ
	UnitManager();
	//デストラクタ
	~UnitManager();

	//初期化
	void Initialize(
		EnemyManager* pEnemyManager
		, BulletManager* pBulletManager
	, EffectManager* pEffectManager);

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

	//ユニットの削除
	void Delete(const DirectX::SimpleMath::Vector3& pos);

	//強化中のフラグを返す
	const bool& GetReinforcementFlag(const DirectX::SimpleMath::Vector3& pos);

private:

	//Unitのパワーアップ
	void UnitPowerUp(Unit* pUnit);

	//Unitの種類からtileデータを返す
	const TILE_DATA& UnitTypeData(const UNIT_TYPE& unitType);
};