#include"pch.h"
#include"GameUI.h"

#include"../Player/Player.h"
#include"ArrowUI.h"

#include"Reinforcement.h"
#include"StageInformation/StageInformation.h"
#include"../EnemyManager/EnemyManager.h"
#include"../../TitleScene/Button/Button.h"
#include"PlaySetting.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const int NUM_SIZE_X = 18 * 2;
const int NUM_SIZE_Y = 18 * 4;
const int TIMER_POS_Y = 250;

const std::string BACKSELECT("セレクトへ戻る");

GameUI::GameUI()
	: mpPlayer(nullptr)
	, mpArrowUI(nullptr)
	, mpSummonUnitUI(nullptr)
	, mpReinforcement(nullptr)
	, mpStageInformation(nullptr)
	, mpEnemyManager(nullptr)
	, mBackSelectFlag(false)
	, mpPlaySetting(nullptr)
	, mSettingFlag(false)
{

}

GameUI::~GameUI(){}

void GameUI::Initialize(EnemyManager* pEnemyManager, Player* pPlayer, UnitManager* pUnitManager, Tutorial* pTutorial)
{
	mpPlayer = pPlayer;
	mpEnemyManager = pEnemyManager;

	mpArrowUI = std::make_unique<ArrowUI>();

	mpSummonUnitUI = std::make_unique<SummonUnitUI>();

	mpReinforcement = std::make_unique<Reinforcement>();

	mpStageInformation = std::make_unique<StageInformation>();

	mpPlaySetting= std::make_unique<PlaySetting>();

	mpStageInformation->Initialize(pUnitManager);
	mpArrowUI->Initialize();
	mpSummonUnitUI->Initialize(pPlayer, pTutorial);
	mpReinforcement->Initialize();
	mpPlaySetting->Initialize();

	mpButtons[BACKSELECT] = std::make_unique<Button>();

	//描画座標の設定
	mpButtons[BACKSELECT]->SetRECT(10, 10, 60, 60);
}

void GameUI::Update()
{
	mpSummonUnitUI->Update();
	mpReinforcement->Update(mpPlayer);

	if (mpButtons[BACKSELECT]->Determining_if_the_mouse_is_on() == true)
	{
		if (mSettingFlag == false)
		{
			mSettingFlag = true;
		}
		else
			mSettingFlag = false;
	}

	if (mSettingFlag == true)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		mpPlaySetting->Update();
		mBackSelectFlag = mpPlaySetting->GetBackSelectFlag();
	}
	else
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);
	}
}

void GameUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	mpArrowUI->Draw();

	//Unitを呼び出すときのUI
	mpSummonUnitUI->Draw(mpPlayer->GetUnitSelectFlag());

	//強化するときのUI
	mpReinforcement->Draw(mpPlayer);

	mpStageInformation->Draw(mpPlayer);

	mpButtons[BACKSELECT]->DrawButton({500,500}, TEXTURE2D::WINDOW, L" ", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::White);

	pObject.GetTexture2D()->Draw(TEXTURE2D::GEAR, { 0,0,300,300 }, { 10, 10, 60, 60 });

	//所持金額の描画
	RECT rect1, rect2;
	rect1 = { 0,0,324,340 };
	rect2 = { 1360,30,1410,80 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MONEY, rect1, rect2);
	DrawNumbers(mpPlayer->GetMoney(), 1550, 0);

	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, { 500,500 }, { 650,2,950,40 },Color(0.0f,0.0f,0.0f,0.5f));

	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, { 500,500 }, { 799,7,801,35 }, Colors::White);


	//残りの敵の数の表示位置
	int Display_position_of_number_of_remaining_enemies = -60;

	pObject.GetText()->DrawInt(
		mpEnemyManager->GetNumber_of_remaining_Enemy()
		, XMFLOAT2(
		760.0f + static_cast<float>(Display_position_of_number_of_remaining_enemies)
			, 5.0f)
		, Colors::Orange, 0.0f, 0.7f);


	pObject.GetTexture2D()->Draw(TEXTURE2D::human, { 0,0,225,225 }, { 
		710 + Display_position_of_number_of_remaining_enemies
		,-5
		,755+ Display_position_of_number_of_remaining_enemies
		,40 },Colors::Orange);


	//HPの表示

	int Display_position_of_HPUI = 0;
	pObject.GetTexture2D()->Draw(TEXTURE2D::HEART, { 0,0,338,315 }, { 810 + Display_position_of_HPUI,5,845 + Display_position_of_HPUI,40 });

	pObject.GetText()->TextDraw(L"x", XMFLOAT2(
		850.0f + static_cast<float>(Display_position_of_HPUI)
		, 0.0f), Colors::Aqua, 0.0f, 0.7f);

	pObject.GetText()->DrawInt(mpPlayer->GetPlayerLife(), XMFLOAT2(
		870.0f+ static_cast<float>( Display_position_of_HPUI), 5.0f), Colors::Aqua, 0.0f, 0.7f);

	if (mSettingFlag == true)
	{
		mpPlaySetting->Draw();
	}
}

void GameUI::DrawNumbers(const int& number, const int& x, const int& y)
{
	DrawManager& pObject = DrawManager::GetInstance();
	int CountNum = number;
	
	for (int i = 0; i < 4; i++)
	{
		int num = 0;

		num = CountNum % 10;

		//x1,y1,x2,y2
		RECT rect1 = { };

		//x1,y1,x2,y2
		rect1 = { x - (i * 35) - 25,y + 30 ,x + 25 - (i * 35) - 20 , y + 80 };

		//切り取り座標的な
		RECT rect2 = { num * NUM_SIZE_X,0,num * NUM_SIZE_X + NUM_SIZE_X ,NUM_SIZE_Y };

		//***********************************************************

		//ここに描画
		pObject.GetTexture2D()->Draw(TEXTURE2D::NUM, rect2, rect1);

		//***********************************************************

		CountNum /= 10;
	}
}

Button* GameUI::Summon_Unit_Button(const UNIT_TYPE& type)
{
	return mpSummonUnitUI->Summon_Unit_Button(type);
}

const bool GameUI::BackSelectScene()
{
	return mBackSelectFlag;
}