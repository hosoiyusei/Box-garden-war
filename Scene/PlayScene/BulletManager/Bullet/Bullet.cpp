#include"pch.h"
#include"Bullet.h"
#include"../../EffectManager/EffectManager.h"

#include"Slashing.h"
#include"Shoot.h"
#include"Shooting.h"
#include"CannonBall.h"
#include"Magic.h"
#include"../../DoubleSpeed/DoubleSpeed.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Bullet::Bullet()
	:mActive(false)
	, mWorld()
	, mPos()
	, mTargetPos()
	, mCollision()
	, mVel()
	, mInitialPos()
	, mpEffectManager(nullptr)
	, mType(BULLET_TYPE::NONE)
{

}

//デストラクタ
Bullet::~Bullet()
{

}

//初期化
void Bullet::Initialize(EffectManager* pEffectManager)
{
	//ポインタの取得
	mpEffectManager = pEffectManager;

	//当たアリ判定の大きさを設定
	mCollision.mRadius = 0.2f;
}

//更新
void Bullet::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	//弾の移動
	mPos += mVel * mpDoubleSpeed.GetSpeed();

	Vector3 len = mPos - mInitialPos;
	
	//弾が範囲外に出たら削除
	if (len.Length() >= mpBulletType->GetLen())
	{
		mActive = false;
	}

	//弾の種類による更新
	mpBulletType->Update(mpEffectManager);
	
	//当たり判定の座標を設定
	mCollision.mPos = mPos;
}

//描画
void Bullet::Draw()
{
	mpBulletType->Draw(mPos);
}

//弾を発射
void Bullet::Shot(
	const Vector3& pos
	, const Vector3& target
	, const BULLET_TYPE& type
	, const int& power
	, const UNIT_LEVEL& level
	, DirectX::SimpleMath::Color color)
{
	//状態を設定
	SetState(type);

	mPos = pos;

	mCollision.mPos = pos;

	mInitialPos = pos;

	float angle = atan2f(
		target.z - mPos.z, target.x - mPos.x);

	//発射
	mpBulletType->Shot(power, angle, color,level);

	mVel.z = static_cast<float>(mpBulletType->GetSpeed() * sin(angle));
	mVel.x = static_cast<float>(mpBulletType->GetSpeed() * cos(angle));

	mActive = true;
}

const int Bullet::Hit()
{
	mActive = false;

	if (mpBulletType->GetType() == BULLET_TYPE::CANNONBALL)
	{
		mpEffectManager->Play(mPos, Vector3(1.0f, 0.0f, 0.0f), 10, TEXTURE3D::SHADOW);
		mpEffectManager->Play(mPos, Vector3(1.0f, 0.5f, 0.0f), 10, TEXTURE3D::SHADOW, 0.003f, 0.15f);
		mpEffectManager->Play(mPos, Vector3(0.5f, 0.5f, 0.5f), 20, TEXTURE3D::SHADOW, 0.003f, 0.1f);
	}


	return mpBulletType->GetOffensivePower();
}

const UNIT_LEVEL Bullet::GetLevel()
{
	return mpBulletType->GetLevel();
}

/****************************************************************************/

void Bullet::SetState(const BULLET_TYPE& type)
{
	mpBulletType.reset(nullptr);

	switch (type)
	{
		case BULLET_TYPE::SLASHING:
		{
			mpBulletType = std::make_unique<Slashing>();
			mType = BULLET_TYPE::SLASHING;
			break;
		}
		case BULLET_TYPE::SHOOT:
		{
			mpBulletType = std::make_unique<Shoot>();
			mType = BULLET_TYPE::SHOOT;
			break;
		}
		case BULLET_TYPE::SHOOTING:
		{
			mpBulletType = std::make_unique<Shooting>();
			mType = BULLET_TYPE::SHOOTING;
			break;
		}
		case BULLET_TYPE::CANNONBALL:
		{
			mpBulletType = std::make_unique<CannonBall>();
			mType = BULLET_TYPE::CANNONBALL;
			break;
		}
		case BULLET_TYPE::MAGIC:
		{
			mpBulletType = std::make_unique<Magic>();
			mType = BULLET_TYPE::MAGIC;
			break;
		}
		default:
			break;
	}
}