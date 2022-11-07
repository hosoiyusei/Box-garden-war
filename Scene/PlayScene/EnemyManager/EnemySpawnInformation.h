#pragma once

//前方宣言
class EnemyManager;
class Player;
class Tutorial;

class EnemySpawnInformation
{
private:

	//スポーンさせる時間
	int mEnemySpawnTimer;

	//出現間隔
	int mSpawnInterval;

	//スポーンさせた数
	int mSpawnCount;

	//クリアフラグ
	bool mClear;

	Player* mpPlayer;

	Tutorial* mpTutorial;

public:

	//コンストラクタ
	EnemySpawnInformation();
	//デストラクタ
	~EnemySpawnInformation() = default;

	//初期化
	void Initialize(Player* pPlayer, Tutorial* pTutorial);

	//Enemyをスポーン
	void Spawn(EnemyManager* pEnemyManager);

	const bool GetClear() { return mClear; }

private:

	//チュートリアル用のスポーン
	void Spawn_for_tutorial(EnemyManager* pEnemyManager);
};