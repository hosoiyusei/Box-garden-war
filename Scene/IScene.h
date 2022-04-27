/*
シーンインターフェース
*/
#pragma once
#include"Scene.h"

class IScene
{
public:

	virtual ~IScene() = default;

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual GAME_SCENE Update(const DX::StepTimer& timer) = 0; 

	// 描画
	virtual void Draw() = 0;

	virtual void Draw2() = 0;

	virtual void Forward() = 0;

	// 終了処理
	virtual void Finalize() = 0;
};