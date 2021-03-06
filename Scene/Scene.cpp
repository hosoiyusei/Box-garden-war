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
// RXgN^
//-------------------------------------------------------------------
Scene::Scene()
	: mNextScene(GAME_SCENE::TITLE)
	, mSceneInformation(GAME_SCENE::TITLE)
	,mpScene(nullptr)
{
}

//-------------------------------------------------------------------
// fXgN^
//-------------------------------------------------------------------
Scene::~Scene()
{
	Finalize();
}

//-------------------------------------------------------------------
// ϊ»
//-------------------------------------------------------------------
void Scene::Initialize()
{
	DrawManager& pObject = DrawManager::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();
	ADX2& adx2 = ADX2::GetInstance();

	//eνϊ»
	inputManager.Initialize();
	pGI.Initialize();
	pRm.AllRead();
	pObject.Initialize();
	adx2.Initialize(
		"Resources/Sound/GameSe.acf"
		, "Resources/Sound/CueSheet_0.acb");

	// V[μ¬
	CreateScene();
}

//-------------------------------------------------------------------
// XV
//-------------------------------------------------------------------
void Scene::Update(const DX::StepTimer& timer)
{
	InputManager& inputManager = InputManager::GetInstance();
	ADX2& adx2 = ADX2::GetInstance();
	Volume& volume = Volume::GetInstance();
	inputManager.Update();
	adx2.Update();

	//SeΜΉΚέθ
	adx2.SetVolume(volume.GetSEVolume());
	
	// ESCL[ΕIΉ
	if (inputManager.GetKeyboardState().Escape) PostQuitMessage(0);

	if (mNextScene != GAME_SCENE::NONE)
	{
		DeleteScene();//V[πν
		CreateScene();//V[πμ¬
	}

	if (mpScene != nullptr)
		mNextScene = mpScene->Update(timer);
}

//-------------------------------------------------------------------
// `ζ
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
// γn
//-------------------------------------------------------------------
void Scene::Finalize()
{
	ADX2& adx2 = ADX2::GetInstance();

	adx2.Finalize();
	DeleteScene();
}

//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘

void Scene::CreateScene()
{
	if (mpScene != nullptr)
		return;

	//ΜV[μ¬
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

	//ΦΜV[ξρΜϊ»
	mNextScene = GAME_SCENE::NONE;
}

void Scene::DeleteScene()
{
	if (mpScene == nullptr)
		return;

	mpScene->Finalize();
	mpScene.reset(nullptr);
}