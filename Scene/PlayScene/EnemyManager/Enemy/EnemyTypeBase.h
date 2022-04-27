#pragma once
#include<SimpleMath.h>
#include"EnemyLevel.h"
#include"../../BulletManager/Bullet/BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//�O���錾
class EffectManager;
class Player;

class EnemyTypeBase
{
public:

	//�f�X�g���N�^
	virtual ~EnemyTypeBase() = default;

	//Enemy���o��������
	virtual void Spawn(EffectManager* pEffectManager,Player* pPlayer, const ENEMY_LEVEL& level) = 0;

	//�ړ��̑���
	virtual const float& Speed() = 0;

	//�G�t�F�N�g�̐F�̐ݒ�
	virtual const DirectX::SimpleMath::Vector3 GetEffectColor() = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw(const DirectX::SimpleMath::Vector3& pos, const float& angle) = 0;

	//�G�t�F�N�g�̕`��
	virtual void EffectDraw(const DirectX::SimpleMath::Vector3& pos) = 0;

	//�_���[�W���󂯂�
	virtual const bool& Damage(const DirectX::SimpleMath::Vector3& pos,const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level) = 0;

	//����ł��邩�ǂ���
	virtual const bool& Whetherdead() = 0;
};