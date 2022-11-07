#pragma once
#include<SimpleMath.h>
#include"../../BulletManager/Bullet/BulletType.h"
#include"UnitLevel.h"
#include"../../Collision/Collision.h"

//�O���錾
class EnemyManager;
class BulletManager;
class EffectManager;

class UnitTypeBase
{
public:

	//�f�X�g���N�^
	virtual ~UnitTypeBase() = default;

	//�o�������Ƃ�
	virtual void Spawn(const DirectX::SimpleMath::Vector3& pos) = 0;

	//���x���̐ݒ�
	virtual void SetLevel(const UNIT_LEVEL& level) = 0;

	//�X�V
	virtual void Update(
		EnemyManager* pEnemyManager
		, BulletManager* pBulletManager
		, EffectManager* pEffectManager
		, const DirectX::SimpleMath::Vector3& pos) = 0;

	//�`��
	virtual void Draw(const DirectX::SimpleMath::Vector3& pos) = 0;

	//Unit�̃G�t�F�N�g�̕`��
	virtual void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager) = 0;

	//�������̃t���O��Ԃ�
	virtual const bool GetReinforcementFlag() = 0;

	//�����蔻���Ԃ�
	virtual const SphereCollision& GetCollision() = 0;

	//Unit�̃p���[�A�b�v
	virtual void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level) = 0;

	//�p���[�A�b�v�̉���
	virtual void Release_power_ups() = 0;

	virtual void SetColor(const DirectX::SimpleMath::Vector3& color) = 0;

	//�U����
	virtual const int GetPower() = 0;
};