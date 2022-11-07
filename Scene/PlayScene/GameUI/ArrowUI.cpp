#include"pch.h"
#include"ArrowUI.h"
#include"../DoubleSpeed/DoubleSpeed.h"
#include"../../TitleScene/Button/Button.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::string REPRODUCTION("再生");
const std::string FAST_FORWARD("早送り");

ArrowUI::ArrowUI()
{

}

void ArrowUI::Initialize()
{
	mpButtons[REPRODUCTION] = std::make_unique<Button>();
	mpButtons[FAST_FORWARD] = std::make_unique<Button>();

	//描画座標の設定
	mpButtons[REPRODUCTION]->SetRECT(1470, 820, 1530, 880);
	mpButtons[FAST_FORWARD]->SetRECT(1370, 820, 1430, 880);
}

void ArrowUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	RECT rect1;
	RECT rect2;
	
	//ウィンドウの画像切り取り範囲
	rect1 = { 500,508 };
	//右側のUIのウィンドウ範囲
	rect2 = { 1300,0,1600,900 };

	//早送りのUIウィンドウの範囲
	mpButtons[FAST_FORWARD]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::White);

	//一時停止・再生のUIウィンドウの範囲
	mpButtons[REPRODUCTION]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::White);

	rect1 = { 150,150 };

	if (mpDoubleSpeed.GetSpeed() == 1.0f)
	{
		//描画範囲
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::REPRODUCTION, rect1, rect2);
	}
	else if (mpDoubleSpeed.GetSpeed() == 2.0f)
	{
		//描画範囲
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
	}
	else
	{
		//描画範囲
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::MAXFASTFORWARD, rect1, rect2);
	}


	//描画範囲
	rect2 = { 1470,820,1530,880 };

	//再生・停止
	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::PAUSE, RECT{ 515,515 }, rect2);
	}
	else
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::EXECUTION, RECT{256, 256, 0, 0 }, rect2);
	}
}