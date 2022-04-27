#include"pch.h"
#include"TitleUI.h"
#include"../../PlayScene/Volume/Volume.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

TitleUI::TitleUI()
	:mSettingFlag(false)
	, mScene(GAME_SCENE::NONE)
{

}

TitleUI::~TitleUI()
{

}

void TitleUI::Update()
{
	InputManager& inputManager = InputManager::GetInstance();
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	//�V�[���̈ړ�
	if (mouseX > 600 && mouseX < 1000 && mouseY>650 && mouseY < 730 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == false)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::STOP);
		mScene = GAME_SCENE::SELECT;
	}

	//�ݒ�̉�ʂɈړ�
	if (mouseX > 600 && mouseX < 1000 && mouseY>750 && mouseY < 830 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == false)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		mSettingFlag = true;
	}

	//�^�C�g����ʂɖ߂�
	if (mouseX > 600 && mouseX < 1000 && mouseY>570 && mouseY < 650 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == true)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON2, SE_RUN::PLAY);
		mSettingFlag = false;
	}

	//BGM�̉��ʂ��グ��
	if (mouseX > 300 && mouseX < 400 && mouseY>200 && mouseY < 300 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == true &&
		pVolume.GetBgmVolume() < 10.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetBgmVolume(pVolume.GetBgmVolume() + 1.0f);
	}

	//BGM�̉��ʂ�������
	if (mouseX > 800 && mouseX < 900 && mouseY>200 && mouseY < 300 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == true &&
		pVolume.GetBgmVolume() > 0.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetBgmVolume(pVolume.GetBgmVolume() - 1.0f);
	}

	//SE�̉��ʂ��グ��
	if (mouseX > 300 && mouseX < 400 && mouseY>400 && mouseY < 500 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == true &&
		pVolume.GetSEVolume() < 10.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetSeVolume(pVolume.GetSEVolume() + 1.0f);
	}

	//SE�̉��ʂ�������
	if (mouseX > 800 && mouseX < 900 && mouseY>400 && mouseY < 500 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mSettingFlag == true &&
		pVolume.GetSEVolume() > 0.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetSeVolume(pVolume.GetSEVolume() - 1.0f);
	}
}

void TitleUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	RECT rect1;
	RECT rect2;
	rect2 = { 0,0,1600,900 };
	rect1 = { 0,0,700,700 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WALL, rect1, rect2);

	//�ݒ��ʂ��J����Ă��邩�ǂ���
	if (mSettingFlag == true)
	{
		DrawSetting();
	}
	else
	{
		rect1={ 0,0,1100,830 };
		rect2={ 300,50,1300,600 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::TITLE, rect1, rect2);

		rect1 = { 500,510 };
		rect2 = { 600,650,1000,730 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

		rect2 = { 600,750,1000,830 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

		if (mouseX > 600 && mouseX < 1000 && mouseY>650 && mouseY < 730)
		{
			rect2 = { 600,650,1000,730 };
			pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		}
		else if (mouseX > 600 && mouseX < 1000 && mouseY>750 && mouseY < 830)
		{
			rect2 = { 600,750,1000,830 };
			pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::LightSkyBlue);
		}

		pObject.GetText()->TextDraw(L"PLAY", XMFLOAT2(710, 655), Colors::White, 0.0f, 1.5f);
		pObject.GetText()->TextDraw(L" �ݒ�", XMFLOAT2(710, 755), Colors::White, 0.0f, 1.5f);
	}
}

//�ݒ�̕`��
void TitleUI::DrawSetting()
{
	Volume& pVolume = Volume::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	RECT rect1;
	RECT rect2;
	rect1 = { 500,520 };
	rect2 = { 100,50,1500,700 };
	//��Ԍ��̃E�B���h�E
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�߂�{�^��
	rect2 = { 600,570,1000,650 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	if (mouseX > 600 && mouseX < 1000 && mouseY>570 && mouseY < 650)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}

	//BGM���ʕύX�̃E�B���h�E
	rect2 = { 300,200,400,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);
	rect2 = { 800,200,900,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);
	rect2 = { 400,200,800,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//SE���ʕύX�̃E�B���h�E
	rect2 = { 300,400,400,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);
	rect2 = { 800,400,900,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);
	rect2 = { 400,400,800,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�}�E�X�J�[�\������������F��ς���
	if (mouseX > 300 &&mouseX < 400 &&mouseY>200 &&mouseY < 300)
	{
		rect2 = { 300,200,400,300 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	else if (mouseX > 800 &&mouseX < 900 &&mouseY>200 &&mouseY < 300)
	{
		rect2 = { 800,200,900,300 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	else if (mouseX > 300 &&mouseX < 400 &&mouseY>  400 &&mouseY < 500)
	{
		rect2 = { 300,400,400,500 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}
	else if (mouseX > 800 &&mouseX < 900 &&mouseY>  400 &&mouseY < 500)
	{
		rect2 = { 800,400,900,500 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Blue);
	}


	//BGM�ύX��UI
	rect1 = { 105,105 };
	rect2 = { 300+10,200+10,400-10,300-10 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::PLUS,rect1, rect2);

	rect1 = { 105,10 };
	rect2 = { 800 + 10,200 + 40,900 - 10,300 - 40 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MINUS, rect1, rect2);

	//SE�ύX��UI
	rect1 = { 105,105 };
	rect2 = { 300 + 10,200 + 10+200,400 - 10,300 - 10+200 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::PLUS, rect1, rect2);

	rect1 = { 105,10 };
	rect2 = { 800 + 10,200 + 40+200,900 - 10,300 - 40+200 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MINUS, rect1, rect2);


	//�����̕`��
	pObject.GetText()->TextDraw(L"�߂�", XMFLOAT2(710, 575), Colors::White, 0.0f, 1.5f);

	pObject.GetText()->TextDraw(L"BGM:",XMFLOAT2(480, 210), Colors::White, 0.0f, 1.5f);

	pObject.GetText()->DrawInt(static_cast<int>(pVolume.GetBgmVolume()), XMFLOAT2(650, 210), Colors::White, 0.0f, 1.5f);

	pObject.GetText()->TextDraw(L"SE :", XMFLOAT2(480, 410), Colors::White, 0.0f, 1.5f);

	pObject.GetText()->DrawInt(static_cast<int>(pVolume.GetSEVolume()), XMFLOAT2(650, 410), Colors::White, 0.0f, 1.5f);
}