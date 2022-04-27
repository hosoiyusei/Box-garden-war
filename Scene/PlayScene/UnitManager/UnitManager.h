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

class UnitManager
{
private:

	//���j�b�g�̔z��
	std::vector<std::unique_ptr<Unit>> mpUnit;

public:

	//�R���X�g���N�^
	UnitManager();
	//�f�X�g���N�^
	~UnitManager();

	//������
	void Initialize(
		EnemyManager* pEnemyManager
		, BulletManager* pBulletManager
	, EffectManager* pEffectManager);

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

	//���j�b�g�̍폜
	void Delete(const DirectX::SimpleMath::Vector3& pos);

	//�������̃t���O��Ԃ�
	const bool& GetReinforcementFlag(const DirectX::SimpleMath::Vector3& pos);

private:

	//Unit�̃p���[�A�b�v
	void UnitPowerUp(Unit* pUnit);

	//Unit�̎�ނ���tile�f�[�^��Ԃ�
	const TILE_DATA& UnitTypeData(const UNIT_TYPE& unitType);
};