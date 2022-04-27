#pragma once
#include"../UnitTypeBase.h"
#include"../UnitLevel.h"

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

	//Unit�̃��x��
	UNIT_LEVEL mLevel;

	//�����蔻��
	SphereCollision mSphereCollision;

public:

	//�R���X�g���N�^
	Shogun();
	//�f�X�g���N�^
	~Shogun();

	//�o�������Ƃ�
	void Spawn(const DirectX::SimpleMath::Vector3& pos)override;

	//�G�t�F�N�g�̐F�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetEffectColor()override;

	//���x���̐ݒ�
	void SetLevel(const UNIT_LEVEL& mlevel)override;

	//�X�V
	void Update(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager, const DirectX::SimpleMath::Vector3& pos)override;

	//�`��
	void Draw(const DirectX::SimpleMath::Vector3& pos)override;

	//Unit�̃G�t�F�N�g�̕`��
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)override;

	//�������̃t���O��Ԃ�
	const bool& GetReinforcementFlag()override { return mReinforcementFlag; }

	//�����蔻���Ԃ�
	const SphereCollision& GetCollision()override { return mSphereCollision; }

	//Unit�̃p���[�A�b�v
	void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)override {};

private:

	//���x���A�b�v�ɂ����鎞��
	const int& LevelUpTime();

	//�U���͂̐ݒ�
	const int GetOffensivePower();
};