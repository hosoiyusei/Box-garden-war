#include"pch.h"
#include"Unit.h"

#include"Swordfighter/Swordfighter.h"

#include"Archer/Archer.h"

#include"Gunner/Gunner.h"

#include"Cannon/Cannon.h"

#include"Wizard/Wizard.h"

#include"Shogun/Shogun.h"

#include"../../EnemyManager/EnemyManager.h"
#include"../../BulletManager/BulletManager.h"
#include"../../EffectManager/EffectManager.h"
#include"../../DoubleSpeed/DoubleSpeed.h"

#include"Common/SoundManager/Adx2.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Unit::Unit()
	: mActive(false)
	, mPos()
	, mpEnemyManager(nullptr)
	, mpBulletManager(nullptr)
	, mpEffectManager(nullptr)
	, mType(UNIT_TYPE::NONE)
	, mLevel(UNIT_LEVEL::NONE)
{

}

//デストラクタ
Unit::~Unit()
{

}

//初期化
void Unit::Initialize(EnemyManager* pEnemyManager, BulletManager* pBulletManager, EffectManager* pEffectManager)
{
	//Enemyの管理者のポインタの取得
	mpEnemyManager = pEnemyManager;

	//弾の管理者のポインタの取得
	mpBulletManager = pBulletManager;

	//Effectの管理者のポインタの取得
	mpEffectManager = pEffectManager;
}

//更新
void Unit::Update()
{
	//Unitの種類ごとの更新
	mpUnitTypeBase->Update(mpEnemyManager, mpBulletManager, mpEffectManager, mPos);
}

//描画
void Unit::Draw()
{
	mpUnitTypeBase->Draw(mPos);
}

//Unitのエフェクトの描画
void Unit::EffectDraw()
{
	mpUnitTypeBase->EffectDraw(mPos, mpEffectManager);
}

//スポーン
void Unit::Spawn(const Vector3& pos, const UNIT_TYPE& type)
{
	//状態を設定
	SetType(type);

	mType = type;

	mLevel = UNIT_LEVEL::LEVEL_1;

	//座標の設定
	mPos = pos;
	mPos.y = 1.0f;

	//Unitの初期設定
	mpUnitTypeBase->Spawn(mPos);

	//アクティブにする
	mActive = true;

	//エフェクトの実行
	mpEffectManager->Play_2(Vector3(mPos.x, mPos.y - 0.3f, mPos.z), GetEffectColor(), 10, TEXTURE3D::SHADOW);

	mpUnitTypeBase->SetColor(GetEffectColor());
}

//Unitのレベルの設定
void Unit::SetUnitLevel(const UNIT_LEVEL& level)
{
	mLevel = level;
	mpUnitTypeBase->SetLevel(level);
	mpUnitTypeBase->SetColor(GetEffectColor());
}

//ユニットの除外
void Unit::Delete()
{
	mPos = Vector3(0.0f, 0.0f, 0.0f);
	mActive = false;
}

//強化中のフラグを返す
const bool Unit::GetReinforcementFlag(){return mpUnitTypeBase->GetReinforcementFlag();}

//当たり判定を返す
const SphereCollision Unit::GetCollision() { return mpUnitTypeBase->GetCollision(); }

//Unitのパワーアップ
void Unit::PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level) { mpUnitTypeBase->PowerUp(GetCollision, level); }

//パワーアップの解除
void Unit::Release_power_ups() { mpUnitTypeBase->Release_power_ups(); }

//攻撃力
const int Unit::GetPower() { return mpUnitTypeBase->GetPower(); }

/**********************************************************************************/

//状態を設定
void Unit::SetType(const UNIT_TYPE& type)
{
	mpUnitTypeBase.reset(false);

	//状態を設定
	switch (type)
	{
		case UNIT_TYPE::SWORDFIGHTER:	{mpUnitTypeBase = std::make_unique<Swordfighter>();	break; }
		case UNIT_TYPE::ARCHER:			{mpUnitTypeBase = std::make_unique<Archer>();		break; }
		case UNIT_TYPE::GUNNER:			{mpUnitTypeBase = std::make_unique<Gunner>();		break; }
		case UNIT_TYPE::CANNON:			{mpUnitTypeBase = std::make_unique<Cannon>();		break; }
		case UNIT_TYPE::SHOGUN:			{mpUnitTypeBase = std::make_unique<Shogun>();		break; }
		default:break;
	}
}

//エフェクトの色の設定
const Vector3 Unit::GetEffectColor()
{
	switch (mLevel)
	{
		case UNIT_LEVEL::LEVEL_1: {return Vector3(0.0f, 0.0f, 1.0f); break; }
		case UNIT_LEVEL::LEVEL_2: {return Vector3(0.0f, 1.0f, 0.0f); break; }
		case UNIT_LEVEL::LEVEL_3: {return Vector3(1.0f, 0.0f, 0.0f); break; }
		case UNIT_LEVEL::LEVEL_4: {return Vector3(1.0f, 1.0f, 0.0f); break; }
		case UNIT_LEVEL::LEVEL_5: {return Vector3(1.0f, 0.5f, 0.0f); break; }
		default:break;
	}

	return Vector3();
}