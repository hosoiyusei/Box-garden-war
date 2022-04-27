#pragma once
#include "StepTimer.h"

enum class GAME_SCENE : int
{
    NONE,

    TITLE,
    SELECT,
    PLAY,
    RESOULT,
};

// �O���錾
class DebugCamera;
class GridFloor;
class IScene;

/// <summary>
/// Game�N���X����A���[�U���������𔲂��o�����N���X
/// </summary>
class Scene
{
private:

    // ���̃V�[���ԍ�
    GAME_SCENE mNextScene;
    GAME_SCENE mSceneInformation;
    // �V�[��
   std::unique_ptr<IScene> mpScene;

public:
    Scene();
    ~Scene();

    void Initialize();
    void Update(const DX::StepTimer& timer);
    void Render();
    void Render2();

    void Forward();
    void Finalize();

    const GAME_SCENE& GetScene() { return mSceneInformation; }

private:

    // �V�[���̍쐬
    void CreateScene();

    // �V�[���̍폜
    void DeleteScene();
};
