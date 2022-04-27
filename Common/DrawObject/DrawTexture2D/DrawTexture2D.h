#pragma once
#include"../../ResourceManager/ResourceManager.h"

class DrawTexture2D
{
public:

	//�R���X�g���N�^
	DrawTexture2D();
	//�f�X�g���N�^
	~DrawTexture2D();

	//�`��
	void Draw(
		const TEXTURE2D& Texture
		, const RECT& recr
		, const RECT& recr2
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f);
};