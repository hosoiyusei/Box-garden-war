#include"pch.h"
#include"PlaySetting.h"

#include"../../TitleScene/Button/Button.h"
#include"../Volume/Volume.h"

const std::string BACKSELECT("セレクトへ戻る");
const std::string BGM_PLUS("bgm_plus");
const std::string BGM_MINUS("bgm_minus");
const std::string SE_PLUS("se_plus");
const std::string SE_MINUS("se_minus");

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlaySetting::PlaySetting()
	:mBackSelectFlag(false)
{

}

void PlaySetting::Initialize()
{
	mpButtons[BACKSELECT] = std::make_unique<Button>();
	mpButtons[BGM_PLUS] = std::make_unique<Button>();
	mpButtons[BGM_MINUS] = std::make_unique<Button>();
	mpButtons[SE_PLUS] = std::make_unique<Button>();
	mpButtons[SE_MINUS] = std::make_unique<Button>();

	//描画座標の設定
	mpButtons[BACKSELECT]->SetRECT(800-190, 600, 990, 660);

	mpButtons[BGM_PLUS]->SetRECT(1000, 200, 1100, 300);
	mpButtons[BGM_MINUS]->SetRECT(500, 200, 600, 300);
	mpButtons[SE_PLUS]->SetRECT(1000, 400, 1100, 500);
	mpButtons[SE_MINUS]->SetRECT(500, 400, 600, 500);
}

void PlaySetting::Update()
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	Setting_Update();

	if (mpButtons[BACKSELECT]->Determining_if_the_mouse_is_on() == true)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		mBackSelectFlag = true;
	}
}

void PlaySetting::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1;
	RECT rect2;

	rect1 = { 500,510 };

	mpButtons[BACKSELECT]->DrawButton({ 500,500 }, TEXTURE2D::WINDOW, L"ステージセレクトに戻る", XMFLOAT2(0,10), Colors::White, 1.0f, Colors::Gray, Colors::White);

	//BGM音量変更のウィンドウ
	mpButtons[BGM_PLUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	mpButtons[BGM_MINUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	rect2 = { 600,200,1000,300 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//SE音量変更のウィンドウ
	mpButtons[SE_PLUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	mpButtons[SE_MINUS]->DrawButton(rect1, TEXTURE2D::WINDOW, L" ", XMFLOAT2(110, 10), Colors::White, 0.0f, Colors::Gray, Colors::White);

	rect2 = { 600,400,1000,500 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);
	Sound_gage_draw();

	//BGM変更のUI
	rect1 = { 105,105 };
	rect2 = { 1010,210,1090,290 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::PLUS, rect1, rect2);

	rect1 = { 105,10 };
	rect2 = { 510,240,590,260 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MINUS, rect1, rect2);

	//SE変更のUI
	rect1 = { 105,105 };
	rect2 = { 1010,410,1090,490 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::PLUS, rect1, rect2);

	rect1 = { 105,10 };
	rect2 = { 510,440,590,460 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::MINUS, rect1, rect2);


	//文字の描画
	pObject.GetText()->TextDraw(L"BGM", XMFLOAT2(680, 200), Colors::Orange, 0.0f, 0.6f);

	pObject.GetText()->TextDraw(L"SE", XMFLOAT2(680, 400), Colors::Orange, 0.0f, 0.6f);
}

//音量のゲージの描画
void PlaySetting::Sound_gage_draw()
{
	Volume& pVolume = Volume::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1, rect2;

	//BGMのゲージの描画
	int bgmVolume = 1074 - (1074 - static_cast<int>(108 * pVolume.GetBgmVolume()));

	rect1 = { 0,0,bgmVolume,124 };

	rect2 = { 620,230,620 + static_cast<int>(36 * pVolume.GetBgmVolume()),270 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE, rect1, rect2, Colors::Orange);

	rect1 = { 0,0,1074,124 };
	rect2 = { 620,230,980,270 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE_FRAME, rect1, rect2);


	//SEのゲージの描画
	int seVolume = 1074 - (1074 - static_cast<int>(108 * pVolume.GetSEVolume()));

	rect1 = { 0,0,seVolume,124 };

	rect2 = { 620,430,620 + static_cast<int>(36 * pVolume.GetSEVolume()),470 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE, rect1, rect2, Colors::Orange);

	rect1 = { 0,0,1074,124 };
	rect2 = { 620,430,980,470 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::GAGE_FRAME, rect1, rect2);
}

//設定の更新
void PlaySetting::Setting_Update()
{
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	//BGMの音量を上げる
	if (mpButtons[BGM_PLUS]->Determining_if_the_mouse_is_on() == true &&
		pVolume.GetBgmVolume() < 10.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetBgmVolume(pVolume.GetBgmVolume() + 1.0f);
	}

	//BGMの音量を下げる
	if (mpButtons[BGM_MINUS]->Determining_if_the_mouse_is_on() == true &&
		pVolume.GetBgmVolume() > 0.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetBgmVolume(pVolume.GetBgmVolume() - 1.0f);
	}

	//SEの音量を上げる
	if (mpButtons[SE_PLUS]->Determining_if_the_mouse_is_on() == true&&
		pVolume.GetSEVolume() < 10.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetSeVolume(pVolume.GetSEVolume() + 1.0f);
	}

	//SEの音量を下げる
	if (mpButtons[SE_MINUS]->Determining_if_the_mouse_is_on() == true&&
		pVolume.GetSEVolume() > 0.0f)
	{
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		pVolume.SetSeVolume(pVolume.GetSEVolume() - 1.0f);
	}
}