#pragma once
#include"../Collision/Capsule.h"
#include"Item/ItemType.h"

//�O���錾
class Item;
class Player;
class Enemy;

class ItemManager
{
private:

	std::vector<std::unique_ptr<Item>> mpItem;

public:

	//�R���X�g���N�^
	ItemManager();
	//�f�X�g���N�^
	~ItemManager();

	//������
	void Initialize(Player* pPlayer);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos);

	//Capsule�̓����蔻���Ԃ�
	void CheckHitCapsule(const Capsule& capsule);

	void Use(const DirectX::SimpleMath::Vector3& pos,const ITEM_TYPE& type);

	void CheckHitCollision(Enemy* pEnemy);
};