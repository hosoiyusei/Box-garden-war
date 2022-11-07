#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"
#include<SimpleMath.h>

//前方宣言
class StageRead;
class StageDraw;
class EnemyManager;
class Player;
class UnitManager;
class BulletManager;
class EffectManager;
class CollisionManager;
class GameUI;
class ItemManager;
class Tutorial;

class PlayScene:public IScene
{
private:

	//カメラのパラメーター
	VIEW mCameraView;

	//タイマー
	DX::StepTimer mTimer;

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

	int mResultTimer;

	bool mInitialFlag;

	float mFade;

	bool mFadeFlag;

	float mResultEffect;

	//フェードの大きさ
	float mFadeScale;

	//フェードの調整
	float mFade_adjustment;

	//フェードのサイズ調整
	float mFadeSize_adjustment;

	//ステージデータのポインタ
	std::unique_ptr<StageRead> mpStageRead;
	//ステージを描画するポインタ
	std::unique_ptr<StageDraw> mpStageDraw;
	//Enemyの管理者のポインタ
	std::unique_ptr<EnemyManager> mpEnemyManager;
	//プレイヤーのポインタ
	std::unique_ptr<Player> mpPlayer;
	//Unitの管理者もポインタ
	std::unique_ptr<UnitManager> mpUnitManager;
	//弾の管理者のポインタ
	std::unique_ptr<BulletManager> mpBulletManager;
	//エフェクトの管理者のポインタ
	std::unique_ptr<EffectManager> mpEffectManager;
	//当たり判定の管理者のポインタ
	std::unique_ptr<CollisionManager> mpCollisionManager;

	//ゲームのUI
	std::unique_ptr<GameUI> mpGameUI;

	//アイテムの管理者のポインタ
	std::unique_ptr<ItemManager> mpItemManager;

	//チュートリアル
	std::unique_ptr<Tutorial> mpTutorial;

public:

	//コンストラクタ
	PlayScene();
	//デストラクタ
	~PlayScene();

	//初期化
	void Initialize() override;

	//更新
	GAME_SCENE Update(const DX::StepTimer& timer) override;

	//描画
	void Draw() override;
	void Draw2()override;

	void Forward()override;

	//終了処理
	void Finalize() override;
};