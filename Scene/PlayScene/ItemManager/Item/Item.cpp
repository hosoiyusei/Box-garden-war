#include"pch.h"
#include"Item.h"
#include"Pit/Pit.h"
#include"Mallet/Mallet.h"
#include"../../DoubleSpeed/DoubleSpeed.h"
#include"../../Player/Player.h"
#include"Money/Money.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Item::Item()
	:mActive(false)
	, mType(ITEM_TYPE::NONE)
	, mActiveTimer(0)
	, mpPlayer(nullptr)
	, mUseFlag(false)
{

}

//デストラクタ
Item::~Item()
{

}

//初期化
void Item::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//更新
void Item::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	for (int i = 0; i < static_cast<int>(mpDoubleSpeed.GetSpeed()); i++)
	{
		mActiveTimer++;
	}
	
	mpItemBase->Update();

	if (mUseFlag == true)
	{
		if (mActiveTimer > 300)
		{
			mActiveTimer = 0;
			mActive = false;
			mpItemBase->SetUseFlag();
			mUseFlag = false;
		}
	}
	else
	{
		if (mActiveTimer > 900)
		{
			mActiveTimer = 0;
			mActive = false;
			mpItemBase->SetUseFlag();
			mUseFlag = false;
		}
	}
}

//描画
void Item::Draw()
{
	mpItemBase->Draw();
}

//Spawn
void Item::Spawn(const Vector3& pos)
{
	mActive = true;
	mType = ITEM_TYPE::Money;
	SetItemType();
	mpItemBase->Spawn(pos);
	mActiveTimer = 0;
}

//Capsuleの当たり判定を返す
void Item::CheckHitCapsule(const Capsule& capsule)
{
	if (mpItemBase->CheckHitCapsule(capsule) == true)
	{
		mActive = false;
		mpPlayer->SetItem(mType);
	}
}


void Item::Use(const DirectX::SimpleMath::Vector3& pos, const ITEM_TYPE type)
{
	mType = type;
	SetItemType();
	mActive = true;
	mpItemBase->Use(pos);
	mActiveTimer = 0;

	mUseFlag = true;
}

const SphereCollision& Item::GetCollision()
{
	return mpItemBase->GetCollision();
}

const bool& Item::GetUseFlag()
{
	return mUseFlag;
}

/**********************************************************************************************************************************************************/

//アイテムの種類を設定
void Item::SetItemType()
{
	switch (mType)
	{
		case ITEM_TYPE::Pit: {mpItemBase = std::make_unique<Pit>();		break; }
		case ITEM_TYPE::Mallet: {mpItemBase = std::make_unique<Mallet>();	break; }
		case ITEM_TYPE::Money: {mpItemBase = std::make_unique<Money>();	break; }
		default:break;
	}
}