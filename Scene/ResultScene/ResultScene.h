#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"

class Button;

class ResultScene :public IScene
{
private:

	float mSceneFade;

	VIEW mCameraView;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

public:

	//コンストラクタ
	ResultScene();
	//デストラクタ
	~ResultScene();

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