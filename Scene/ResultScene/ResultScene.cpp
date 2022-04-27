#include "pch.h"
#include"ResultScene.h"

#include"Resultdata.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
ResultScene::ResultScene()
	:mSceneFade(0.0f)
	, mCameraView()
{

}

//�f�X�g���N�^
ResultScene::~ResultScene()
{

}

//������
void ResultScene::Initialize()
{

}

//�X�V
GAME_SCENE ResultScene::Update(const DX::StepTimer& timer)
{
	timer;//�x������
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mSceneFade <= 0.6f)
	{
		mSceneFade += 0.01f;
	}

	//�^�C�g���ɖ߂�
	if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
		inputManager.GetMouseState().x > 600 &&
		inputManager.GetMouseState().x < 1000 &&
		inputManager.GetMouseState().y>650 &&
		inputManager.GetMouseState().y < 730)
	{
		soundmanager.BGM_Run(SOUND_BGM::PLAY_BGM, BGM_RUN::STOP);
		soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		return GAME_SCENE::TITLE;
	}

	return GAME_SCENE::NONE;
}


//�`��
void ResultScene::Draw()
{
	CameraParam& pCm = CameraParam::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();
	Resultdata* result = Resultdata::GetResultdataInstance();
	InputManager& inputManager = InputManager::GetInstance();

	pCm.SetParam(mCameraView);

	RECT rect1, rect2;

	rect2 = { 0,0,1600,900 };
	rect1 = { 0,0,700,700 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WALL, rect1, rect2);//�w�i

	rect1 = {0,0, 1130,751 };

	rect2 = { 0,-300,1300,1000 };

	if (result->GetGameOver() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::DEFEAT, rect1, rect2,Colors::Blue);
	}
	else if (result->GetVictory() == true)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::VECTORY, rect1, rect2, Colors::Yellow);
	}

	//�^�C�g���ɖ߂�E�B���h�E
	rect1 = { 500,510 };
	rect2 = { 600,650,1000,730 };
	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2);

	//�}�E�X���\���I���K�͈͓��Ȃ�F��ς���
	if (inputManager.GetMouseState().x > 600 &&
		inputManager.GetMouseState().x < 1000 &&
		inputManager.GetMouseState().y>650 &&
		inputManager.GetMouseState().y < 730)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, rect1, rect2, Colors::Black);
	}

	pObject.GetText()->TextDraw(L"�^�C�g���֖߂�", XMFLOAT2(620, 660), Colors::White, 0.0f, 1.5f);

	Matrix world = Matrix::Identity;

	pObject.GetTexture3D()->SetDraw(world);
	pObject.GetTexture3D()->SetColor(0.0f, 0.0f, 0.0f, mSceneFade);
	world *= Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));
	world *= Matrix::CreateScale(30.0f);
	pObject.GetTexture3D()->DrawBillboard(world);
	pObject.GetTexture3D()->HDrawShader(world, TEXTURE3D::PIT);
}

//�I������
void ResultScene::Finalize()
{

}