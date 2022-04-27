#include"pch.h"
#include"StageInformation.h"

#include"../../Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

StageInformation::StageInformation()
{

}

StageInformation::~StageInformation()
{

}

void StageInformation::Draw(Player* pPlayer)
{
	DrawManager& pObject = DrawManager::GetInstance();

	STAGE_DATA stagedata = pPlayer->GetStageData(
		static_cast<int>(pPlayer->GetPlayerPos().x)
		, static_cast<int>(pPlayer->GetPlayerPos().z));

	int levelnum = GetLevel(stagedata.unit_Level);

	if (stagedata.unit_Level != UNIT_LEVEL::NONE)
	{
		pObject.GetText()->TextDraw(L"ƒŒƒxƒ‹ :", XMFLOAT2(1320, 680), Colors::White, 0.0f, 0.7f);
		pObject.GetText()->DrawInt(levelnum, XMFLOAT2(1450,  680), Colors::White, 0.0f, 0.7f);
	}

	if (stagedata.tileData == TILE_DATA::Swordfighter ||
		stagedata.tileData == TILE_DATA::Archer ||
		stagedata.tileData == TILE_DATA::Gunner ||
		stagedata.tileData == TILE_DATA::Cannon ||
		stagedata.tileData == TILE_DATA::Wizard)
	{
		pObject.GetText()->TextDraw(L"ƒ^ƒCƒv :", XMFLOAT2(1320, 650), Colors::White, 0.0f, 0.7f);
		UnitType(stagedata.tileData);
	}
}

//ƒŒƒxƒ‹‚ðint‚Å•Ô‚·
const int& StageInformation::GetLevel(const UNIT_LEVEL& level)
{
	switch (level)
	{
		case UNIT_LEVEL::LEVEL_1: {return 1; break; }
		case UNIT_LEVEL::LEVEL_2: {return 2; break; }
		case UNIT_LEVEL::LEVEL_3: {return 3; break; }
		case UNIT_LEVEL::LEVEL_4: {return 4; break; }
		case UNIT_LEVEL::LEVEL_5: {return 5; break; }
		default:break;
	}
}

void StageInformation::UnitType(const TILE_DATA data)
{
	DrawManager& pObject = DrawManager::GetInstance();

	switch (data)
	{
		case TILE_DATA::Swordfighter:	{pObject.GetText()->TextDraw(L"Œ•Žm", XMFLOAT2(1450, 650), Colors::White, 0.0f, 0.7f); break; }
		case TILE_DATA::Archer:			{pObject.GetText()->TextDraw(L"‹|Žm",       XMFLOAT2(1450, 650), Colors::White, 0.0f, 0.7f); break; }
		case TILE_DATA::Gunner:			{pObject.GetText()->TextDraw(L"eŽm",       XMFLOAT2(1450, 650), Colors::White, 0.0f, 0.7f); break; }
		case TILE_DATA::Cannon:			{pObject.GetText()->TextDraw(L"‘å–C",       XMFLOAT2(1450, 650), Colors::White, 0.0f, 0.7f); break; }
		case TILE_DATA::Shogun:			{pObject.GetText()->TextDraw(L"‰¤",       XMFLOAT2(1450, 650), Colors::White, 0.0f, 0.7f); break; }
		default:break;
	}
}