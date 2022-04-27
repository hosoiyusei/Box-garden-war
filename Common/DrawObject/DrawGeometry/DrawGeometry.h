#pragma once
#include<SimpleMath.h>
#include"../../ResourceManager/ResourceManager.h"

class DrawGeometry
{
public:

	//コンストラクタ
	DrawGeometry();
	//デストラクタ
	~DrawGeometry();

	//Geometryの描画
	void Draw(const DirectX::SimpleMath::Matrix& world
		,const SHAPE& shape
		,const DirectX::FXMVECTOR& color = DirectX::Colors::White);

	//Geometryの描画(カラーを変更できる)
	void DrawSetColor(const DirectX::SimpleMath::Matrix& world
		, const SHAPE& shape
		, const DirectX::SimpleMath::Color& color);
};