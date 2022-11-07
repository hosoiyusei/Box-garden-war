#pragma once
#include<SimpleMath.h>

class Effect
{
private:

	//�G�t�F�N�g�̍��W
	DirectX::SimpleMath::Vector3 mPos, mStartPos;

	//�ړ����x
	DirectX::SimpleMath::Vector3 mSpeed;

	//�F
	DirectX::SimpleMath::Vector3 mColor;

	//���[���h
	DirectX::SimpleMath::Matrix mWorld;

	//�`�悷��e�N�X�`��
	TEXTURE3D mTexture;

	//�L�����ǂ����̃t���O
	bool mActive;

	//�����Ă鎞��
	int mActiveTimer;

	//�傫��
	float mSize;

	bool mSetBillboardFlag;

public:

	//�R���X�g���N�^
	Effect();
	//�f�X�g���N�^
	~Effect();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�t�F�N�g�̎��s
	void Play(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3 color
		, const TEXTURE3D& texture
		, const float& speed
		, const float& size
		, const bool& SetBillboard = false);

	void SetMoveVector(
		const DirectX::SimpleMath::Vector3& vel);

	//Active�t���O��Ԃ�
	const bool GetActive() { return mActive; }
};