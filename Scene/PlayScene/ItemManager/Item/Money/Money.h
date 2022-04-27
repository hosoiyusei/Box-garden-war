#pragma once
#include"../ItemBase.h"
#include"../../../Collision/Capsule.h"
#include"../../../Collision/Collision.h"

class Money :public ItemBase
{
private:

	DirectX::SimpleMath::Vector3 mPos;

	float mFloating;

	bool mUse;

	Capsule mCapsule;

	SphereCollision mSphereCollision;

public:

	//�R���X�g���N�^
	Money();
	//�f�X�g���N�^
	~Money();

	//������
	void Initialize()override;

	//�X�V
	void Update()override;

	//�`��
	void Draw()override;

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos) override;

	//Capsule�̓����蔻���Ԃ�
	const bool& CheckHitCapsule(const Capsule& capsule)override;

	void Use(const DirectX::SimpleMath::Vector3& pos)override {};

	const SphereCollision& GetCollision()override { return mSphereCollision; }

	const bool& GetUseFlag()override { return false; }

	void SetUseFlag()override {}
};