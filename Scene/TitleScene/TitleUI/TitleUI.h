#pragma once
#include"../../Scene.h"

class Button;

class TitleUI
{
private:

	//設定のフラグ
	bool mSettingFlag;

	GAME_SCENE mScene;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

public:

	//コンストラクタ
	TitleUI();
	//デストラクタ
	~TitleUI();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//シーンを返す
	GAME_SCENE GetScene() { return mScene; }

private:

	//設定の更新
	void Setting_Update();

	//設定の描画
	void DrawSetting();

	//音量のゲージの描画
	void Sound_gage_draw();
};