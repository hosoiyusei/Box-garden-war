#pragma once
#include <SimpleMath.h>
#include"../../ResourceManager/ResourceManager.h"

class DrawModel
{
public:

	//コンストラクタ
	DrawModel();
	//デストラクタ
	~DrawModel();

	//描画
	void Draw(
		const DirectX::SimpleMath::Matrix& world
		, const MODEL_NAME& name);
};