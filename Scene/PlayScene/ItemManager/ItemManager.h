#pragma once
#include"../Collision/Capsule.h"
#include"Item/ItemType.h"

//前方宣言
class Item;
class Player;
class Enemy;

class ItemManager
{
private:

	std::vector<std::unique_ptr<Item>> mpItem;

public:

	//コンストラクタ
	ItemManager();
	//デストラクタ
	~ItemManager();

	//初期化
	void Initialize(Player* pPlayer);

	//更新
	void Update();

	//描画
	void Draw();

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos);

	//Capsuleの当たり判定を返す
	void CheckHitCapsule(const Capsule& capsule);

	void Use(const DirectX::SimpleMath::Vector3& pos,const ITEM_TYPE& type);

	void CheckHitCollision(Enemy* pEnemy);
};