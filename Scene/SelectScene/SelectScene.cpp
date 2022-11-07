#include "pch.h"
#include"SelectScene.h"

#include"../PlayScene/Stage/StageNum.h"
#include"SelectUI/SelectUI.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
SelectScene::SelectScene()
	: mCameraView()
	, mStageNum(0)
	, mSceneFade(0.6f)
	, mMoveFadeFlag(false)
{

}

//�f�X�g���N�^
SelectScene::~SelectScene()
{

}

//������
void SelectScene::Initialize()
{
	mpSelectUI = std::make_unique<SelectUI>();

	mpSelectUI->Initialize();
}

//�X�V
GAME_SCENE SelectScene::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	SoundManager& soundmanager = SoundManager::GetInstance();

	mMoveFadeFlag = mpSelectUI->Update();

	if (mMoveFadeFlag == true && mSceneFade > 0.0f)
	{
		mSceneFade -= 0.01f;
	}
	else if (mSceneFade <= 0.0f)
	{
		soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::STOP);
		return GAME_SCENE::PLAY;
	}

	return mpSelectUI->Title_Back();
}


//�`��
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

//�I������
void SelectScene::Finalize()
{

}