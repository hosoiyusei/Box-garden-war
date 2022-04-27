#pragma once
#include"../../Collision/Capsule.h"
#include"ItemType.h"
#include"../../Collision/Collision.h"

//前方宣言
class ItemBase;
class Player;

class Item
{
private:

	//Activeフラグ
	bool mActive;

	int mActiveTimer;

	bool mUseFlag;

	//アイテムの種類
	ITEM_TYPE mType;

	std::unique_ptr<ItemBase> mpItemBase;

	Player* mpPlayer;

public:

	//コンストラクタ
	Item();
	//デストラクタ
	~Item();

	//初期化
	void Initialize(Player* pPlayer);

	//更新
	void Update();

	//描画
	void Draw();

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos);

	//Capsuleの当たり判定を返す
	void  CheckHitCapsule(const Capsule& capsule);

	//Activeフラグを返す
	const bool& GetActive() { return mActive; }

	//Itemnの種類を返す
	const ITEM_TYPE& GetType() { return mType; }

	void Use(const DirectX::SimpleMath::Vector3& pos, const ITEM_TYPE type);

	const SphereCollision& GetCollision();

	const bool& GetUseFlag();

private:

	//アイテムの種類を設定
	void SetItemType();
};