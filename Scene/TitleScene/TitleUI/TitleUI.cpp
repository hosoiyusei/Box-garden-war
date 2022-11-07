#include"pch.h"
#include"TitleUI.h"
#include"../../PlayScene/Volume/Volume.h"

#include"../Button/Button.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::string PLAY("play");
const std::string SETTING("setting");
const std::string BACK_TITLE("back_title");
const std::string BGM_PLUS("bgm_plus");
const std::string BGM_MINUS("bgm_minus");
const std::string SE_PLUS("se_plus");
const std::string SE_MINUS("se_minus");


TitleUI::TitleUI()
	:mSettingFlag(false)
	, mScene(GAME_SCENE::NONE)
{

}

TitleUI::~TitleUI()
{

}

void TitleUI::Initialize()
{
	mpButtons[PLAY] = std::make_unique<Button>();
	mpButtons[SETTING] = std::make_unique<Button>();
	mpButtons[BACK_TITLE] = std::make_unique<Button>();
	mpButtons[BGM_PLUS] = std::make_unique<Button>();
	mpButtons[BGM_MINUS] = std::make_unique<Button>();
	mpButtons[SE_PLUS] = std::make_unique<Button>();
	mpButtons[SE_MINUS] = std::make_unique<Button>();

	//�`����W�̐ݒ�
	mpButtons[PLAY]->SetRECT(600, 650, 1000, 730);
	mpButtons[SETTING]->SetRECT(600, 750, 1000, 830);
	mpButtons[BACK_TITLE]->SetRECT(600, 570, 1000, 650);
	mpButtons[BGM_PLUS]->SetRECT(1000, 200, 1100, 300);
	mpButtons[BGM_MINUS]->SetRECT(500, 200, 600, 300);
	mpButtons[SE_PLUS]->SetRECT(1000, 400, 1100, 500);
	mpButtons[SE_MINUS]->SetRECT(500, 400, 600, 500);
}

void TitleUI::Update()
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	//�V�[���̈ړ�
	if (mpButtons[PLAY]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == false)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::STOP);
		mScene = GAME_SCENE::SELECT;
	}

	//�ݒ�̉�ʂɈړ�
	if (mpButtons[SETTING]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == false)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		mSettingFlag = true;
	}

	if (mSettingFlag == true)
	{
		Setting_Update();
	}
}

void TitleUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

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
		rect1={ 0,0,1373,642 };
		rect2={ 350,50,1250,600 };
		pObject.GetTexture2D()->Draw(TEXTURE2D::TITLE, rect1, rect2);

		mpButtons[PLAY]->DrawButton(RECT{ 500,510 }, TEXTURE2D::WINDOW, L"PLAY", XMFLOAT2(100, 10), Colors::White, 1.5f, Colors::Gray, Colors::White);

		mpButtons[SETTING]->DrawButton(RECT{ 500,510 }, TEXTURE2D::WINDOW, L"�ݒ�", XMFLOAT2(120, 10), Colors::White, 1.5f, Colors::Gray, Colors::White);
	}
}

//�ݒ�̕`��
void TitleUI::DrawSetting()
{
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1;
	RECT rect2;
	rect1 = { 500,510 };

	//�߂�{�^��
	mpButtons[BACK_TITLE]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�߂�", XMFLOAT2(120, 10), Colors::White, 1.5f, Colors::Gray, Colors::White);

	//BGM���ʕύX�̃E�B���h�E
	mpButtons[BGM_PLUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	mpButtons[BGM_MINUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	rect2 = { 600,200,1000,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//SE���ʕύX�̃E�B���h�E
	mpButtons[SE_PLUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	mpButtons[SE_MINUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	rect2 = { 600,400,1000,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//����Gage�̕`��
	Sound_gage_draw();

	//BGM�ύX��UI
	rect1 = { 105,105 };
	rect2 = { 1010,210,1090,290 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::PLUS,rect1, rect2);

	rect1 = { 105,10 };
	rect2 = { 510,240,590,260 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MINUS, rect1, rect2);

	//SE�ύX��UI
	rect1 = { 105,105 };
	rect2 = { 1010,410,1090,490 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::PLUS, rect1, rect2);

	rect1 = { 105,10 };
	rect2 = { 510,440,590,460 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MINUS, rect1, rect2);


	//�����̕`��
	pObject.GetText()->TextDraw(L"BGM",XMFLOAT2(680, 200), Colors::Orange, 0.0f, 0.6f);

	pObject.GetText()->TextDraw(L"SE", XMFLOAT2(680, 400), Colors::Orange, 0.0f, 0.6f);
}

//�ݒ�̍X�V
void TitleUI::Setting_Update()
{
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	//�^�C�g����ʂɖ߂�
	if (mpButtons[BACK_TITLE]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == true)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON2, SE_RUN::PLAY);
		mSettingFlag = false;
	}

	//BGM�̉��ʂ��グ��
	if (mpButtons[BGM_PLUS]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == true &&
		pVolume.GetBgmVolume() < 10.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetBgmVolume(pVolume.GetBgmVolume() + 1.0f);
	}

	//BGM�̉��ʂ�������
	if (mpButtons[BGM_MINUS]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == true &&
		pVolume.GetBgmVolume() > 0.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetBgmVolume(pVolume.GetBgmVolume() - 1.0f);
	}

	//SE�̉��ʂ��グ��
	if (mpButtons[SE_PLUS]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == true &&
		pVolume.GetSEVolume() < 10.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetSeVolume(pVolume.GetSEVolume() + 1.0f);
	}

	//SE�̉��ʂ�������
	if (mpButtons[SE_MINUS]->Determining_if_the_mouse_is_on() == true &&
		mSettingFlag == true &&
		pVolume.GetSEVolume() > 0.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetSeVolume(pVolume.GetSEVolume() - 1.0f);
	}
}

//���ʂ̃Q�[�W�̕`��
void TitleUI::Sound_gage_draw()
{
	Volume& pVolume = Volume::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1, rect2;

	//BGM�̃Q�[�W�̕`��
	int bgmVolume = 1074 - (1074 - static_cast<int>(108 * pVolume.GetBgmVolume()));

	rect1 = { 0,0,bgmVolume,124 };

	rect2 = { 620,230,620 + static_cast<int>(36 * pVolume.GetBgmVolume()),270 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE, rect1, rect2, Colors::Orange);

	rect1 = { 0,0,1074,124 };
	rect2 = { 620,230,980,270 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE_FRAME, rect1, rect2);


	//SE�̃Q�[�W�̕`��
	int seVolume = 1074 - (1074 - static_cast<int>(108 * pVolume.GetSEVolume()));

	rect1 = { 0,0,seVolume,124 };

	rect2 = { 620,430,620 + static_cast<int>(36 * pVolume.GetSEVolume()),470 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE, rect1, rect2, Colors::Orange);

	rect1 = { 0,0,1074,124 };
	rect2 = { 620,430,980,470 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE_FRAME, rect1, rect2);
}