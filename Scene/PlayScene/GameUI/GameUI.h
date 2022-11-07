#pragma once
#include"SummonUnitUI.h"

//前方宣言
class Player;
class ArrowUI;
class Tutorial;

class Reinforcement;
class StageInformation;
class EnemyManager;
class UnitManager;
class Button;
class PlaySetting;

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

	std::unique_ptr<PlaySetting> mpPlaySetting;

	EnemyManager* mpEnemyManager;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

	bool mBackSelectFlag;

	bool mSettingFlag;

public:

	//コンストラクタ
	GameUI();
	//デストラクタ
	~GameUI();

	//初期化
	void Initialize(EnemyManager* pEnemyManager, Player* pPlayer, UnitManager* pUnitManager, Tutorial* pTutorial);

	void Update();

	//描画
	void Draw();

	Button* Summon_Unit_Button(const UNIT_TYPE& type);

	const bool BackSelectScene();

private:

	void DrawNumbers(const int& number,const int& x,const int& y);
};