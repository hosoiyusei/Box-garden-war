#pragma once
#include"EnemyTypeBase.h"
#include"EnemyLevel.h"
#include"EnemyType.h"

class ArmoredSoldier :public EnemyTypeBase
{
private:

	//���x��
	ENEMY_LEVEL mLevel;

	DirectX::SimpleMath::Vector3 mPos;

	//��̈ʒu
	DirectX::SimpleMath::Vector3 mRightHandPos
		, mLeftHandPos;

	//���̌���
	float mSpearAngle;

	//��̐U��
	float mHandAngle;

	//Enemy��HP
	int mHP;

	//�ݑ���Ԃ̃^�C�}�[
	int mSlowFootTimer;

	//�R�Ď���
	int mCombustionTimer;

	//Enemy�̑���
	float mSpeed;

	//Enemy�̏��
	Enemy_Status mEnemy_Status, mEnemy_Status2;

	//�G�t�F�N�g�̃|�C���^
	EffectManager* mpEffectManager;

	//�v���C���[�̃|�C���^
	Player* mpPlayer;

	//���b�_
	bool mArmor_point;

public:

	//�R���X�g���N�^
	ArmoredSoldier();
	//�f�X�g���N�^
	~ArmoredSoldier();

	//Enemy���o��������
	void Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)override;

	//�ړ��̑���
	const float Speed()override { return mSpeed; }

	//�G�t�F�N�g�̐F�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetEffectColor()override;

	//�X�V
	void Update()override;

	//�`��
	void Draw(const DirectX::SimpleMath::Vector3& pos, const float& angle, const float& fade = 1.0f)override;

	//�G�t�F�N�g�̕`��
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos)override;

	//�_���[�W���󂯂�
	const bool Damage(const DirectX::SimpleMath::Vector3& pos, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)override;

	//����ł��邩�ǂ���
	const bool Whetherdead();

private:

	//�ݑ����
	void SlowFoot();

	//�R�ď��
	void Combustion();

	//HP�̐ݒ�
	const int SetHP();

	//��
	const int GetMoney();

	//��Ԃ��Ƃ̏���
	void Processingofeachstate();

	//��Ԃ��Ƃ̏���
	void Processingofeachstate2();
};