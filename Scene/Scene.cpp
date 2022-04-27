//
// Scene.cpp
//
#include "pch.h"
#include "Scene.h"

#include"Common/SoundManager/Adx2.h"
#include"PlayScene/Volume/Volume.h"

#include"TitleScene/TitleScene.h"
#include"SelectScene/SelectScene.h"
#include"PlayScene/PlayScene.h"
#include"ResultScene/ResultScene.h"

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
Scene::Scene()
	: mNextScene(GAME_SCENE::TITLE)
	, mSceneInformation(GAME_SCENE::TITLE)
	,mpScene(nullptr)
{
}

//-------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------
Scene::~Scene()
{
	Finalize();
}

//-------------------------------------------------------------------
// 初期化処理
//-------------------------------------------------------------------
void Scene::Initialize()
{
	DrawManager& pObject = DrawManager::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();
	ADX2& adx2 = ADX2::GetInstance();

	//各種初期化
	inputManager.Initialize();
	pGI.Initialize();
	pRm.AllRead();
	pObject.Initialize();
	adx2.Initialize(
		"Resources/Sound/GameSe.acf"
		, "Resources/Sound/CueSheet_0.acb");

	// シーン作成
	CreateScene();
}

//-------------------------------------------------------------------
// 更新処理
//-------------------------------------------------------------------
void Scene::Update(const DX::StepTimer& timer)
{
	InputManager& inputManager = InputManager::GetInstance();
	ADX2& adx2 = ADX2::GetInstance();
	Volume& volume = Volume::GetInstance();
	inputManager.Update();
	adx2.Update();

	//Seの音量設定
	adx2.SetVolume(volume.GetSEVolume());
	
	// ESCキーで終了
	if (inputManager.GetKeyboardState().Escape) PostQuitMessage(0);

	if (mNextScene != GAME_SCENE::NONE)
	{
		DeleteScene();//シーンを削除
		CreateScene();//シーンを作成
	}

	if (mpScene != nullptr)
		mNextScene = mpScene->Update(timer);
}

//-------------------------------------------------------------------
// 描画処理
//-------------------------------------------------------------------
void Scene::Render()
{
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}
}
void Scene::Render2()
{
	if (mpScene != nullptr)
	{
		mpScene->Draw2();
	}
}

void Scene::Forward()
{
	if (mpScene != nullptr)
	{
		mpScene->Forward();
	}
}

//-------------------------------------------------------------------
// 後始末
//-------------------------------------------------------------------
void Scene::Finalize()
{
	ADX2& adx2 = ADX2::GetInstance();

	adx2.Finalize();
	DeleteScene();
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void Scene::CreateScene()
{
	if (mpScene != nullptr)
		return;

	//次のシーン作成
	switch (mNextScene)
	{
		case GAME_SCENE::TITLE:
		{
			mpScene = std::make_unique<TitleScene>();
			mSceneInformation = GAME_SCENE::TITLE;
			break;
		}
		case GAME_SCENE::SELECT:
		{
			mpScene = std::make_unique<SelectScene>();
			mSceneInformation = GAME_SCENE::SELECT;
			break;
		}
		case GAME_SCENE::PLAY:
		{
			mpScene = std::make_unique<PlayScene>();
			mSceneInformation = GAME_SCENE::PLAY;
			break;
		}
		case GAME_SCENE::RESOULT:
		{
			mpScene = std::make_unique<ResultScene>();
			mSceneInformation = GAME_SCENE::RESOULT;
			break;
		}
		default:return;
	}

	mpScene->Initialize();

	//次へのシーン情報の初期化
	mNextScene = GAME_SCENE::NONE;
}

void Scene::DeleteScene()
{
	if (mpScene == nullptr)
		return;

	mpScene->Finalize();
	mpScene.reset(nullptr);
}