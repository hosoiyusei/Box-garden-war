#pragma once

//�O���錾
class EnemyManager;
class Player;
class Tutorial;

class EnemySpawnInformation
{
private:

	//�X�|�[�������鎞��
	int mEnemySpawnTimer;

	//�o���Ԋu
	int mSpawnInterval;

	//�X�|�[����������
	int mSpawnCount;

	//�N���A�t���O
	bool mClear;

	Player* mpPlayer;

	Tutorial* mpTutorial;

public:

	//�R���X�g���N�^
	EnemySpawnInformation();
	//�f�X�g���N�^
	~EnemySpawnInformation() = default;

	//������
	void Initialize(Player* pPlayer, Tutorial* pTutorial);

	//Enemy���X�|�[��
	void Spawn(EnemyManager* pEnemyManager);

	const bool GetClear() { return mClear; }

private:

	//�`���[�g���A���p�̃X�|�[��
	void Spawn_for_tutorial(EnemyManager* pEnemyManager);
};