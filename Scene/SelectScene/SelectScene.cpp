#include "pch.h"
#include"SelectScene.h"

#include"../PlayScene/Stage/StageNum.h"
#include"SelectUI/SelectUI.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
SelectScene::SelectScene()
	: mCameraView()
	, mStageNum(0)
	, mSceneFade(0.6f)
	, mMoveFadeFlag(false)
{

}

//デストラクタ
SelectScene::~SelectScene()
{

}

//初期化
void SelectScene::Initialize()
{
	mpSelectUI = std::make_unique<SelectUI>();
}

//更新
GAME_SCENE SelectScene::Update(const DX::StepTimer& timer)
{
	timer;//警告除け
	InputManager& inputManager = InputManager::GetInstance();

	StageNum& setstage = StageNum::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	if (mouseX > 100 && mouseX < 400 && mouseY>100 && mouseY < 200 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		setstage.SetStage(0);
		mMoveFadeFlag = true;
		//return GAME_SCENE::PLAY;
	}
	else if (mouseX > 100 && mouseX < 400 && mouseY>250 && mouseY < 350 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		setstage.SetStage(1);
		mMoveFadeFlag = true;
		//return GAME_SCENE::PLAY;
	}
	else if (mouseX > 100 && mouseX < 400 && mouseY>400 && mouseY < 500 &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		setstage.SetStage(2);
		mMoveFadeFlag = true;
		//return GAME_SCENE::PLAY;
	}
	else if (mouseX > 100 && mouseX < 400 && mouseY>550 && mouseY < 650&&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		setstage.SetStage(3);
		mMoveFadeFlag = true;
		//return GAME_SCENE::PLAY;
	}

	if (mMoveFadeFlag == true && mSceneFade > 0.0f)
	{
		mSceneFade -= 0.01f;
	}
	else if (mSceneFade <= 0.0f)
	{
		soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::STOP);
		return GAME_SCENE::PLAY;
	}

	return GAME_SCENE::NONE;
}


//描画
void SelectScene::Draw()
{
	CameraParam& pCm = CameraParam::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();

	pCm.SetParam(mCameraView);

	mpSelectUI->Draw();

	Matrix world = Matrix::Identity;

	pObject.GetTexture3D()->SetDraw(world);
	pObject.GetTexture3D()->SetColor(0.0f, 0.0f, 0.0f, mSceneFade);
	world *= Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));
	world *= Matrix::CreateScale(30.0f);
	pObject.GetTexture3D()->DrawBillboard(world);
	pObject.GetTexture3D()->HDrawShader(world,TEXTURE3D::PIT);
}

//終了処理
void SelectScene::Finalize()
{

}