#pragma once

class Player;

class Tutorial
{
private:

	//チュートリアルのイベントの番号
	int mTutorial_event_number;

	//一時保存用ステージ座標
	int mX, mY;

	int mTutorial_UI_Timer;

	Player* mpPlayer;

public:

	Tutorial();
	~Tutorial() = default;

	//初期化
	void Initialize(Player* pPlayer);

	//更新
	void Update();

	//描画
	void Draw();

	//描画2
	void Draw2();

	//イベントの番号
	const int GetmTutorial_event_number() { return mTutorial_event_number; }

	//イベントの番号のセット
	void SetmTutorial_event_number(const int& eventnum) { mTutorial_event_number = eventnum; }

private:

	//テキストの再生
	void Play_text(
		const wchar_t* txt
		, const DirectX::XMFLOAT2& pos
		, const int& event_num
		, DirectX::FXMVECTOR& color = DirectX::Colors::White);

	//マウスが範囲内にあるかの判定
	const bool Determining_if_the_mouse_is_on(const RECT& rect);

	//チュートリアルのUI
	void Tutorial_Guide_UI(const RECT& rect, const int& event_num);

	//チュートリアルのUI
	void Tutorial_Guide_UI2(const int& event_num);
};