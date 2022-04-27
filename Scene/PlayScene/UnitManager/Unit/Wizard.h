#pragma once
#include"../UnitTypeBase.h"
#include<SimpleMath.h>
#include"../UnitLevel.h"

class Wizard :public UnitTypeBase
{
private:

	//��̈ʒu
	DirectX::SimpleMath::Vector3
		mLeftHandPos
		, mRightHandPos;

	//���̉�]
	float mSwordAngle;

	//�U�����[�V�����̃^�C�}�[
	int mAttackMoveTimer;

	//Unit�̃��x��
	UNIT_LEVEL mLevel;

public:

	//�R���X�g���N�^
	Wizard();
	//�f�X�g���N�^
	~Wizard();

	//���G����
	const float& SetLen()override { return 1.7f; }

	//�e�̔��ˊԊu
	const int& ShotInterval()override { return 60; }

	//���˂���e�̎��
	const BULLET_TYPE& SetType() override { return BULLET_TYPE::SLASHING; }

	//�G�t�F�N�g�̐F�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetEffectColor()override;

	//���x���̐ݒ�
	void SetLevel(const UNIT_LEVEL& level)override;

	//�U���͂̐ݒ�
	const int GetOffensivePower()override;

	//�X�V
	void Update(bool& attackFlag)override;

	//�`��
	void Draw(
		const float& angle
		, const DirectX::SimpleMath::Vector3& pos)override;
};