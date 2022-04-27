#pragma once
#include <SimpleMath.h>
#include"../../ResourceManager/ResourceManager.h"

class DrawModel
{
public:

	//�R���X�g���N�^
	DrawModel();
	//�f�X�g���N�^
	~DrawModel();

	//�`��
	void Draw(
		const DirectX::SimpleMath::Matrix& world
		, const MODEL_NAME& name);
};