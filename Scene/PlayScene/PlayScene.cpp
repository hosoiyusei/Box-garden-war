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

	//各ポインタの初期化
	mpStageRead->SetStageNum(setstage.GetStageNum());

	mpStageDraw->Initialize(mpStageRead.get());

	mpEnemyManager->Initialize(
		mpStageRead.get()
		, mpBulletManager.get()
		, mpEffectManager.get()
		, mpEnemyManager.get()
		, mpPlayer.get()
		, mpItemManager.get());

	mpPlayer->Initialize(
		mpStageRead.get()
		, mpUnitManager.get()
		, mpStageDraw.get()
		, mpPlayer.get()
		, mpItemManager.get());

	mpUnitManager->Initialize(
		mpEnemyManager.get()
		, mpBulletManager.get()
		, mpEffectManager.get());
	mpBulletManager->Initialize(mpEffectManager.get());

	mpEffectManager->Initialize();

	mpGameUI->Initialize(mpPlayer.get());

	mpItemManager->Initialize(mpPlayer.get());

	mpDoubleSpeed.SetExecutionFlag(true);
}

//更新
GAME_SCENE PlayScene::Update(const DX::StepTimer& timer)
{
	mTimer=timer;
	Resultdata* result = Resultdata::GetResultdataInstance();

	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	Volume& pVolume = Volume::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mFadeFlag == false && mFade <= 0.6f)
	{
		mFade += 0.01;
	}
	else
	{
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
		mpUnitManager->Update();
		mpBulletManager->Update();
		mpEffectManager->Update();
		mpItemManager->Update();
	}

	mpPlayer->Update();

	mCameraView = mpPlayer->GetCameraParam();
	mCameraView.eyeY = abs(mCameraView.eyeY)+10.0f;
	
	//シーンを移動
	if (mpPlayer->GetClear() == true ||
		mpPlayer->GetGameOver() == true)
	{
		mResultTimer++;

		if (mResultEffect < 1.6f)
			mResultEffect += 0.01f;
	}

	if (mResultTimer >= 240)
	{
		if (mFade >= 0.01f)
		{
			mFade -= 0.01f;
		}
		else
		{
			result->SetGameOver(mpPlayer->GetGameOver());
			result->SetVictory(mpPlayer->GetClear());
			result->SetMoney(mpPlayer->GetMoney());
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

	world *= Matrix::CreateScale(-1.0f,1.0f,1.0f);

	pObject.GetModel()->Draw(world, MODEL_NAME::SKY);

	pCm.SetParam(mCameraView);
	mpStageDraw->Draw();
	mpEnemyManager->Draw();
	mpUnitManager->Draw();
	mpBulletManager->Draw();

	pObject.GetTexture3D()->SetDraw(mWorld);

	mpPlayer->Draw();
	mpEffectManager->Draw();
	mpEnemyManager->EffectDraw();
	mpUnitManager->EffectDraw();
	mpItemManager->Draw();
}

void PlayScene::Draw2()
{
	mpGameUI->Draw();
}

void PlayScene::Forward()
{
	DrawManager& pObject = DrawManager::GetInstance();

	Vector3 p = Vector3(mCameraView.targetX, -mCameraView.targetZ, mCameraView.eyeY - 5.0f);
	Matrix world = Matrix::Identity;
	if (mpPlayer->GetClear() == true)
	{
		world *= Matrix::CreateScale(5.0f);
		world *= Matrix::CreateRotationY(3.14f);
		world *= Matrix::CreateTranslation(p);
		pObject.GetTexture3D()->SetColor(2.0f, 2.0f, 0.0f, mResultEffect);
		pObject.GetTexture3D()->DrawBillboard(world);
		pObject.GetTexture3D()->MDrawShader(world, TEXTURE3D::VICTORY);
	}
	else if (mpPlayer->GetGameOver() == true)
	{
		world *= Matrix::CreateScale(5.0f);
		world *= Matrix::CreateRotationY(3.14f);
		world *= Matrix::CreateTranslation(p);
		pObject.GetTexture3D()->SetColor(0.2f, 0.2f, 2.0f, mResultEffect);
		pObject.GetTexture3D()->DrawBillboard(world);
		pObject.GetTexture3D()->MDrawShader(world, TEXTURE3D::DEFEAT);
	}

	world = Matrix::Identity;
	p = Vector3(mCameraView.targetX, -mCameraView.targetZ, mCameraView.eyeY - 1.0f);
	world *= Matrix::CreateScale(2.0f);
	world *= Matrix::CreateTranslation(p);

	pObject.GetTexture3D()->SetColor(0.0f, 0.0f, 0.0f, mFade);
	pObject.GetTexture3D()->DrawBillboard(world);
	pObject.GetTexture3D()->HDrawShader(world, TEXTURE3D::PIT);
}

//終了処理
void PlayScene::Finalize()
{
	
}