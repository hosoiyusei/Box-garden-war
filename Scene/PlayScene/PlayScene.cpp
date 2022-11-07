#include"pch.h"
#include"Scene/PlayScene/PlayScene.h"

#include"Stage/StageNum.h"
#include"Volume/Volume.h"

#include"Stage/StageRead.h"
#include"Stage/StageDraw.h"
#include"EnemyManager/EnemyManager.h"
#include"Player/Player.h"
#include"UnitManager/UnitManager.h"
#include"BulletManager/BulletManager.h"
#include"EffectManager/EffectManager.h"
#include"Collision/CollisionManager.h"
#include"GameUI/GameUI.h"
#include"ItemManager/ItemManager.h"

#include"DoubleSpeed/DoubleSpeed.h"

#include"../ResultScene/Resultdata.h"
#include"Tutorial/Tutorial.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
PlayScene::PlayScene()
	:mCameraView()
	, mTimer()
	, mWorld()
	, mResultTimer(0)
	, mInitialFlag(false)
	, mFade(0.0f)
	, mFadeFlag(false)
	, mResultEffect(0.0f)
	, mFadeScale(15.5f)
	, mFade_adjustment(0.3f)
	, mFadeSize_adjustment(1.3f)
{
	
}

//デストラクタ
PlayScene::~PlayScene()
{

}

//初期化
void PlayScene::Initialize()
{
	StageNum& setstage = StageNum::GetInstance();
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	//ポインタを作成
	mpStageRead = std::make_unique<StageRead>();
	mpStageDraw = std::make_unique<StageDraw>();
	mpEnemyManager = std::make_unique<EnemyManager>();
	mpPlayer = std::make_unique<Player>();
	mpUnitManager = std::make_unique<UnitManager>();
	mpBulletManager = std::make_unique<BulletManager>();
	mpEffectManager = std::make_unique<EffectManager>();
	mpCollisionManager = std::unique_ptr<CollisionManager>();
	mpGameUI = std::make_unique<GameUI>();
	mpItemManager = std::make_unique<ItemManager>();
	mpTutorial = std::make_unique<Tutorial>();

	//各ポインタの初期化
	mpStageRead->SetStageNum(setstage.GetStageNum());

	mpStageDraw->Initialize(mpStageRead.get());

	mpEnemyManager->Initialize(
		mpStageRead.get()
		, mpBulletManager.get()
		, mpEffectManager.get()
		, mpEnemyManager.get()
		, mpPlayer.get()
		, mpItemManager.get()
		, mpTutorial.get());

	mpPlayer->Initialize(
		mpStageRead.get()
		, mpUnitManager.get()
		, mpStageDraw.get()
		, mpPlayer.get()
		, mpItemManager.get()
		, mpGameUI.get());

	mpUnitManager->Initialize(
		mpEnemyManager.get()
		, mpBulletManager.get()
		, mpEffectManager.get()
		, mpPlayer.get());
	mpBulletManager->Initialize(mpEffectManager.get());

	mpEffectManager->Initialize();

	mpGameUI->Initialize(mpEnemyManager.get(), mpPlayer.get(), mpUnitManager.get(),mpTutorial.get());

	mpItemManager->Initialize(mpPlayer.get());

	mpDoubleSpeed.SetExecutionFlag(true);

	mpTutorial->Initialize(mpPlayer.get());
}

//更新
GAME_SCENE PlayScene::Update(const DX::StepTimer& timer)
{
	mTimer=timer;
	Resultdata* result = Resultdata::GetResultdataInstance();

	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	mpTutorial->Update();

	if (mFadeFlag == false && mFade <= 0.6f)
	{
		mFade += 0.008;
	}
	else
	{
		mFade_adjustment = 1.0f;
		mFadeFlag = true;
	}

	if (mInitialFlag == false)
	{
		//BGMの再生
		soundmanager.BGM_Run(SOUND_BGM::PLAY_BGM, BGM_RUN::LOOP);
		mInitialFlag = true;
	}

	//BGMの音量設定
	soundmanager.BGM_Run(SOUND_BGM::PLAY_BGM, BGM_RUN::VOLUME, pVolume.GetBgmVolume());

	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		mpCollisionManager->CheckHit(mpEnemyManager.get());

		mpEnemyManager->Update();
		
		mpBulletManager->Update();
		
		mpItemManager->Update();
	}

	mpEffectManager->Update();
	mpUnitManager->Update();

	mpPlayer->Update();
	mpGameUI->Update();

	mCameraView = mpPlayer->GetCameraParam();
	
	//シーンを移動
	if (mpPlayer->GetClear() == true ||
		mpPlayer->GetGameOver() == true)
	{
		mResultTimer++;

		if (mResultEffect < 1.6f)
			mResultEffect += 0.01f;
	}

	if (mResultTimer >= 240||
		mpGameUI->BackSelectScene() == true)
	{
		mFadeSize_adjustment = 0.2f;
		if (mFade >= 0.01f)
		{
			mFade -= 0.01f;
		}
		else
		{
			result->SetGameOver(mpPlayer->GetGameOver());
			result->SetVictory(mpPlayer->GetClear());
			result->SetMoney(mpPlayer->GetMoney());

			if (mpGameUI->BackSelectScene() == true)
			{
				return GAME_SCENE::SELECT;
			}

			return GAME_SCENE::RESOULT;
		}
	}
	
	return GAME_SCENE::NONE;
}

//描画
void PlayScene::Draw()
{
	CameraParam& pCm = CameraParam::GetInstance();
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;

	world *= Matrix::CreateScale(3.0f);
	pObject.GetModel()->Draw(world, MODEL_NAME::SKY);

	pCm.SetParam(mCameraView);
	mpStageDraw->Draw();
	mpEnemyManager->Draw();
	mpUnitManager->Draw();
	mpBulletManager->Draw();

	pObject.GetTexture3D()->SetDraw(mWorld);

	mpTutorial->Draw();
	mpPlayer->Draw();
	mpEffectManager->Draw();
	mpEnemyManager->EffectDraw();
	mpUnitManager->EffectDraw();
	mpItemManager->Draw();
}

void PlayScene::Draw2()
{
	CameraParam& pCm = CameraParam::GetInstance();
	pCm.SetParam(mCameraView);
	mpGameUI->Draw();
	mpTutorial->Draw2();
}

void PlayScene::Forward()
{
	DrawManager& pObject = DrawManager::GetInstance();

	Vector3 target(mCameraView.targetX, mCameraView.targetY, mCameraView.targetZ);

	Vector3 eye(mCameraView.eyeX, mCameraView.eyeY, mCameraView.eyeZ);

	Vector3 vel(target - eye);

	Vector3 p(eye + vel * 0.061f);

	Matrix world = Matrix::Identity;

	
	
	world *= Matrix::CreateRotationY(3.14f);
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale(2.0f);
	world *= Matrix::CreateTranslation(p);

	if (mpPlayer->GetClear() == true)
	{
		pObject.GetTexture3D()->SetColor(2.0f, 2.0f, 0.0f, mResultEffect);
		pObject.GetTexture3D()->MDrawShader(world, TEXTURE3D::VICTORY);
	}
	else if (mpPlayer->GetGameOver() == true)
	{
		pObject.GetTexture3D()->SetColor(0.2f, 0.2f, 2.0f, mResultEffect);
		pObject.GetTexture3D()->MDrawShader(world, TEXTURE3D::DEFEAT);
	}

	vel = (target - eye);

	p=Vector3(eye + vel * 0.06f);

	world = Matrix::Identity;
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale(mFadeScale * mFadeSize_adjustment);
	world *= Matrix::CreateTranslation(p);
	
	pObject.GetTexture3D()->SetColor(0.0f, 0.0f, 0.0f, mFade);
	
	pObject.GetTexture3D()->HDrawShader(world, TEXTURE3D::FADE3D);
}

//終了処理
void PlayScene::Finalize()
{
	
}