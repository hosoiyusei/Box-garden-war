#pragma once
#include<SimpleMath.h>
#include"../../ResourceManager/ResourceManager.h"

class DrawGeometry
{
public:

	//�R���X�g���N�^
	DrawGeometry();
	//�f�X�g���N�^
	~DrawGeometry();

	//Geometry�̕`��
	void Draw(const DirectX::SimpleMath::Matrix& world
		,const SHAPE& shape
		,const DirectX::FXMVECTOR& color = DirectX::Colors::White);

	//Geometry�̕`��(�J���[��ύX�ł���)
	void DrawSetColor(const DirectX::SimpleMath::Matrix& world
		, const SHAPE& shape
		, const DirectX::SimpleMath::Color& color);
};