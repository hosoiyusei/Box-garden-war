#include"pch.h"
#include"ArrowUI.h"
#include"../DoubleSpeed/DoubleSpeed.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ArrowUI::ArrowUI()
{

}

ArrowUI::~ArrowUI()
{

}

void ArrowUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	RECT rect1;
	RECT rect2;
	
	//ウィンドウの画像切り取り範囲
	rect1 = { 500,508 };
	//右側のUIのウィンドウ範囲
	rect2 = { 1300,0,1600,900 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);//2

	//早送りのUIウィンドウの範囲
	rect2 = { 1370,820,1430,880 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);//3

	//一時停止・再生のUIウィンドウの範囲
	rect2 = { 1470,820,1530,880 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);//4

	//マウスが範囲に入ったときにウィンドウの色を変える
	if (1370 <= inputManager.GetMouseState().x &&//縮小
		1450 >= inputManager.GetMouseState().x &&
		810 <= inputManager.GetMouseState().y &&
		890 >= inputManager.GetMouseState().y)
	{
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	else if (1470 <= inputManager.GetMouseState().x &&//縮小
		1550 >= inputManager.GetMouseState().x &&
		810 <= inputManager.GetMouseState().y &&
		890 >= inputManager.GetMouseState().y)
	{
		rect2 = { 1470,820,1530,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}

	if (mpDoubleSpeed.GetSpeed() == 1.0f)
	{
		//再生・早送りの画像の切り取り範囲
		rect1 = { 280,280 };
		//描画範囲
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::REPRODUCTION, rect1, rect2);
	}
	else if (mpDoubleSpeed.GetSpeed() == 2.0f)
	{
		//早送りの画像切り取り範囲
		rect1 = { 300,300 };
		//描画範囲
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
	}
	else
	{
		//早送りの画像切り取り範囲
		rect1 = { 300,300 };
		//描画範囲
		rect2 = { 1365,830,1405,870 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
		//二つ描画
		rect2 = { 1395,830,1435,870 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
	}

	//一時停止と再生の画像の切り取り範囲
	rect1 = { 515,515 };
	//描画範囲
	rect2 = { 1470,820,1530,880 };

	//再生・停止
	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::PAUSE, rect1, rect2);
	}
	else
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::EXECUTION, rect1, rect2);
	}
}