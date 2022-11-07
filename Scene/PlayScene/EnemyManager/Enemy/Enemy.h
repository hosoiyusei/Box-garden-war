#pragma once
#include<SimpleMath.h>
#include"../../Collision/Collision.h"
#include"../../../Utility.h"
#include"../../AStar/AStar.h"
#include"../EnemyManager.h"
#include"EnemyLevel.h"
#include"../../BulletManager/Bullet/BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//�O���錾
class StageRead;
class EnemyTypeBase;
class EffectManager;
class Player;
class ItemManager;
class AStar;
class EnemyManager;

class Enemy
{
private:

	//Enemy�̓����蔻��
	SphereCollision mCollision;

	//Enemy�̍��W
	DirectX::SimpleMath::Vector3 mPos;

	//�ړI�n
	DirectX::SimpleMath::Vector3 mDestination;

	//�A�N�e�B�u�t���O
	bool mActive;

	//�����Ă邩�ǂ����̃t���O
	bool mDeath;

	//Enemy�̃X�s�[�h
	float mSpeed;

	//Enemy�̌���
	float mAngle;

	bool mGoal;

	float mRandom_height;

	float mRandom_rotation, mRandom_rotation2;
	
	float mFade_out;

	ENEMY_TYPE mEnemyType;

	//Enemy�̏��
	std::unique_ptr<EnemyTypeBase> mpEnemyTypeBase;

	//�G�t�F�N�g�̊Ǘ��҂̃|�C���^
	EffectManager* mpEffectManager;

	//Player�̃|�C���^
	Player* mpPlayer;

	//�A�C�e���̊Ǘ��҂̃|�C���^
	ItemManager* mpItemManager;

	std::unique_ptr<AStar> mpAStar;

	EnemyManager* mpEnemyManager;

public:

	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize(
		EnemyManager* pEnemyManager
		, StageRead* pStageRead
		, EffectManager* pEffectManager
		, Player* pPlayer
		, ItemManager* pItemManager);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�t�F�N�g�̕`��
	void EffectDraw();

	//Enemy���X�|�[��
	void Spawn(
		const int& startnum
		, const ENEMY_TYPE& type
		, const ENEMY_LEVEL& level);

	//Enemy�̍��W�̎擾
	const DirectX::SimpleMath::Vector3& GetPos() { return mPos; }

	//�����蔻���Ԃ�
	SphereCollision& GetCollision() { return mCollision; }

	//�_���[�W���󂯂�
	void Damage(const int& damage, const BULLET_TYPE& type,const UNIT_LEVEL level);

	//�A�N�e�B�u���ǂ����̃t���O
	const bool GetActive() { return mActive; }

	//���S���Ă��邩�ǂ����̃t���O
	const bool GetDeath() { return mDeath; }

	//Enemy�̎�ނ��擾
	const ENEMY_TYPE& GetEnemyType() { return mEnemyType; }

	const bool GetGoal() { return mGoal; }

private:

	//Enemy�̈ړ�
	void Move();

	//��Ԃ̐ݒ�
	void SetType(const ENEMY_TYPE& type);
};