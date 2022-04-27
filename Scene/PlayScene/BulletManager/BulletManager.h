#pragma once
#include<vector>
#include<SimpleMath.h>
#include"../Collision/Collision.h"
#include"Bullet/BulletType.h"
#include"../UnitManager/Unit/UnitLevel.h"

//前方宣言
class Enemy;
class EffectManager;

//前方宣言
class Bullet;

class BulletManager
{
private:

	//Bulletの配列
	std::vector<std::unique_ptr<Bullet>> mpBullet;

public:

	//コンストラクタ
	BulletManager();
	//デストラクタ
	~BulletManager();

	//初期化
	void Initialize(EffectManager* pEffectManager);

	//更新
	void Update();

	//描画
	void Draw();

	//弾を発射する
	void Shot(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& target
		, const BULLET_TYPE& type
		, const int& power
		, const UNIT_LEVEL& level
		, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f));

	//弾の当たり判定
	bool CheckHitCollision(
		Enemy* pEnemy);
};