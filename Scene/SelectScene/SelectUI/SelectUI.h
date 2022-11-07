#pragma once
#include"../../IScene.h"

class Button;
class SelectStageLoad;

class SelectUI
{
private:

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

	int mStage_draw_num;

	//シーン移動のフェードのフラグ
	bool mMoveFadeFlag;

	bool mBackTitle_Flag;

	std::unique_ptr<SelectStageLoad> mpSelectStageLoad;

public:

	//コンストラクタ
	SelectUI();
	//デストラクタ
	~SelectUI();

	//初期化
	void Initialize();

	//更新
	const bool Update();

	//描画
	void Draw();

	const GAME_SCENE Title_Back();

private:

	//マウスをクリックしたときのイベント
	void ClickEvent(const int& stagenum);
};