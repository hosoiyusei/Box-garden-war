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
	
	//�E�B���h�E�̉摜�؂���͈�
	rect1 = { 500,508 };
	//�E����UI�̃E�B���h�E�͈�
	rect2 = { 1300,0,1600,900 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);//2

	//�������UI�E�B���h�E�͈̔�
	rect2 = { 1370,820,1430,880 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);//3

	//�ꎞ��~�E�Đ���UI�E�B���h�E�͈̔�
	rect2 = { 1470,820,1530,880 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);//4

	//�}�E�X���͈͂ɓ������Ƃ��ɃE�B���h�E�̐F��ς���
	if (1370 <= inputManager.GetMouseState().x &&//�k��
		1450 >= inputManager.GetMouseState().x &&
		810 <= inputManager.GetMouseState().y &&
		890 >= inputManager.GetMouseState().y)
	{
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	else if (1470 <= inputManager.GetMouseState().x &&//�k��
		1550 >= inputManager.GetMouseState().x &&
		810 <= inputManager.GetMouseState().y &&
		890 >= inputManager.GetMouseState().y)
	{
		rect2 = { 1470,820,1530,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}

	if (mpDoubleSpeed.GetSpeed() == 1.0f)
	{
		//�Đ��E������̉摜�̐؂���͈�
		rect1 = { 280,280 };
		//�`��͈�
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::REPRODUCTION, rect1, rect2);
	}
	else if (mpDoubleSpeed.GetSpeed() == 2.0f)
	{
		//������̉摜�؂���͈�
		rect1 = { 300,300 };
		//�`��͈�
		rect2 = { 1370,820,1430,880 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
	}
	else
	{
		//������̉摜�؂���͈�
		rect1 = { 300,300 };
		//�`��͈�
		rect2 = { 1365,830,1405,870 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
		//��`��
		rect2 = { 1395,830,1435,870 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::FASTFORWRD, rect1, rect2);
	}

	//�ꎞ��~�ƍĐ��̉摜�̐؂���͈�
	rect1 = { 515,515 };
	//�`��͈�
	rect2 = { 1470,820,1530,880 };

	//�Đ��E��~
	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::PAUSE, rect1, rect2);
	}
	else
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::EXECUTION, rect1, rect2);
	}
}