#pragma once
#include<SimpleMath.h>
#include<vector>
#include"Unit/UnitType.h"
#include"../Player/StageTileData.h"
#include"Unit/UnitLevel.h"

//�O���錾
class Unit;
class EnemyManager;
class BulletManager;
class EffectManager;
class Player;

class UnitManager
{
private:

	//���j�b�g�̔z��
	std::vector<std::unique_ptr<Unit>> mpUnit;

	Player* mpPlayer;

public:

	//�R���X�g���N�^
	UnitManager();
	//�f�X�g���N�^
	~UnitManager();

	//������
	void Initialize(
		EnemyManager* pEnemyManager
		, BulletManager* pBulletManager
		, EffectManager* pEffectManager
		, Player* mpPlayer);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//Unit�̃G�t�F�N�g�̕`��
	void EffectDraw();

	//�X�|�[��
	const TILE_DATA Spawn(
		const DirectX::SimpleMath::Vector3& pos
		,const UNIT_TYPE& type);

	//Unit�̃��x���̐ݒ�
	void SetUnitLevel(
		const DirectX::SimpleMath::Vector3& pos
		,const UNIT_LEVEL& level);

	//�������̃t���O��Ԃ�
	const bool GetReinforcementFlag(const DirectX::SimpleMath::Vector3& pos);

	//���j�b�g�̍폜
	void Delete(const DirectX::SimpleMath::Vector3& pos);

	//�U����
	const int GetPower(const DirectX::SimpleMath::Vector3& pos);

	//Unit�̃p���[�A�b�v
	void UnitPowerUp(Unit* pUnit);

	//�p���[�A�b�v�̉���
	void Release_power_ups();

private:

	//Unit�̎�ނ���tile�f�[�^��Ԃ�
	const TILE_DATA UnitTypeData(const UNIT_TYPE& unitType);
};