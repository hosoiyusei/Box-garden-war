#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"

class SelectUI;

class SelectScene :public IScene
{
private:

	VIEW mCameraView;

	//ロードするステージの番号
	int mStageNum;

	std::unique_ptr<SelectUI> mpSelectUI;

	float mSceneFade;

	bool mMoveFadeFlag;

public:

	//コンストラクタ
	SelectScene();
	//デストラクタ
	~SelectScene();

	//初期化
	void Initialize() override;

	//更新
	GAME_SCENE Update(const DX::StepTimer& timer) override;

	//描画
	void Draw() override;
	void Draw2()override {};

	void Forward()override {};

	//終了処理
	void Finalize() override;

};