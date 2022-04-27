#pragma once
#include"EnemyTypeBase.h"
#include"EnemyLevel.h"

class Boss :public EnemyTypeBase
{
private:

	//���x��
	ENEMY_LEVEL mLevel;

	//Enemy��HP
	int mHP;

	//�ݑ���Ԃ̃t���O
	bool mSlowFootFlag;

	//�ݑ���Ԃ̃^�C�}�[
	int mSlowFootTimer;

	//Enemy�̑���
	float mSpeed;

	//�G�t�F�N�g�̃|�C���^
	EffectManager* mpEffectManager;

	//�v���C���[�̃|�C���^
	Player* mpPlayer;

public:

	//�R���X�g���N�^
	Boss();
	//�f�X�g���N�^
	~Boss();

	//Enemy���o��������
	void Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)override;

	//�ړ��̑���
	const float& Speed()override { return mSpeed; }

	//�G�t�F�N�g�̐F�̐ݒ�
	const DirectX::SimpleMath::Vector3 GetEffectColor()override { return DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f); }

	//�X�V
	void Update()override;

	//�`��
	void Draw(const DirectX::SimpleMath::Vector3& pos, const float& angle)override;

	//�G�t�F�N�g�̕`��
	void EffectDraw(const DirectX::SimpleMath::Vector3& pos)override;

	//�_���[�W���󂯂�
	const bool& Damage(const DirectX::SimpleMath::Vector3& pos, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)override;

	//����ł��邩�ǂ���
	const bool& Whetherdead() { return false; };

private:

	//�ݑ����
	void SlowFoot();

	//HP�̐ݒ�
	const int& SetHP();

	//��
	const int& GetMoney();
};