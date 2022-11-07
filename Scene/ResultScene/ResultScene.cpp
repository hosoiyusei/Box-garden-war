#include "pch.h"
#include"ResultScene.h"

#include"Resultdata.h"

#include"../TitleScene/Button/Button.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::string TITLE_BACK("タイトルへ戻る");

//コンストラクタ
ResultScene::ResultScene()
	:mSceneFade(0.0f)
	, mCameraView()
{

}

//デストラクタ
ResultScene::~ResultScene()
{

}

//初期化
void ResultScene::Initialize()
{
	mpButtons[TITLE_BACK] = std::make_unique<Button>();

	//描画座標の設定
	mpButtons[TITLE_BACK]->SetRECT(600, 650, 1000, 730);
}

//更新
GAME_SCENE ResultScene::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);//警告除け
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mSceneFade <= 0.6f)
	{
		mSceneFade += 0.01f;
	}

	if (mpButtons[TITLE_BACK]->Determining_if_the_mouse_is_on() == true)
	{
		soundmanager.BGM_Run(SOUND_BGM::PLAY_BGM, BGM_RUN::STOP);
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		return GAME_SCENE::TITLE;
	}

	return GAME_SCENE::NONE;
}


//描画
void ResultScene::Draw()
{
	CameraParam& pCm = CameraParam::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();
	Resultdata* result = Resultdata::GetResultdataInstance();

	pCm.SetParam(mCameraView);

	RECT rect1, rect2;

	rect2 = { 0,0,1600,900 };
	rect1 = { 0,0,700,700 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WALL, rect1, rect2);//背景

	rect1 = {0,0, 1135,751 };

	rect2 = { 100,0,1500,900 };

	if (result->GetGameOver() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::DEFEAT, rect1, rect2,Colors::Blue);
	}
	else if (result->GetVictory() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::VECTORY, rect1, rect2, Colors::Yellow);
	}

	//タイトルに戻るウィンドウ
	mpButtons[TITLE_BACK]->DrawButton(RECT{ 500,510 }, TEXTURE2D::WINDOW, L"タイトルへ戻る", XMFLOAT2(15, 10), Colors::White, 1.5f, Colors::Gray, Colors::White);

	Matrix world = Matrix::Identity;

	pObject.GetTexture3D()->SetDraw(world);
	pObject.GetTexture3D()->SetColor(0.0f, 0.0f, 0.0f, mSceneFade);
	world *= Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));
	world *= Matrix::CreateScale(30.0f);
	pObject.GetTexture3D()->DrawBillboard(world);
	pObject.GetTexture3D()->HDrawShader(world, TEXTURE3D::PIT);
}

//終了処理
void ResultScene::Finalize()
{

}