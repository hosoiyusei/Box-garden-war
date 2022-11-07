#include"pch.h"
#include"ArrowUI.h"
#include"../DoubleSpeed/DoubleSpeed.h"
#include"../../TitleScene/Button/Button.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::string REPRODUCTION("�Đ�");
const std::string FAST_FORWARD("������");

ArrowUI::ArrowUI()
{

}

void ArrowUI::Initialize()
{
	mpButtons[REPRODUCTION] = std::make_unique<Button>();
	mpButtons[FAST_FORWARD] = std::make_unique<Button>();

	//�`����W�̐ݒ�
	mpButtons[REPRODUCTION]->SetRECT(1470, 820, 1530, 880);
	mpButtons[FAST_FORWARD]->SetRECT(1370, 820, 1430, 880);
}

void ArrowUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	RECT rect1;
	RECT rect2;
	
	//�E�B���h�E�̉摜�؂���͈�
	rect1 = { 500,508 };
	//�E����UI�̃E�B���h�E�͈�
	rect2 = { 1300,0,1600,900 };

	//�������UI�E�B���h�E�͈̔�
	mpButtons[FAST_FORWARD]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::White);

	//�ꎞ��~�E�Đ���UI�E�B���h�E�͈̔�
	mpButtons[REPRODUCTION]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(), Colors::White, 1.0f, Colors::Gray, Colors::White);

	rect1 = { 150,150 };

	if (mpDoubleSpeed.GetSpeed() == 1.0f)
	{
		//�`��͈�
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::REPRODUCTION, rect1, rect2);
	}
	else if (mpDoubleSpeed.GetSpeed() == 2.0f)
	{
		//�`��͈�
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
	}
	else
	{
		//�`��͈�
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::MAXFASTFORWARD, rect1, rect2);
	}


	//�`��͈�
	rect2 = { 1470,820,1530,880 };

	//�Đ��E��~
	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::PAUSE, RECT{ 515,515 }, rect2);
	}
	else
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::EXECUTION, RECT{256, 256, 0, 0 }, rect2);
	}
}