#pragma once

class EnemyManager;

class CollisionManager final
{
private:

public:

	CollisionManager();
	~CollisionManager();

	void CheckHit(EnemyManager* pEnemyManager);
};