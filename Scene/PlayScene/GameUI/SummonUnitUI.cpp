#include"pch.h"
#include"SummonUnitUI.h"

#include"../Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
SummonUnitUI::SummonUnitUI()
	:mType(UNIT_TYPE::NONE)
	, mWindowPosX(1600)
{

}

//�f�X�g���N�^
SummonUnitUI::~SummonUnitUI()
{

}

void SummonUnitUI::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//�`��
void SummonUnitUI::Draw(const bool& Flag, const int& X, const int& Y)
{
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();

	//�摜�̐؂���
	RECT rect1;
	RECT rect2;

	//�E�B���h�E�̉摜�̐؂���͈�
	rect1 = { 500, 520 };

	//Unit���Ăяo���Ƃ���UI
	if (Flag == false)
	{
		mWindowPosX += (1600 - mWindowPosX) / 2;
	}
	else if (Flag == true)
	{
		mWindowPosX -= (mWindowPosX - 1400) / 2;
		
		//�������������
		XMFLOAT2 Pos;
		Pos = XMFLOAT2(1320, 650);

		pObject.GetText()->TextDraw(L"���O", Pos, Colors::White, 0.0f, 0.7f);
		UnitName(Pos);
		pObject.GetText()->TextDraw(L"�U����", Pos + XMFLOAT2(0, 30), Colors::White, 0.0f, 0.7f);
		UnitAttack(Pos + XMFLOAT2(0, 30));
		pObject.GetText()->TextDraw(L"�\��", Pos + XMFLOAT2(0, 60), Colors::White, 0.0f, 0.7f);
		Unitattribute(Pos + XMFLOAT2(0, 60));
		pObject.GetText()->TextDraw(L"�K�v���z", Pos + XMFLOAT2(0, 90), Colors::White, 0.0f, 0.7f);
		Money(Pos + XMFLOAT2(0, 90));
	}

	//�E�B���h�E�̉摜�̕`��
	rect2 = { mWindowPosX,100,mWindowPosX + 100,200 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);

	rect2 = { mWindowPosX,210,mWindowPosX + 100,310 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);

	rect2 = { mWindowPosX,320,mWindowPosX + 100,420 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);

	rect2 = { mWindowPosX,430,mWindowPosX + 100,530 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);

	rect2 = { mWindowPosX,540,mWindowPosX + 100,640 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);

	//�}�E�X�J�[�\�����E�B���h�E�͈̔͂ɓ������Ƃ��F��ς���
	if (1400 <= inputManager.GetMouseState().x && 100 <= inputManager.GetMouseState().y && 1500 >= inputManager.GetMouseState().x && 200 >= inputManager.GetMouseState().y)
	{
		rect2 = { mWindowPosX,100,mWindowPosX + 100,200 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		mType = UNIT_TYPE::SWORDFIGHTER;
	}
	else if (1400 <= inputManager.GetMouseState().x && 210 <= inputManager.GetMouseState().y && 1500 >= inputManager.GetMouseState().x && 310 >= inputManager.GetMouseState().y)
	{
		rect2 = { mWindowPosX,210,mWindowPosX + 100,310 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		mType = UNIT_TYPE::ARCHER;
	}
	else if (1400 <= inputManager.GetMouseState().x && 320 <= inputManager.GetMouseState().y && 1500 >= inputManager.GetMouseState().x && 420 >= inputManager.GetMouseState().y)
	{
		rect2 = { mWindowPosX,320,mWindowPosX + 100,420 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		mType = UNIT_TYPE::GUNNER;
	}
	else if (1400 <= inputManager.GetMouseState().x && 430 <= inputManager.GetMouseState().y && 1500 >= inputManager.GetMouseState().x && 530 >= inputManager.GetMouseState().y)
	{
		rect2 = { mWindowPosX,430,mWindowPosX + 100,530 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		mType = UNIT_TYPE::CANNON;
	}
	else if (1400 <= inputManager.GetMouseState().x && 540 <= inputManager.GetMouseState().y && 1500 >= inputManager.GetMouseState().x && 640 >= inputManager.GetMouseState().y)
	{
		rect2 = { mWindowPosX,540,mWindowPosX + 100,640 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		mType = UNIT_TYPE::SHOGUN;
	}

	//Unit�̃A�C�R���摜�̐؂���͈�
	rect1 = { 256,256 };

	//���m�̃A�C�R��
	rect2 = { mWindowPosX + 100,200,mWindowPosX + 200,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::SWORD, rect1, rect2, Colors::White, 3.14f);

	//�|���̃A�C�R��
	rect2 = { mWindowPosX + 100,310,mWindowPosX + 200,410 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::BOW_AND_ARROW, rect1, rect2, Colors::White, 3.14f);

	//�K���i�[�̃A�C�R��
	rect2 = { mWindowPosX + 100,420,mWindowPosX + 200,520 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GUN, rect1, rect2, Colors::White, 3.14f);

	//��C�̃A�C�R��
	rect2 = { mWindowPosX + 100,530,mWindowPosX + 200,630 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::CANNON, rect1, rect2, Colors::White, 3.14f);

	//���R�̃A�C�R��
	rect2 = { mWindowPosX + 100,640,mWindowPosX + 200,740 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::SHOGUN, rect1, rect2, Colors::White, 3.14f);
}

/**********************************************************************************/

//Unit�̖��O
void SummonUnitUI::UnitName(const XMFLOAT2& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	pObject.GetText()->TextDraw(L":", pos + XMFLOAT2(140,0), Colors::White, 0.0f, 0.7f);

	XMFLOAT2 Pos(150, 0);

	switch (mType)
	{
		case UNIT_TYPE::SWORDFIGHTER:
		{
			pObject.GetText()->TextDraw(L"���m", pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::ARCHER:
		{
			pObject.GetText()->TextDraw(L"�|��", pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::GUNNER:
		{
			pObject.GetText()->TextDraw(L"�e�m", pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::CANNON:
		{
			pObject.GetText()->TextDraw(L"��C", pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::SHOGUN:
		{
			pObject.GetText()->TextDraw(L"��", pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		default:break;
	}
}

//Unit�̍U����
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
			pObject.GetText()->DrawInt(3, pos + Pos, Colors::White, 0.0f, 0.7f);
			break;
		}
		case UNIT_TYPE::CANNON:
		{
			pObject.GetText()->DrawInt(5, pos + Pos, Colors::White, 0.0f, 0.7f);
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

//Unit�̑���
void SummonUnitUI::Unitattribute(const XMFLOAT2& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1 = { 0,0,83,81 };
	RECT rect2 = { pos.x + 150,pos.y,pos.x + 190,pos.y + 40 };
	RECT rect3 = { pos.x + 190,pos.y,pos.x + 230,pos.y + 40 };

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

//�K�v�ȋ�
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