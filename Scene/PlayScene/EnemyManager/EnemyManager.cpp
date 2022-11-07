#include"pch.h"
#include"EnemyManager.h"

#include"Enemy/Enemy.h"
#include"../BulletManager/BulletManager.h"
#include"EnemySpawnInformation.h"
#include"../Player/Player.h"
#include"../ItemManager/ItemManager.h"
#include"../Stage/StageNum.h"

//Enemy����鐔
const int ENEMY_NUM(170);

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
EnemyManager::EnemyManager()
	: mpEnemy()
	, mpBulletManager(nullptr)
	, mpEnemyManager(nullptr)
	, mpPlayer(nullptr)
	, mpItemManager(nullptr)
	, mNumber_of_remaining_Enemy(0)
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
	, ItemManager* pItemManager
	, Tutorial* pTutorial)
{
	//�e�̊Ǘ��҂̃|�C���^�̎擾
	mpBulletManager = pBulletManager;

	//�X�|�[�����̃|�C���^�̍쐬
	mpEnemySpawnInformation = std::make_unique<EnemySpawnInformation>();

	mpEnemySpawnInformation->Initialize(pPlayer, pTutorial);

	//Enemy�̊Ǘ��҂̃|�C���^�̎擾
	mpEnemyManager = pEnemyManager;

	mpPlayer = pPlayer;

	mpItemManager = pItemManager;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mpEnemy.push_back(std::make_unique<Enemy>());
		mpEnemy[i]->Initialize(
			pEnemyManager
			, pStageRead
			, pEffectManager
			, pPlayer
			, pItemManager);
	}

	StageNum& setstage = StageNum::GetInstance();

	if (setstage.GetStageNum() != STAGE_NUM::TUTORIAL)
	{
		mNumber_of_remaining_Enemy = 170;
	}
	else
	{
		mNumber_of_remaining_Enemy = 50;
	}
}

//�X�V
void EnemyManager::Update()
{
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		//�A�N�e�B�u��������X�V
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true ||
			mpEnemy[i]->GetDeath() == true && mpEnemy[i]->GetGoal() != true)
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
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		//�A�N�e�B�u��������`��
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetGoal() != true||
			mpEnemy[i]->GetDeath() == true && mpEnemy[i]->GetGoal() != true)
		{
			mpEnemy[i]->Draw();
		}
	}
}

//�G�t�F�N�g�̕`��
void EnemyManager::EffectDraw()
{
	for (size_t i = 0; i < mpEnemy.size(); i++)
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
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true &&
			mpEnemy[i]->GetDeath() == false)
		{
			mpBulletManager->CheckHitCollision(mpEnemy[i].get());

			mpItemManager->CheckHitCollision(mpEnemy[i].get());
		}
	}
}

//Enemy�����邩�ǂ���
const bool EnemyManager::GetEnemyActive()
{
	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetDeath() == false)
		{
			return true;
		}
	}

	return false;
}

//��ԋ߂�Enemy�̍��W
const Vector3 EnemyManager::ClosestPos(const Vector3& pos
	, const ENEMY_TYPE& type)
{
	Vector3 len1, len2, target;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	target = Vector3(1000.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetDeath() == false)
		{
			if (mpEnemy[i]->GetEnemyType() != type)
			{
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
	}

	//��ԋ߂�Enemy�̍��W
	return target;
}

//��ԋ߂�Enemy�̎��
const ENEMY_TYPE EnemyManager::ClosestPosEnemyType(const Vector3& pos)
{
	Vector3 len1, len2;
	len2 = Vector3(0.0f, 0.0f, 0.0f);

	//Enemy�̎��
	ENEMY_TYPE target = ENEMY_TYPE::NONE;

	for (size_t i = 0; i < mpEnemy.size(); i++)
	{
		if (mpEnemy[i]->GetActive() == true && mpEnemy[i]->GetDeath() == false)
		{
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
	for (size_t i = 0; i < mpEnemy.size(); i++)
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