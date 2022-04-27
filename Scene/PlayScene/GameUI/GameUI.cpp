#include"pch.h"
#include"GameUI.h"

#include"../Player/Player.h"
#include"ArrowUI.h"
#include"SummonUnitUI.h"
#include"Reinforcement.h"
#include"StageInformation/StageInformation.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const int NUM_SIZE_X = 18 * 2;
const int NUM_SIZE_Y = 18 * 4;
const int TIMER_POS_Y = 250;

GameUI::GameUI()
	: mpPlayer(nullptr)
{

}

GameUI::~GameUI()
{

}

void GameUI::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;

	mpArrowUI = std::make_unique<ArrowUI>();

	mpSummonUnitUI = std::make_unique<SummonUnitUI>();

	mpReinforcement = std::make_unique<Reinforcement>();

	mpStageInformation = std::make_unique<StageInformation>();
}

void GameUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	mpArrowUI->Draw();

	//Unit‚ðŒÄ‚Ño‚·‚Æ‚«‚ÌUI
	mpSummonUnitUI->Draw(mpPlayer->GetUnitSelectFlag(), mpPlayer->GetInputMousePosX(), mpPlayer->GetInputMousePosY());

	//‹­‰»‚·‚é‚Æ‚«‚ÌUI
	mpReinforcement->Draw(mpPlayer);

	mpStageInformation->Draw(mpPlayer);

	//ŠŽ‹àŠz‚Ì•`‰æ
	RECT rect1, rect2;
	rect1 = { 0,0,324,340 };
	rect2 = { 1330,30,1380,80 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MONEY, rect1, rect2);
	//pObject.GetText()->TextDraw(L"ŠŽ‹à :", XMFLOAT2(1330, 30),Colors::Gold);
	//pObject.GetText()->DrawInt(mpPlayer->GetMoney(), XMFLOAT2(1440, 30));
	DrawNumbers(mpPlayer->GetMoney(), 1550, 0);
}

void GameUI::DrawNumbers(const int& number, const int& x, const int& y)
{
	DrawManager& pObject = DrawManager::GetInstance();
	int CountNum = number;
	
	for (int i = 0; i < 5; i++)
	{
		int num = 0;

		num = CountNum % 10;

		//x1,y1,x2,y2
		RECT rect1 = { };

		//x1,y1,x2,y2
		rect1 = { x - (i * 35) - 25,y + 30 ,x + 25 - (i * 35) - 20 , y + 80 };

		//Ø‚èŽæ‚èÀ•W“I‚È
		RECT rect2 = { num * NUM_SIZE_X,0,num * NUM_SIZE_X + NUM_SIZE_X ,NUM_SIZE_Y };

		//***********************************************************

		//‚±‚±‚É•`‰æ
		pObject.GetTexture2D()->Draw(TEXTURE2D::NUM, rect2, rect1);

		//***********************************************************

		CountNum /= 10;
	}
}