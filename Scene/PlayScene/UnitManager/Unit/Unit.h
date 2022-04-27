#pragma once
#include<SimpleMath.h>
#include"UnitType.h"
#include"UnitLevel.h"
#include"../../Collision/Collision.h"

//�O���錾
class EnemyManager;
class BulletManager;
class UnitTypeBase;
class EffectManager;

class Unit
{
private:

	//���W�@��ԋ߂�Enemy�̍��W�@Enemy�Ƃ̋���
	DirectX::SimpleMath::Vector3 mPos;

	//�A�N�e�B�u���ǂ����̃t���O
	bool mActive;

	//Unit�̎��
	UNIT_TYPE mType;

	//Unit�̃��x��
	UNIT_LEVEL mLevel;

	//Enemy�̊Ǘ��҂̃|�C���^
	EnemyManager* mpEnemyManager;

	//�e�̊Ǘ��҂̃|�C���^
	BulletManager* mpBulletManager;

	//���j�b�g�̏��
	std::unique_ptr<UnitTypeBase> mpUnitTypeBase;

	//�G�t�F�N�g�̊Ǘ��҂̃|�C���^
	EffectManager* mpEffectManager;

public:

	//�R���X�g���N�^
	Unit();
	//�f�X�g���N�^
	~Unit();

	//������
	void Initialize(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//Unit�̃G�t�F�N�g�̕`��
	void EffectDraw();

	//�X�|�[��
	void Spawn(const DirectX::SimpleMath::Vector3& pos, const UNIT_TYPE& type);

	//Unit�̃��x���̐ݒ�
	void SetUnitLevel(const UNIT_LEVEL& level);

	//�A�N�e�B�u�t���O�̎擾
	const bool& GetActive() { return mActive; }

	//���j�b�g�̍��W���擾
	const DirectX::SimpleMath::Vector3& GetPos() { return mPos; }

	//Unit�̍폜
	void Delete();

	//�������̃t���O��Ԃ�
	const bool& GetReinforcementFlag();

	//�����蔻���Ԃ�
	const SphereCollision& GetCollision();

	//Unit�̎�ނ�Ԃ�
	const UNIT_TYPE& GetUnitType() { return mType; }

	//Unit�̃��x����Ԃ�
	const UNIT_LEVEL& GetUnitLevel() { return mLevel; }

	//Unit�̃p���[�A�b�v
	void PowerUp(const SphereCollision& GetCollision,const UNIT_LEVEL& level);

private:

	//��Ԃ̐ݒ�
	void SetType(const UNIT_TYPE& type);
};