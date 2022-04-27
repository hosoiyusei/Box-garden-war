#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"

//前方宣言
class TitleUI;

class TitleScene:public IScene
{
private:

	VIEW mCameraView;

	std::unique_ptr<TitleUI> mpTitleUI;

	bool mInitialFlag;

public:

	//コンストラクタ
	TitleScene();
	//デストラクタ
	~TitleScene();

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