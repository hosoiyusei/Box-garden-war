#pragma once
#include<SimpleMath.h>
#include"../../Collision/Collision.h"
#include"BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//�O���錾
class BulletTypeBase;
class EffectManager;

class Bullet
{
private:

	//�e�̍��W�@�^�[�Q�b�g�@�i�ޕ���
	DirectX::SimpleMath::Vector3
		mPos, mTargetPos, mVel, mInitialPos;

	//���[���h
	DirectX::SimpleMath::Matrix mWorld;

	//Actove�t���O
	bool mActive;

	BULLET_TYPE mType;

	//�e�̓����蔻��
	SphereCollision mCollision;

	//�e�̏��
	std::unique_ptr<BulletTypeBase> mpBulletType;

	//EffectManager�̃|�C���^
	EffectManager* mpEffectManager;

public:

	//�R���X�g���N�^
	Bullet();
	//�f�X�g���N�^
	~Bullet();

	//������
	void Initialize(EffectManager* pEffectManager);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�e�𔭎�
	void Shot(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& target
		, const BULLET_TYPE& type
		, const int& power
		, const UNIT_LEVEL& level
		, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f));

	//�e�����������Ƃ�
	const int& Hit();

	//�A�N�e�B�u�t���O�̎擾
	const bool& GetActive() { return mActive; }

	//�����蔻����擾
	const SphereCollision& GetCollision() { return mCollision; }

	const BULLET_TYPE& GetBulletType() { return mType; }

	const UNIT_LEVEL& GetLevel();

private:

	//��Ԃ̐ݒ�
	void SetState(const BULLET_TYPE& type);
};