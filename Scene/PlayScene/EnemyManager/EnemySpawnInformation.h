#pragma once

//�O���錾
class EnemyManager;

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

public:

	//�R���X�g���N�^
	EnemySpawnInformation();
	//�f�X�g���N�^
	~EnemySpawnInformation();

	//Enemy���X�|�[��
	void Spawn(EnemyManager* pEnemyManager);

	const bool& GetClear() { return mClear; }
};