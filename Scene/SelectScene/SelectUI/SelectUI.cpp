#include"pch.h"
#include"SelectUI.h"
#include"../../TitleScene/Button/Button.h"

#include"../../PlayScene/Stage/StageNum.h"

#include"../SelectStageLoad/SelectStageLoad.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::string STAGE_1("stage_1");
const std::string STAGE_2("stage_2");
const std::string STAGE_3("stage_3");
const std::string STAGE_4("stage_4");
const std::string TUTORIAL("tutorial");
const std::string BACK_TITLE("back");

//�R���X�g���N�^
SelectUI::SelectUI()
	:mMoveFadeFlag(false)
	, mStage_draw_num(0)
	, mBackTitle_Flag(false)
{

}

//�f�X�g���N�^
SelectUI::~SelectUI()
{

}

//������
void SelectUI::Initialize()
{
	mpButtons[TUTORIAL] = std::make_unique<Button>();
	mpButtons[STAGE_1] = std::make_unique<Button>();
	mpButtons[STAGE_2] = std::make_unique<Button>();
	mpButtons[STAGE_3] = std::make_unique<Button>();
	mpButtons[STAGE_4] = std::make_unique<Button>();
	mpButtons[BACK_TITLE] = std::make_unique<Button>();

	//�`����W�̐ݒ�
	mpButtons[TUTORIAL]->SetRECT(100, 30, 460, 120);
	mpButtons[STAGE_1]->SetRECT(100, 150, 400, 250);
	mpButtons[STAGE_2]->SetRECT(100, 300, 400, 400);
	mpButtons[STAGE_3]->SetRECT(100, 450, 400, 550);
	mpButtons[STAGE_4]->SetRECT(100, 600, 400, 700);
	mpButtons[BACK_TITLE]->SetRECT(100, 750, 500, 850);

	mMoveFadeFlag = false;

	mpSelectStageLoad = std::make_unique<SelectStageLoad>();

	mpSelectStageLoad->Initialize();
}

//�X�V
const bool SelectUI::Update()
{
	if (mpButtons[STAGE_1]->Determining_if_the_mouse_is_on() == true)
	{
		ClickEvent(0);
	}
	else if (mpButtons[STAGE_2]->Determining_if_the_mouse_is_on() == true)
	{
		ClickEvent(1);
	}
	else if (mpButtons[STAGE_3]->Determining_if_the_mouse_is_on() == true)
	{
		ClickEvent(2);
	}
	else if (mpButtons[STAGE_4]->Determining_if_the_mouse_is_on() == true)
	{
		ClickEvent(3);
	}
	else if (mpButtons[TUTORIAL]->Determining_if_the_mouse_is_on() == true)
	{
		ClickEvent(4);
	}
	else if (mpButtons[BACK_TITLE]->Determining_if_the_mouse_is_on() == true)
	{
		mBackTitle_Flag = true;
	}

	if (mpButtons[STAGE_1]->When_the_mouse_cursor_enters_the_range() == true)
	{
		mStage_draw_num = 1; mpSelectStageLoad->Update(mStage_draw_num);
	}
	else if (mpButtons[STAGE_2]->When_the_mouse_cursor_enters_the_range() == true)
	{
		mStage_draw_num = 2; mpSelectStageLoad->Update(mStage_draw_num);
	}
	else if (mpButtons[STAGE_3]->When_the_mouse_cursor_enters_the_range() == true)
	{
		mStage_draw_num = 3; mpSelectStageLoad->Update(mStage_draw_num);
	}
	else if (mpButtons[STAGE_4]->When_the_mouse_cursor_enters_the_range() == true)
	{
		mStage_draw_num = 4; mpSelectStageLoad->Update(mStage_draw_num);
	}
	else if (mpButtons[TUTORIAL]->When_the_mouse_cursor_enters_the_range() == true)
	{
		mStage_draw_num = 5; mpSelectStageLoad->Update(mStage_draw_num);
	}

	return mMoveFadeFlag;
}

//�`��
void SelectUI::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	RECT rect1;
	RECT rect2;

	//�ǂ̕`��͈�
	rect2 = { 0,0,1600,900 };
	//�摜�؂���͈�
	rect1 = { 0,0,700,700 };
	//�w�i(��)�̕`��
	pObject.GetTexture2D()->Draw(TEXTURE2D::WALL, rect1, rect2);

	mpSelectStageLoad->Draw();


	//�E�B���h�E�̐؂���͈�
	rect1 = { 500,510 };

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	mpButtons[TUTORIAL]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�`���[�g���A��", XMFLOAT2(0, 10), Colors::White, 1.5f, Colors::Gray, Colors::White);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	mpButtons[STAGE_1]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�X�e�[�W 1", XMFLOAT2(10, 20), Colors::White, 1.5f, Colors::Gray, Colors::White);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	mpButtons[STAGE_2]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�X�e�[�W 2", XMFLOAT2(10, 20), Colors::White, 1.5f, Colors::Gray, Colors::White);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	mpButtons[STAGE_3]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�X�e�[�W 3", XMFLOAT2(10, 20), Colors::White, 1.5f, Colors::Gray, Colors::White);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	mpButtons[STAGE_4]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�X�e�[�W 4", XMFLOAT2(10, 20), Colors::White, 1.5f, Colors::Gray, Colors::White);

	//�X�e�[�W�P�̃E�B���h�E�̕`��͈�
	mpButtons[BACK_TITLE]->DrawButton(rect1, TEXTURE2D::WINDOW, L"�^�C�g���֖߂�", XMFLOAT2(10, 20), Colors::White, 1.5f, Colors::Gray, Colors::White);
}

void SelectUI::ClickEvent(const int& stagenum)
{
	SoundManager& soundmanager = SoundManager::GetInstance();
	StageNum& setstage = StageNum::GetInstance();
	setstage.SetStage(stagenum);
	mMoveFadeFlag = true;

	soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
}

//�^�C�g���֖߂�
const GAME_SCENE SelectUI::Title_Back()
{
	if (mBackTitle_Flag == true)
		return GAME_SCENE::TITLE;

	return GAME_SCENE::NONE;
}