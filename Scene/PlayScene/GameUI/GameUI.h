#pragma once

//前方宣言
class Player;
class ArrowUI;
class SummonUnitUI;
class Reinforcement;
class StageInformation;

class GameUI
{
private:

	//プレイヤーのポインタ
	Player* mpPlayer;

	//早送り・一時停止のUI
	std::unique_ptr<ArrowUI> mpArrowUI;

	//Unitを呼び出すときのUI
	std::unique_ptr<SummonUnitUI> mpSummonUnitUI;

	//Unitを強化するときのUI
	std::unique_ptr<Reinforcement> mpReinforcement;

	//ステージの情報のUI
	std::unique_ptr<StageInformation> mpStageInformation;

public:

	//コンストラクタ
	GameUI();
	//デストラクタ
	~GameUI();

	//初期化
	void Initialize(Player* pPlayer);

	//描画
	void Draw();

private:

	void DrawNumbers(const int& number,const int& x,const int& y);
};