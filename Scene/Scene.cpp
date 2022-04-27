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
// �R���X�g���N�^
//-------------------------------------------------------------------
Scene::Scene()
	: mNextScene(GAME_SCENE::TITLE)
	, mSceneInformation(GAME_SCENE::TITLE)
	,mpScene(nullptr)
{
}

//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
Scene::~Scene()
{
	Finalize();
}

//-------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------
void Scene::Initialize()
{
	DrawManager& pObject = DrawManager::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();
	ADX2& adx2 = ADX2::GetInstance();

	//�e�평����
	inputManager.Initialize();
	pGI.Initialize();
	pRm.AllRead();
	pObject.Initialize();
	adx2.Initialize(
		"Resources/Sound/GameSe.acf"
		, "Resources/Sound/CueSheet_0.acb");

	// �V�[���쐬
	CreateScene();
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void Scene::Update(const DX::StepTimer& timer)
{
	InputManager& inputManager = InputManager::GetInstance();
	ADX2& adx2 = ADX2::GetInstance();
	Volume& volume = Volume::GetInstance();
	inputManager.Update();
	adx2.Update();

	//Se�̉��ʐݒ�
	adx2.SetVolume(volume.GetSEVolume());
	
	// ESC�L�[�ŏI��
	if (inputManager.GetKeyboardState().Escape) PostQuitMessage(0);

	if (mNextScene != GAME_SCENE::NONE)
	{
		DeleteScene();//�V�[�����폜
		CreateScene();//�V�[�����쐬
	}

	if (mpScene != nullptr)
		mNextScene = mpScene->Update(timer);
}

//-------------------------------------------------------------------
// �`�揈��
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
// ��n��
//-------------------------------------------------------------------
void Scene::Finalize()
{
	ADX2& adx2 = ADX2::GetInstance();

	adx2.Finalize();
	DeleteScene();
}

//��������������������������������������������������������������������������������������������������������������������������������������������

void Scene::CreateScene()
{
	if (mpScene != nullptr)
		return;

	//���̃V�[���쐬
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

	//���ւ̃V�[�����̏�����
	mNextScene = GAME_SCENE::NONE;
}

void Scene::DeleteScene()
{
	if (mpScene == nullptr)
		return;

	mpScene->Finalize();
	mpScene.reset(nullptr);
}