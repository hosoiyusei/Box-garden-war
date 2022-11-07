#pragma once
#include"../UnitTypeBase.h"
#include"../UnitLevel.h"
#include"Shogun_Param.h"

class Shogun :public UnitTypeBase
{
private:

	//��̈ʒu
	DirectX::SimpleMath::Vector3 mLeftHandPos, mRightHandPos;

	//Unit�̌���
	float mAngle;

	//�G���߂��ɂ��邩�ǂ����̃t���O
	bool mEnemyApproachingFlag;

	//�������̃t���O
	bool mReinforcementFlag;

	//�����̃^�C�}�[
	int mReinforcementTimer;

	//�G�t�F�N�g�𔭐�������^�C�}�[
	int mEffectTimer;

	//�ꎞ�񎦒��̋����̃^�C�}�[
	int mEnhanced_timer_during_pause;

	//�ʏ�A�j���[�V�����^�C�}�[
	float mNormal_animation_timer;

	//Unit�̃��x��
	UNIT_LEVEL mLevel;

	//�����蔻��
	SphereCollision mSphereCollision;

	DirectX::SimpleMath::Vector3 mColor;

	Shogun_Param mParam;

public:

	//�R���X�g���N�^
	Shogun();
	//�f�X�g���N�^
	~Shogun();

	//�o�������Ƃ�
	void Spawn(const DirectX::SimpleMath::Vector3& pos)override;

	//���x���̐ݒ�
	void SetLevel(const UNIT_LEVEL& mlevel)override;

	//�X�V
	void Update(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager, const DirectX::SimpleMath::Vector3& pos)override;

	//�`��
	void Draw(const DirectX::SimpleMath::Vector3& pos)override;

	//Unit�̃G�t�F�N�g�̕`��
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)override;

	//�������̃t���O��Ԃ�
	const bool GetReinforcementFlag()override { return mReinforcementFlag; }

	//�����蔻���Ԃ�
	const SphereCollision& GetCollision()override { return mSphereCollision; }

	//Unit�̃p���[�A�b�v
	void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)override {
		UNREFERENCED_PARAMETER(GetCollision); UNREFERENCED_PARAMETER(level);
	};

	//�p���[�A�b�v�̉���
	void Release_power_ups()override {}

	//�F�̐ݒ�
	void SetColor(const DirectX::SimpleMath::Vector3& color)override { mColor = color; }

	//�U����
	const int GetPower()override { return 0; }

private:

	//���x���A�b�v�ɂ����鎞��
	const int LevelUpTime();

	//�U���͂̐ݒ�
	const int GetOffensivePower();

	void Normal_animation();
};