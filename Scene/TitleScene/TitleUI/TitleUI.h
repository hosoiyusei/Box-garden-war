#pragma once
#include"../../Scene.h"

class TitleUI
{
private:

	//設定のフラグ
	bool mSettingFlag;

	GAME_SCENE mScene;

public:

	//コンストラクタ
	TitleUI();
	//デストラクタ
	~TitleUI();

	//更新
	void Update();

	//描画
	void Draw();

	//シーンを返す
	GAME_SCENE GetScene() { return mScene; }

private:

	//設定の描画
	void DrawSetting();
};