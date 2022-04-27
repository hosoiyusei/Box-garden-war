#include"pch.h"
#include"EnemyManager.h"

#include"Enemy/Enemy.h"
#include"../BulletManager/BulletManager.h"
#include"EnemySpawnInformation.h"
#include"../Player/Player.h"
#include"../ItemManager/ItemManager.h"

//Enemy����鐔
const int ENEMY_NUM(500);

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
EnemyManager::EnemyManager()
	: mpEnemy()
	, mpBulletManager(nullptr)
	, mEnemyActive(false)
	, mpEnemyManager(nullptr)
	, mpPlayer(nullptr)
{

}

//�f�X�g���N�^
EnemyManager::~EnemyManager()
{

}

//������
void EnemyManager::Initialize(
	StageRead* pStageRead
	, BulletManager* pBulletManager
	, EffectManager* pEffectManager
	, EnemyManager* pEnemyManager
	, Player* pPlayer
, ItemManager* pItemManager)
{
	//�e�̊Ǘ��҂̃|�C���^�̎擾
	mpBulletManager = pBulletManager;

	//�X�|�[�����̃|�C���^�̍쐬
	mpEnemySpawnInformation = std::make_unique<EnemySpawnInformation>();

	//Enemy�̊Ǘ��҂̃|�C���^�̎擾
	mpEnemyManager = pEnemyManager;

	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mpEnemy.push_back(std::make_unique<Enemy>());
		mpEnemy[i]->Initialize(
			pStageRead
			, pEffectManager
			, pPlayer
			, pItemManager);
	}
}

//�X�V
void EnemyManager::Update()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//�A�N�e�B�u��������X�V
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->Update();
		}
	}

	mpEnemySpawnInformation->Spawn(mpEnemyManager);

	mpPlayer->SetClear(mpEnemySpawnInformation->GetClear());
}

//�`��
void EnemyManager::Draw()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//�A�N�e�B�u��������`��
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->Draw();
		}
	}
}

//�G�t�F�N�g�̕`��
void EnemyManager::EffectDraw()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//�A�N�e�B�u��������`��
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->EffectDraw();
		}
	}
}

//Enemy�̓����蔻��
void EnemyManager::CheckHitEnemy()
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true)
		{
			mpBulletManager->CheckHitCollision(
				mpEnemy[i].get());

			mpItemManager->CheckHitCollision(mpEnemy[i].get());
		}
	}
}

//��ԋ߂�Enemy�̍��W
const DirectX::SimpleMath::Vector3& EnemyManager::ClosestPos(const DirectX::SimpleMath::Vector3& pos)
{
	DirectX::SimpleMath::Vector3 len1, len2, target;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	mEnemyActive = false;

	for (int i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true)
		{
			mEnemyActive = true;

			//Enemy�Ƃ̋���
			len1 = pos - mpEnemy[i]->GetPos();
			if (len2.Length() > len1.Length() ||
				len2 == Vector3(0.0f, 0.0f, 0.0f))
			{
				len2 = len1;
				//��ԋ߂�Enemy�̍��W���擾
	 			target = mpEnemy[i]->GetPos();
			}
		}
	}

	//��ԋ߂�Enemy�̍��W
	return target;
}

//��ԋ߂�Enemy�̎��
const ENEMY_TYPE& EnemyManager::ClosestPosEnemyType(const DirectX::SimpleMath::Vector3& pos)
{
	DirectX::SimpleMath::Vector3 len1, len2;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	//Enemy�̎��
	ENEMY_TYPE target;

	mEnemyActive = false;

	for (int i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true)
		{
			mEnemyActive = true;

			//Enemy�Ƃ̋���
			len1 = pos - mpEnemy[i]->GetPos();
			if (len2.Length() > len1.Length() ||
				len2 == Vector3(0.0f, 0.0f, 0.0f))
			{
				len2 = len1;
				//��ԋ߂�Enemy�̍��W���擾
				target = mpEnemy[i]->GetEnemyType();
			}
		}
	}

	//��ԋ߂�Enemy�̍��W
	return target;
}

//Enemy���Ăяo��
void EnemyManager::EnemySpawn(
	const int& startnum
	, const ENEMY_TYPE& type
	, const ENEMY_LEVEL& level)
{
	for (int i = 0; i < mpEnemy.size(); i++)
	{
		//Enemy���g���Ă��Ȃ�������X�|�[��
		if (mpEnemy[i]->GetActive() == false &&
			mpEnemy[i]->GetDeath() == false)
		{
			mpEnemy[i]->Spawn(startnum, type, level);
			break;
		}
	}
}