#include"pch.h"
#include"SelectUI.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
SelectUI::SelectUI()
{

}

//デストラクタ
SelectUI::~SelectUI()
{

}

//描画
void SelectUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	RECT rect1;
	RECT rect2;

	//壁の描画範囲
	rect2 = { 0,0,1600,900 };
	//画像切り取り範囲
	rect1 = { 0,0,700,700 };
	//背景(壁)の描画
	pObject.GetTexture2D()->Draw(TEXTURE2D::WALL, rect1, rect2);

	//ウィンドウの切り取り範囲
	rect1 = { 500,510 };

	//ステージ１のウィンドウの描画範囲
	rect2 = { 100,100,400,200 };
	//ウィンドウの描画
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//ステージ１のウィンドウの描画範囲
	rect2 = { 100,250,400,350 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//ステージ１のウィンドウの描画範囲
	rect2 = { 100,400,400,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//ステージ１のウィンドウの描画範囲
	rect2 = { 100,550,400,650 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//マウスカーソルが範囲に入ったら
	//ステージ１
	if (mouseX > 100 && mouseX < 400 && mouseY>100 && mouseY < 200)
	{
		rect2 = { 100,100,400,200 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	//ステージ２
	else if (mouseX > 100 && mouseX < 400 && mouseY>250 && mouseY < 350)
	{
		rect2 = { 100,250,400,350 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	//ステージ３
	else if (mouseX > 100 && mouseX < 400 && mouseY>400 && mouseY < 500)
	{
		rect2 = { 100,400,400,500 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	//ステージ４
	else if (mouseX > 100 && mouseX < 400 && mouseY>550 && mouseY < 650)
	{
		rect2 = { 100,550,400,650 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}

	//ステージの選択し描画
	pObject.GetText()->TextDraw(L"ステージ 1", XMFLOAT2(110, 100+25), Colors::White, 0.0f, 1.5f);
	pObject.GetText()->TextDraw(L"ステージ 2", XMFLOAT2(110, 250+25), Colors::White, 0.0f, 1.5f);
	pObject.GetText()->TextDraw(L"ステージ 3", XMFLOAT2(110, 400+25), Colors::White, 0.0f, 1.5f);
	pObject.GetText()->TextDraw(L"ステージ 4", XMFLOAT2(110, 550+25), Colors::White, 0.0f, 1.5f);
}