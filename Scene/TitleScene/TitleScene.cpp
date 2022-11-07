#include "pch.h"
#include"TitleScene.h"
#include"Common/SoundManager/Adx2.h"
#include"TitleUI/TitleUI.h"
#include"../PlayScene/Volume/Volume.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
TitleScene::TitleScene()
	:mInitialFlag(false)
{

}

//�f�X�g���N�^
TitleScene::~TitleScene()
{

}

//������
void TitleScene::Initialize()
{
	mpTitleUI = std::make_unique<TitleUI>();

	mpTitleUI->Initialize();
}

//�X�V
GAME_SCENE TitleScene::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);//�x������
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mInitialFlag == false)
	{
		//BGm�̍Đ�
		soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::LOOP);
		mInitialFlag = true;
	}

	//BGm�̉��ʐݒ�
	soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::VOLUME, pVolume.GetBgmVolume());

	//UI�̍X�V
	mpTitleUI->Update();

	//�V�[���̈ړ�
	return mpTitleUI->GetScene();
}

//�`��
void TitleScene::Draw()
{
	CameraParam& pCm = CameraParam::GetInstance();
	
	pCm.SetParam(mCameraView);

	mpTitleUI->Draw();
}

//�I������
void TitleScene::Finalize()
{
	
}