#pragma once
#include"../../Collision/Capsule.h"
#include"ItemType.h"
#include"../../Collision/Collision.h"

//�O���錾
class ItemBase;
class Player;

class Item
{
private:

	//Active�t���O
	bool mActive;

	int mActiveTimer;

	bool mUseFlag;

	//�A�C�e���̎��
	ITEM_TYPE mType;

	std::unique_ptr<ItemBase> mpItemBase;

	Player* mpPlayer;

public:

	//�R���X�g���N�^
	Item();
	//�f�X�g���N�^
	~Item();

	//������
	void Initialize(Player* pPlayer);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//Spawn
	void Spawn(const DirectX::SimpleMath::Vector3& pos);

	//Capsule�̓����蔻���Ԃ�
	void  CheckHitCapsule(const Capsule& capsule);

	//Active�t���O��Ԃ�
	const bool& GetActive() { return mActive; }

	//Itemn�̎�ނ�Ԃ�
	const ITEM_TYPE& GetType() { return mType; }

	void Use(const DirectX::SimpleMath::Vector3& pos, const ITEM_TYPE type);

	const SphereCollision& GetCollision();

	const bool& GetUseFlag();

private:

	//�A�C�e���̎�ނ�ݒ�
	void SetItemType();
};