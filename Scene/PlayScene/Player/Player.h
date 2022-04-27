#pragma once
#include<SimpleMath.h>
#include<vector>
#include"Scene/Utility.h"
#include"../Collision/Capsule.h"
#include"SpawnUnit.h"
#include"StageTileData.h"
#include"../UnitManager/Unit/UnitLevel.h"
#include"../ItemManager/Item/ItemType.h"

//前方宣言
class StageRead;
class UnitManager;
class StageDraw;
class ItemManager;

class Player :private SpawnUnit
{
private:

	//カメラのパラメーター
	VIEW mCameraView;

	//プレイヤーの座標
	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mGoalPos;

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

	//カメラの高さ
	float mCameraHeight;

	//ターゲットの大きさ
	float mTargetSize;

	ITEM_TYPE mItemType;

	//ユニットの管理者のポインタ
	UnitManager* mpUnitManager;

	//ステージ描画のポインタ
	StageDraw* mpStageDraw;

	ItemManager* mpItemManager;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize(StageRead* pStageRead, UnitManager* pUnitManager, StageDraw* pStageDraw, Player* pPlayer, ItemManager* pItemManager);

	//更新
	void Update();

	//描画
	void Draw();

	//ダメージを受ける
	void LifeDamage();

	//クリアフラグを受け取る
	void SetClear(const bool& clear) { mClear = clear; }

	//クリアフラグを返す
	const bool& GetClear() { return mClear; }

	//ゲームオーバーのフラグを返す
	const bool& GetGameOver() { return mGameOver; }

	//カメラのパラメーターを返す
	const VIEW& GetCameraParam() { return mCameraView; }

	//金を増やす
	void SetMoney(const int money);

	//金の取得
	const int& GetMoney() { return mMoney; }

	//Unitの選択フラグを返す
	const bool& GetUnitSelectFlag(){return SpawnUnit::GetUnitSelectFlag();}

	//Unitの強化フラグを返す
	const bool& GetReinforcementFlag(){return SpawnUnit::GetReinforcementFlag();}

	//マウスのX座標を返す
	const int& GetInputMousePosX(){return SpawnUnit::GetInputMousePosX();}

	//マウスのY座標を返す
	const int& GetInputMousePosY(){return SpawnUnit::GetInputMousePosY();}

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
	const STAGE_DATA& GetStageData(const int& x, const int& y) { return mStageData[y][x]; }

	const DirectX::SimpleMath::Vector3& GetPlayerPos() { return mPos; }

	//アイテムをセット
	void SetItem(const ITEM_TYPE& type) { mItemType = type; }

	//プレイヤーの持つアイテム
	const ITEM_TYPE& GetPlayerItem() { return mItemType; }

private:

	//プレイヤーの移動
	void CameraMove();

	//Unitをスポーン
	void UnitSpawn();

	//スクリーン座標をワールド座標に変換する行列を作成する関数 
	const DirectX::SimpleMath::Matrix& CreateMatrix_Screen2World();

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

	void NumDraw(const int& num);
};