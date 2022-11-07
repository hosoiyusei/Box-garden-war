#include "pch.h"
#include"TitleScene.h"
#include"Common/SoundManager/Adx2.h"
#include"TitleUI/TitleUI.h"
#include"../PlayScene/Volume/Volume.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
TitleScene::TitleScene()
	:mInitialFlag(false)
{

}

//デストラクタ
TitleScene::~TitleScene()
{

}

//初期化
void TitleScene::Initialize()
{
	mpTitleUI = std::make_unique<TitleUI>();

	mpTitleUI->Initialize();
}

//更新
GAME_SCENE TitleScene::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);//警告除け
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mInitialFlag == false)
	{
		//BGmの再生
		soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::LOOP);
		mInitialFlag = true;
	}

	//BGmの音量設定
	soundmanager.BGM_Run(SOUND_BGM::TITLE_BGM, BGM_RUN::VOLUME, pVolume.GetBgmVolume());

	//UIの更新
	mpTitleUI->Update();

	//シーンの移動
	return mpTitleUI->GetScene();
}

//描画
void TitleScene::Draw()
{
	CameraParam& pCm = CameraParam::GetInstance();
	
	pCm.SetParam(mCameraView);

	mpTitleUI->Draw();
}

//終了処理
void TitleScene::Finalize()
{
	
}