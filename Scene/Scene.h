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

// 前方宣言
class DebugCamera;
class GridFloor;
class IScene;

/// <summary>
/// Gameクラスから、ユーザ処理部分を抜き出したクラス
/// </summary>
class Scene
{
private:

    // 次のシーン番号
    GAME_SCENE mNextScene;
    GAME_SCENE mSceneInformation;
    // シーン
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

    // シーンの作成
    void CreateScene();

    // シーンの削除
    void DeleteScene();
};
