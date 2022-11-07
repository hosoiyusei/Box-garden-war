#pragma once
#include"../ItemBase.h"
#include"../../../Collision/Capsule.h"
#include"../../../Collision/Collision.h"

class Mallet :public ItemBase
{
private:

	DirectX::SimpleMath::Vector3 mPos;

	float mFloating;

	bool mUse;

	Capsule mCapsule;

	SphereCollision mSphereCollision;

public:

	//�R���X�g���N�^
	Mallet();
	//�f�X�g���N�^
	~Mallet();

	//������
	void Initialize()override;

	//�X�V
	void Update()override;

	//�`��
	void Draw()override;

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos) override;

	//Capsule�̓����蔻���Ԃ�
	const bool CheckHitCapsule(const Capsule& capsule)override;

	void Use(const DirectX::SimpleMath::Vector3& pos)override { UNREFERENCED_PARAMETER(pos); };

	const SphereCollision& GetCollision()override {return mSphereCollision;}

	const bool GetUseFlag()override { return false; }

	void SetUseFlag()override {}
};