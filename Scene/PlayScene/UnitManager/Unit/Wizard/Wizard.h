#pragma once
#include"../UnitTypeBase.h"
#include<SimpleMath.h>
#include"../UnitLevel.h"

//class Wizard :public UnitTypeBase
//{
//private:
//
//	//��̈ʒu
//	DirectX::SimpleMath::Vector3 mLeftHandPos, mRightHandPos;
//
//	//��̉�]
//	float mWandAngle;
//
//	float mWandLight;
//
//	//�U�����[�V�����̃^�C�}�[
//	int mAttackMoveTimer;
//
//	//Unit�̌���
//	float mAngle;
//
//	//�U���Ԋu
//	int mAttackTimer;
//
//	//�U���\���ǂ����̃t���O
//	bool mAttackFlag;
//
//	//�G���߂��ɂ��邩�ǂ����̃t���O
//	bool mEnemyApproachingFlag;
//
//	//�������̃t���O
//	bool mReinforcementFlag;
//
//	//�����̃^�C�}�[
//	int mReinforcementTimer;
//
//	//�p���[�A�b�v�̃t���O
//	bool mPowerUpFlag;
//
//	//�G�t�F�N�g�𔭐�������^�C�}�[
//	int mEffectTimer;
//
//	//�p���[�A�b�v�̃��x��
//	UNIT_LEVEL mPowerUpLevel;
//
//	//Unit�̃��x��
//	UNIT_LEVEL mLevel;
//
//	//�����蔻��
//	SphereCollision mSphereCollision;
//
//public:
//
//	//�R���X�g���N�^
//	Wizard();
//	//�f�X�g���N�^
//	~Wizard();
//
//	//�o�������Ƃ�
//	void Spawn(const DirectX::SimpleMath::Vector3& pos)override;
//
//	//�G�t�F�N�g�̐F�̐ݒ�
//	const DirectX::SimpleMath::Vector3 GetEffectColor()override;
//
//	//���x���̐ݒ�
//	void SetLevel(const UNIT_LEVEL& level)override;
//
//	//�X�V
//	void Update(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager, const DirectX::SimpleMath::Vector3& pos)override;
//
//	//�`��
//	void Draw(const DirectX::SimpleMath::Vector3& pos)override;
//
//	//Unit�̃G�t�F�N�g�̕`��
//	void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager)override;
//
//	//�������̃t���O��Ԃ�
//	const bool& GetReinforcementFlag()override { return mReinforcementFlag; }
//
//	//�����蔻���Ԃ�
//	const SphereCollision& GetCollision()override { return mSphereCollision; }
//
//	//Unit�̃p���[�A�b�v
//	void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level)override;
//
//private:
//
//	//�U��
//	void Attack(EnemyManager* pEnemyManager, BulletManager* pBulletManager, const DirectX::SimpleMath::Vector3& pos);
//
//	//�U������Ƃ��̃A�j���[�V����
//	void AttackAnimation();
//
//	//���x���A�b�v�ɂ����鎞��
//	const int& LevelUpTime();
//
//	//�U���͂̐ݒ�
//	const int GetOffensivePower();
//
//	//�p���[�A�b�v���郌�x��
//	const int& PowerUpLevel();
//};