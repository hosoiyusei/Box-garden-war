#include"pch.h"
#include"SelectUI.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
SelectUI::SelectUI()
{

}

//�f�X�g���N�^
SelectUI::~SelectUI()
{

}

//�`��
void SelectUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	RECT rect1;
	RECT rect2;

	//�ǂ̕`��͈�
	rect2 = { 0,0,1600,900 };
	//�摜�؂���͈�
	rect1 = { 0,0,700,700 };
	//�w�i(��)�̕`��
	pObject.GetTexture2D()->Draw(TEXTURE2D::WALL, rect1, rect2);

	//�E�B���h�E�̐؂���͈�
	rect1 = { 500,510 };

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	rect2 = { 100,100,400,200 };
	//�E�B���h�E�̕`��
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	rect2 = { 100,250,400,350 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	rect2 = { 100,400,400,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	rect2 = { 100,550,400,650 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�}�E�X�J�[�\�����͈͂ɓ�������
	//�X�e�[�W�P
	if (mouseX > 100 && mouseX < 400 && mouseY>100 && mouseY < 200)
	{
		rect2 = { 100,100,400,200 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	//�X�e�[�W�Q
	else if (mouseX > 100 && mouseX < 400 && mouseY>250 && mouseY < 350)
	{
		rect2 = { 100,250,400,350 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	//�X�e�[�W�R
	else if (mouseX > 100 && mouseX < 400 && mouseY>400 && mouseY < 500)
	{
		rect2 = { 100,400,400,500 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	//�X�e�[�W�S
	else if (mouseX > 100 && mouseX < 400 && mouseY>550 && mouseY < 650)
	{
		rect2 = { 100,550,400,650 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}

	//�X�e�[�W�̑I�����`��
	pObject.GetText()->TextDraw(L"�X�e�[�W 1", XMFLOAT2(110, 100+25), Colors::White, 0.0f, 1.5f);
	pObject.GetText()->TextDraw(L"�X�e�[�W 2", XMFLOAT2(110, 250+25), Colors::White, 0.0f, 1.5f);
	pObject.GetText()->TextDraw(L"�X�e�[�W 3", XMFLOAT2(110, 400+25), Colors::White, 0.0f, 1.5f);
	pObject.GetText()->TextDraw(L"�X�e�[�W 4", XMFLOAT2(110, 550+25), Colors::White, 0.0f, 1.5f);
}