#pragma once

//�O���錾
class Effect;

class EffectManager
{
private:

	//Effect�̔z��
	std::vector<std::unique_ptr<Effect>> mpEffect;

public:

	//�R���X�g���N�^
	EffectManager();
	//�f�X�g���N�^
	~EffectManager();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�t�F�N�g�̎��s
	void Play(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& color
		, const int& number
		, const TEXTURE3D& texture
		, const float& speed = 0.003f
		, const float& size = 0.3f);

	//�G�t�F�N�g�̎��s
	void Play_2(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& color
		, const int& number
		, const TEXTURE3D& texture
		, const float& speed = 0.003f
		, const float& size = 0.3f);

	//�G�t�F�N�g�̎��s
	void Play_3(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& color
		, const int& number
		, const TEXTURE3D& texture
		, const float& speed = 0.003f
		, const float& size = 0.3f);
};