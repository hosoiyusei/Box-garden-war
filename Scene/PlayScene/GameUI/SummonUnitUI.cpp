#include"pch.h"
#include"SummonUnitUI.h"

#include"../Player/Player.h"

#include"../Tutorial/Tutorial.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::string SWORD("剣");
const std::string BOW("弓");
const std::string GUN("銃");
const std::string CANNON("大砲");
const std::string KING("王");

//Spawnさせるときの金
const int SWORDFIGHTER_COST(-10);
const int ARCHER_COST(-20);
const int GUNNER_COST(-30);
const int CANNON_COST(-40);
const int SHOGUN_COST(-50);

//コンストラクタ
SummonUnitUI::SummonUnitUI()
	:mType(UNIT_TYPE::NONE)
	, mWindowPosX(1600)
	, mpPlayer(nullptr)
	, mOnButtonFlag(false)
{

}

//デストラクタ
SummonUnitUI::~SummonUnitUI()
{

}

void SummonUnitUI::Initialize(Player* pPlayer, Tutorial* pTutorial)
{
	mpPlayer = pPlayer;
	mpTutorial = pTutorial;

	mpButtons[UNIT_TYPE::SWORDFIGHTER] = std::make_unique<Button>();
	mpButtons[UNIT_TYPE::ARCHER      ] = std::make_unique<Button>();
	mpButtons[UNIT_TYPE::GUNNER      ] = std::make_unique<Button>();
	mpButtons[UNIT_TYPE::CANNON      ] = std::make_unique<Button>();
	mpButtons[UNIT_TYPE::SHOGUN      ] = std::make_unique<Button>();

	//描画座標の設定
	mpButtons[UNIT_TYPE::SWORDFIGHTER]->SetRECT(mWindowPosX, 100, mWindowPosX + 100, 200);
	mpButtons[UNIT_TYPE::ARCHER]->SetRECT(mWindowPosX, 200, mWindowPosX + 100, 300);
	mpButtons[UNIT_TYPE::GUNNER]->SetRECT(mWindowPosX, 300, mWindowPosX + 100, 400);
	mpButtons[UNIT_TYPE::CANNON]->SetRECT(mWindowPosX, 400, mWindowPosX + 100, 500);
	mpButtons[UNIT_TYPE::SHOGUN]->SetRECT(mWindowPosX,  500, mWindowPosX + 100, 600);
}

void SummonUnitUI::Update()
{
	mpButtons[UNIT_TYPE::SWORDFIGHTER]->SetRECT(mWindowPosX, 100, mWindowPosX + 100, 200);
	mpButtons[UNIT_TYPE::ARCHER]->SetRECT(mWindowPosX, 200, mWindowPosX + 100, 300);
	mpButtons[UNIT_TYPE::GUNNER]->SetRECT(mWindowPosX, 300, mWindowPosX + 100, 400);
	mpButtons[UNIT_TYPE::CANNON]->SetRECT(mWindowPosX, 400, mWindowPosX + 100, 500);
	mpButtons[UNIT_TYPE::SHOGUN]->SetRECT(mWindowPosX,  500, mWindowPosX + 100, 600);

	Button_Change_Color();
}

//描画
void SummonUnitUI::Draw(const bool& Flag)
{
	DrawManager& pObject = DrawManager::GetInstance();

	//画像の切り取り
	RECT rect1;
	RECT rect2;

	//Unitを呼び出すときのUI
	if (Flag == false)
	{
		mWindowPosX += (1700 - mWindowPosX) / 2;
	}
	else if (Flag == true)
	{
		mWindowPosX -= (mWindowPosX - 1400) / 2;
		
		//ここから説明文
		XMFLOAT2 Pos;
		Pos = XMFLOAT2(1320, 650);

		pObject.GetText()->TextDraw(L"兵種", Pos, Colors::White, 0.0f, 0.7f);
		UnitName(Pos);
		pObject.GetText()->TextDraw(L"攻撃力", Pos + XMFLOAT2(0, 30), Colors::White, 0.0f, 0.7f);
		UnitAttack(Pos + XMFLOAT2(0, 30));
		pObject.GetText()->TextDraw(L"能力", Pos + XMFLOAT2(0, 60), Colors::White, 0.0f, 0.7f);
		Unitattribute(Pos + XMFLOAT2(0, 60));
		pObject.GetText()->TextDraw(L"必要金額", Pos + XMFLOAT2(0, 90), Colors::White, 0.0f, 0.7f);
		Money(Pos + XMFLOAT2(0, 90));
	}

	//ウィンドウの画像の描画
	Change_Color(UNIT_TYPE::SWORDFIGHTER, 10, 0,0);
	Change_Color(UNIT_TYPE::ARCHER, 20, -120, 480);
	Change_Color(UNIT_TYPE::GUNNER, 30, -240, 360);
	Change_Color(UNIT_TYPE::CANNON, 40, -360, 240);
	Change_Color(UNIT_TYPE::SHOGUN, 50, -480, 120);

	mOnButtonFlag = false;

	//Unitのアイコン画像の切り取り範囲
	rect1 = { 256,256 };

	//剣士のアイコン
	rect2 = { mWindowPosX + 100,200,mWindowPosX + 200,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::SWORD, rect1, rect2, Colors::White, 3.14f);

	//弓兵のアイコン
	rect2 = { mWindowPosX + 100,300,mWindowPosX + 200,400 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::BOW_AND_ARROW, rect1, rect2, Colors::White, 3.14f);

	//ガンナーのアイコン
	rect2 = { mWindowPosX + 100,400,mWindowPosX + 200,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GUN, rect1, rect2, Colors::White, 3.14f);

	//大砲のアイコン
	rect2 = { mWindowPosX + 100,500,mWindowPosX + 200,600 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::CANNON, rect1, rect2, Colors::White, 3.14f);

	//将軍のアイコン
	rect2 = { mWindowPosX + 100,600,mWindowPosX + 200,700 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::SHOGUN, rect1, rect2, Colors::White, 3.14f);
}

/**********************************************************************************/

//Unitの名前
void SummonUnitUI::UnitName(const XMFLOAT2& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	pObject.GetText()->TextDraw(L":", pos + XMFLOAT2(140,0), Colors::White, 0.0f, 0.7f);

	XMFLOAT2 Pos(150, 0);

	const float x = static_cast<float>(mWindowPosX - 50);

	switch (mType)
	{
		case UNIT_TYPE::SWORDFIGHTER:
		{
			pObject.GetText()->TextDraw(L"剣士", pos + Pos, Colors::White, 0.0f, 0.7f);
			pObject.GetText()->TextDraw(L"→", XMFLOAT2(x, 130));
			break;
		}
		case UNIT_TYPE::ARCHER:
		{
			pObject.GetText()->TextDraw(L"弓兵", pos + Pos, Colors::White, 0.0f, 0.7f);
			pObject.GetText()->TextDraw(L"→", XMFLOAT2(x, 230));
			break;
		}
		case UNIT_TYPE::GUNNER:
		{
			pObject.GetText()->TextDraw(L"銃士", pos + Pos, Colors::White, 0.0f, 0.7f);
			pObject.GetText()->TextDraw(L"→", XMFLOAT2(x, 330));
			break;
		}
		case UNIT_TYPE::CANNON:
		{
			pObject.GetText()->TextDraw(L"大砲", pos + Pos, Colors::White, 0.0f, 0.7f);
			pObject.GetText()->TextDraw(L"→", XMFLOAT2(x, 430));
			break;
		}
		case UNIT_TYPE::SHOGUN:
		{
			pObject.GetText()->TextDraw(L"将軍", pos + Pos, Colors::White, 0.0f, 0.7f);
			pObject.GetText()->TextDraw(L"→", XMFLOAT2(x, 530));
			break;
		}
		default:break;
	}
}

//Unitの攻撃力
void SummonUnitUI::UnitAttack(const XMFLOAT2& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	XMFLOAT2 Pos(150, 0);
	pObject.GetText()->TextDraw(L":", pos + XMFLOAT2(140, 0), Colors::White, 0.0f, 0.7f);

	switch (mType)
	{
		case UNIT_TYPE::SWORDFIGHTER:
		{
			pObject.GetText()->DrawInt(2, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::ARCHER:
		{
			pObject.GetText()->DrawInt(1, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::GUNNER:
		{
			pObject.GetText()->DrawInt(2, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::CANNON:
		{
			pObject.GetText()->DrawInt(8, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::SHOGUN:
		{
			pObject.GetText()->DrawInt(0, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		default:break;
	}
}

//Unitの属性
void SummonUnitUI::Unitattribute(const XMFLOAT2& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1 = { 0,0,83,81 };
	RECT rect2 = { static_cast<int>(pos.x) + 150, static_cast<int>(pos.y), static_cast<int>(pos.x) + 190, static_cast<int>(pos.y) + 40 };
	RECT rect3 = { static_cast<int>(pos.x) + 190, static_cast<int>(pos.y), static_cast<int>(pos.x) + 230, static_cast<int>(pos.y) + 40 };

	pObject.GetText()->TextDraw(L":", pos + XMFLOAT2(140, 0), Colors::White, 0.0f, 0.7f);

	switch (mType)
	{
		case UNIT_TYPE::SWORDFIGHTER:
		{
			pObject.GetTexture2D()->Draw(TEXTURE2D::TI, rect1, rect2);
			break;
		}
		case UNIT_TYPE::ARCHER:
		{
			pObject.GetTexture2D()->Draw(TEXTURE2D::TI, rect1, rect2);
			pObject.GetTexture2D()->Draw(TEXTURE2D::KUU, rect1, rect3);
			break;
		}
		case UNIT_TYPE::GUNNER:
		{
			pObject.GetTexture2D()->Draw(TEXTURE2D::TI, rect1, rect2);
			pObject.GetTexture2D()->Draw(TEXTURE2D::KUU, rect1, rect3);
			break;
		}
		case UNIT_TYPE::CANNON:
		{
			pObject.GetTexture2D()->Draw(TEXTURE2D::TI, rect1, rect2);
			break;
		}
		case UNIT_TYPE::SHOGUN:
		{
			break;
		}
		default:break;
	}
}

//必要な金
void SummonUnitUI::Money(const XMFLOAT2& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	XMFLOAT2 Pos(150, 0);

	pObject.GetText()->TextDraw(L":", pos + XMFLOAT2(140, 0), Colors::White, 0.0f, 0.7f);

	switch (mType)
	{
		case UNIT_TYPE::SWORDFIGHTER:
		{
			pObject.GetText()->DrawInt(10, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::ARCHER:
		{
			pObject.GetText()->DrawInt(20, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::GUNNER:
		{
			pObject.GetText()->DrawInt(30, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::CANNON:
		{
			pObject.GetText()->DrawInt(40, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::SHOGUN:
		{
			pObject.GetText()->DrawInt(50, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		default:break;
	}
}

void SummonUnitUI::Change_Color(const UNIT_TYPE& type, const int& money, const int& mouse_scroll, const int& mouse_scroll2)
{
	InputManager& inputManager = InputManager::GetInstance();

	//画像の切り取りサイズ
	RECT rect{ 500, 510 };

	if (mpTutorial->GetmTutorial_event_number() == 6)
	{
		if (mouse_scroll == inputManager.GetMouseState().scrollWheelValue ||
			mouse_scroll2 == inputManager.GetMouseState().scrollWheelValue)
		{
			mpButtons[type]->DrawButton(rect, TEXTURE2D::WINDOW, L"", XMFLOAT2(), Colors::White, 1.0f, Colors::Aqua, Colors::Aqua);
		}
		else
			mpButtons[type]->DrawButton(rect, TEXTURE2D::WINDOW, L"", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::Gray);
		return;
	}

	if (mpPlayer->GetMoney() >= money)
	{
		if (mouse_scroll == inputManager.GetMouseState().scrollWheelValue && mOnButtonFlag == false||
			mouse_scroll2 == inputManager.GetMouseState().scrollWheelValue && mOnButtonFlag == false)
		{
			mpButtons[type]->DrawButton(rect, TEXTURE2D::WINDOW, L"", XMFLOAT2(), Colors::White, 1.0f, Colors::Aqua, Colors::Aqua);
			return;
		}

		mpButtons[type]->DrawButton(rect, TEXTURE2D::WINDOW, L"", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::Aqua);
	}
	else
	{
		mpButtons[type]->DrawButton(rect, TEXTURE2D::WINDOW, L"", XMFLOAT2(), Colors::White, 1.0f
			, Color(0.2f,0.2f,0.2f), Color(0.2f, 0.2f, 0.2f));
	}
}

void SummonUnitUI::Button_Change_Color()
{
	InputManager& inputManager = InputManager::GetInstance();

	if (mpButtons[UNIT_TYPE::SWORDFIGHTER]->When_the_mouse_cursor_enters_the_range() == true&& mpTutorial->GetmTutorial_event_number() != 6)
	{
		mType = UNIT_TYPE::SWORDFIGHTER; mOnButtonFlag = true;
	}
	else if (mpButtons[UNIT_TYPE::ARCHER]->When_the_mouse_cursor_enters_the_range() == true && mpTutorial->GetmTutorial_event_number() != 6)
	{
		mType = UNIT_TYPE::ARCHER; mOnButtonFlag = true;
	}
	else if (mpButtons[UNIT_TYPE::GUNNER]->When_the_mouse_cursor_enters_the_range() == true && mpTutorial->GetmTutorial_event_number() != 6)
	{
		mType = UNIT_TYPE::GUNNER; mOnButtonFlag = true;
	}
	else if (mpButtons[UNIT_TYPE::CANNON]->When_the_mouse_cursor_enters_the_range() == true && mpTutorial->GetmTutorial_event_number() != 6)
	{
		mType = UNIT_TYPE::CANNON; mOnButtonFlag = true;
	}
	else if (mpButtons[UNIT_TYPE::SHOGUN]->When_the_mouse_cursor_enters_the_range() == true && mpTutorial->GetmTutorial_event_number() != 6)
	{
		mType = UNIT_TYPE::SHOGUN; mOnButtonFlag = true;
	}
	else if (inputManager.GetMouseState().scrollWheelValue == 0)
	{
		mType = UNIT_TYPE::SWORDFIGHTER;
	}
	else if (inputManager.GetMouseState().scrollWheelValue == -120||
		inputManager.GetMouseState().scrollWheelValue == 480)
	{
		mType = UNIT_TYPE::ARCHER;
	}
	else if (inputManager.GetMouseState().scrollWheelValue == -240 ||
		inputManager.GetMouseState().scrollWheelValue == 360)
	{
		mType = UNIT_TYPE::GUNNER;
	}
	else if (inputManager.GetMouseState().scrollWheelValue == -360 ||
		inputManager.GetMouseState().scrollWheelValue == 240)
	{
		mType = UNIT_TYPE::CANNON;
	}
	else if (inputManager.GetMouseState().scrollWheelValue == -480 ||
		inputManager.GetMouseState().scrollWheelValue == 120)
	{
		mType = UNIT_TYPE::SHOGUN;
	}
}