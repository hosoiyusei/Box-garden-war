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
class Tutorial;

class EnemyManager final
{
private:

	//�c��̓G�̐�
	int mNumber_of_remaining_Enemy;

	//Enemy�̔z��
	std::vector<std::unique_ptr<Enemy>> mpEnemy;

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
		, ItemManager* pItemManager
		, Tutorial* pTutorial);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�t�F�N�g�̕`��
	void EffectDraw();

	//Enemy�̓����蔻��
	void CheckHitEnemy();

	//Enemy�����邩�ǂ���
	const bool GetEnemyActive();

	//��ԋ߂�Enemy�̍��W
	const DirectX::SimpleMath::Vector3 ClosestPos(
		const DirectX::SimpleMath::Vector3& pos
		, const ENEMY_TYPE& type = ENEMY_TYPE::NONE);

	//��ԋ߂�Enemy�̎��
	const ENEMY_TYPE ClosestPosEnemyType(
		const DirectX::SimpleMath::Vector3& pos);

	//Enemy�̃X�|�[��
	void EnemySpawn(
		const int& startnum
		, const ENEMY_TYPE& type
		, const ENEMY_LEVEL& level);

	//�G�̎c��̐�
	const int GetNumber_of_remaining_Enemy() { return mNumber_of_remaining_Enemy; }

	//�G�̐������炷
	void SetNumber_of_remaining_Enemy() { mNumber_of_remaining_Enemy--; }
};