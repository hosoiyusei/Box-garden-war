#pragma once
#include<SimpleMath.h>
#include<vector>
#include"Scene/Utility.h"
#include"../Collision/Capsule.h"
#include"SpawnUnit.h"
#include"StageTileData.h"
#include"../UnitManager/Unit/UnitLevel.h"
#include"../ItemManager/Item/ItemType.h"
#include"Player_Param.h"

//前方宣言
class StageRead;
class UnitManager;
class StageDraw;
class ItemManager;
class GameUI;

class Player :private SpawnUnit
{
private:

	//カメラのパラメーター
	VIEW mCameraView, mCameraView2;

	//プレイヤーの座標
	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mGoalPos;

	DirectX::SimpleMath::Vector3 mSecondTarget;

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

	//プレイヤーのステージデータ
	std::vector<std::vector<STAGE_DATA>> mStageData;

	//ステージのCapsuleとの当たり判定
	Capsule mCapsule;

	//ステージの立幅と横幅
	int mHorizontal, mVertical;

	//プレイヤーの体力
	int mLife;

	//金
	int mMoney;

	//クリアフラグ
	bool mClear;

	//ゲームオーバーフラグ
	bool mGameOver;

	//Unit呼び出しフラグ
	bool mUnitSpawnFlag;

	//カメラを動かしているかどうかのフラグ
	bool mCameraMoveFlag;

	//ターゲットの大きさ
	float mTargetSize;

	//ユニットが出すことが出来るかどうかのフラグ
	bool mFlag_of_whether_the_unit_can_be_put_out;

	//増えるかね
	int mScrollMoney;

	ITEM_TYPE mItemType;

	//ユニットの管理者のポインタ
	UnitManager* mpUnitManager;

	//ステージ描画のポインタ
	StageDraw* mpStageDraw;

	ItemManager* mpItemManager;

	Player_Param mParam;

	//点滅
	float mBlinking;

	GameUI* mpGameUI;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize(
		StageRead* pStageRead
		, UnitManager* pUnitManager
		, StageDraw* pStageDraw
		, Player* pPlayer
		, ItemManager* pItemManager
		, GameUI* pGameUI);

	//更新
	void Update();

	//描画
	void Draw();

	//ダメージを受ける
	void LifeDamage();

	//クリアフラグを受け取る
	void SetClear(const bool& clear) { mClear = clear; }

	//クリアフラグを返す
	const bool GetClear() { return mClear; }

	//ゲームオーバーのフラグを返す
	const bool GetGameOver() { return mGameOver; }

	//カメラのパラメーターを返す
	const VIEW GetCameraParam() { return mCameraView; }

	//金を増やす
	void SetMoney(const int money);

	//金の取得
	const int GetMoney() { return mScrollMoney; }

	//Unitの選択フラグを返す
	const bool GetUnitSelectFlag(){return SpawnUnit::GetUnitSelectFlag();}

	//Unitの強化フラグを返す
	const bool GetReinforcementFlag(){return SpawnUnit::GetReinforcementFlag();}

	//ステージのデータの書き換え
	void SetTileNum(
		const int& x
		, const int& y
		, const TILE_DATA& newTileData
		, const UNIT_LEVEL& newLevelData)
	{
		mStageData[y][x].tileData = newTileData; 
		mStageData[y][x].unit_Level = newLevelData;
	}

	//ステージの配列の番号を返す
	const STAGE_DATA GetStageData(const int& x, const int& y) { return mStageData[y][x]; }

	const DirectX::SimpleMath::Vector3 GetPlayerPos() { return mPos; }

	//アイテムをセット
	void SetItem(const ITEM_TYPE& type) { mItemType = type; }

	//プレイヤーの持つアイテム
	const ITEM_TYPE GetPlayerItem() { return mItemType; }

	//Targetが重なっているとき
	const bool Stage_Target_Duplicate();

	void SetFlag_of_whether_the_unit_can_be_put_out(const bool& set) { mFlag_of_whether_the_unit_can_be_put_out = set; }

	const int GetPlayerLife() { return mLife; }

	const bool Get_Unit_Spawn_Flag() { return mUnitSpawnFlag; }

private:

	//プレイヤーの移動
	void CameraMove();

	//Unitをスポーン
	void UnitSpawn();

	//スクリーン座標をワールド座標に変換する行列を作成する関数 
	const DirectX::SimpleMath::Matrix CreateMatrix_Screen2World();

	//マウスレイキャスト
	void MouseRayCast();

	//初期化時のステージデータの設定
	const TILE_DATA SetStageData(const int& datanum);

	//倍速
	void SpeedUp();

	//一時停止
	void Pause();

	void GetItem();

	void UseItem();

	//ステージとの交点を求める
	const DirectX::SimpleMath::Vector3 IntersectPlaneAndLine(
		const DirectX::SimpleMath::Vector3&  A,   //線分始点
		const DirectX::SimpleMath::Vector3&  B,   //線分終点
		const DirectX::SimpleMath::Plane&     PL); //平面

	//ユニットの攻撃範囲の描画
	void Drawing_the_attack_range_of_the_unit();
};