#pragma once
#include"../../Collision/Capsule.h"
#include"../../Collision/Collision.h"

class ItemBase
{
public:

	//�f�X�g���N�^
	virtual ~ItemBase() = default;

	//������
	virtual void Initialize() = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;

	//Spawn
	virtual void Spawn(const DirectX::SimpleMath::Vector3& pos) = 0;

	//Capsule�̓����蔻���Ԃ�
	virtual const bool&  CheckHitCapsule(const Capsule& capsule) = 0;

	virtual void Use(const DirectX::SimpleMath::Vector3& pos) = 0;

	virtual const SphereCollision& GetCollision() = 0;

	virtual const bool& GetUseFlag() = 0;

	virtual void SetUseFlag() = 0;
};