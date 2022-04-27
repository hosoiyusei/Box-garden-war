#include"pch.h"
#include"CollisionManager.h"

#include"../EnemyManager/EnemyManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::CheckHit(EnemyManager* pEnemyManager)
{
	pEnemyManager->CheckHitEnemy();
}