#pragma once

//前方宣言
class EnemyManager;

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

public:

	//コンストラクタ
	EnemySpawnInformation();
	//デストラクタ
	~EnemySpawnInformation();

	//Enemyをスポーン
	void Spawn(EnemyManager* pEnemyManager);

	const bool& GetClear() { return mClear; }
};