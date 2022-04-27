#pragma once
#include<vector>
#include"Enemy/EnemyType.h"
#include"Enemy/EnemyLevel.h"

//�O���錾
class Enemy;
class StageRead;
class BulletManager;
class EnemySpawnInformation;
class EffectManager;
class Player;
class ItemManager;

class EnemyManager final
{
private:

	//Enemy�̔z��
	std::vector<std::unique_ptr<Enemy>> mpEnemy;

	//Enemy�����邩�ǂ���
	bool mEnemyActive;

	//�e�̊Ǘ��҂̃|�C���^
	BulletManager* mpBulletManager;

	//�X�|�[�����̃|�C���^
	std::unique_ptr<EnemySpawnInformation> mpEnemySpawnInformation;

	//Enemy�̊Ǘ��҂̃|�C���^
	EnemyManager* mpEnemyManager;

	//Player�̃|�C���^
	Player* mpPlayer;

	ItemManager* mpItemManager;

public:

	//�R���X�g���N�^
	EnemyManager();
	//�f�X�g���N�^
	~EnemyManager();

	//������
	void Initialize(
		StageRead* pStageRead
		, BulletManager* pBulletManager
		, EffectManager* pEffectManager
		, EnemyManager* pEnemyManager
		, Player* pPlayer
		, ItemManager* pItemManager);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�t�F�N�g�̕`��
	void EffectDraw();

	//Enemy�̓����蔻��
	void CheckHitEnemy();

	//Enemy�����邩�ǂ���
	const bool& GetEnemyActive() { return mEnemyActive; }

	//��ԋ߂�Enemy�̍��W
	const DirectX::SimpleMath::Vector3& ClosestPos(
		const DirectX::SimpleMath::Vector3& pos);

	//��ԋ߂�Enemy�̎��
	const ENEMY_TYPE& ClosestPosEnemyType(
		const DirectX::SimpleMath::Vector3& pos);

	//Enemy�̃X�|�[��
	void EnemySpawn(
		const int& startnum
		, const ENEMY_TYPE& type
		, const ENEMY_LEVEL& level);
};