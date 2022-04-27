#include"pch.h"
#include"Reinforcement.h"

#include"../Player/Player.h"

#include"../Player/StageTileData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//レベル上げるときの金
const int LEVEL_UP_COST_2(10);
const int LEVEL_UP_COST_3(20);
const int LEVEL_UP_COST_4(30);
const int LEVEL_UP_COST_5(40);

//Unitの種類毎のレベル上げるときの金
const int LEVEL_UP_COST_SWORDFIGHTER(10);
const int LEVEL_UP_COST_ARCHER(20);
const int LEVEL_UP_COST_GUNNER(30);
const int LEVEL_UP_COST_CANNON(40);
const int LEVEL_UP_COST_SHOGUN(50);

Reinforcement::Reinforcement()
	:mLevel(UNIT_LEVEL::NONE)
	, mWindowPosX(1600)
{

}

Reinforcement::~Reinforcement()
{

}

void Reinforcement::Draw(Player* mpPlayer)
{
	//強化するときのUI
	if (mpPlayer->GetReinforcementFlag() == false)
	{
		//ウィンドウの座標を移動
		mWindowPosX += (1600 - mWindowPosX) / 2;
	}
	else if (mpPlayer->GetReinforcementFlag() == true)
	{
		mWindowPosX -= (mWindowPosX - 1400) / 2;

		DrawManager& pObject = DrawManager::GetInstance();

		//ステージの情報
		STAGE_DATA stagedata = mpPlayer->GetStageData(static_cast<int>(mpPlayer->GetPlayerPos().x), static_cast<int>(mpPlayer->GetPlayerPos().z));

		RECT rect1;
		RECT rect2;

		rect1 = { 500,520 };
		rect2 = { mWindowPosX,100,mWindowPosX + 100,200 };
		//パワーアップのウィンドウの描画
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

		rect1 = { 750,730,0,0 };
		rect2 = { mWindowPosX+100,200,mWindowPosX+200,300 };
		//パワーアップのUIの描画
		pObject.GetTexture2D()->Draw(TEXTURE2D::POWERUP, rect1, rect2, Colors::White, 3.14f);

		pObject.GetText()->TextDraw(L"必要金額：", XMFLOAT2(1360, 200), Colors::White, 0.0f, 0.7f);
		pObject.GetText()->DrawInt(RequestedAmount(stagedata), XMFLOAT2(1510, 200), Colors::White, 0.0f, 0.7f);
	}
}

int Reinforcement::RequestedAmount(STAGE_DATA data)
{
	switch (data.tileData)
	{
		case TILE_DATA::Swordfighter:	{return LevelRequestedAmount(data)+ LEVEL_UP_COST_SWORDFIGHTER;break; }
		case TILE_DATA::Archer:			{return LevelRequestedAmount(data)+ LEVEL_UP_COST_ARCHER;break; }
		case TILE_DATA::Gunner:			{return LevelRequestedAmount(data)+ LEVEL_UP_COST_GUNNER;break; }
		case TILE_DATA::Cannon:			{return LevelRequestedAmount(data)+ LEVEL_UP_COST_CANNON;break; }
		case TILE_DATA::Shogun:			{return LevelRequestedAmount(data)+ LEVEL_UP_COST_SHOGUN;break; }
		default:break;
	}

	return 0;
}

int Reinforcement::LevelRequestedAmount(STAGE_DATA data)
{
	switch (data.unit_Level)
	{
		case UNIT_LEVEL::LEVEL_1: {return LEVEL_UP_COST_2; break; }
		case UNIT_LEVEL::LEVEL_2: {return LEVEL_UP_COST_3; break; }
		case UNIT_LEVEL::LEVEL_3: {return LEVEL_UP_COST_4; break; }
		case UNIT_LEVEL::LEVEL_4: {return LEVEL_UP_COST_5; break; }
		default:break;
	}

	return 0;
}