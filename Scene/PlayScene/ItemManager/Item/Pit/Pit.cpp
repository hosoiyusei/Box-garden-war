#include"pch.h"
#include"Pit.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Pit::Pit()
	:mCapsule()
	,mPos()
	, mFloating(0.0f)
	, mSphereCollision()
	, mUse(false)
{

}

//デストラクタ
Pit::~Pit()
{

}

//初期化
void Pit::Initialize()
{

}

//更新
void Pit::Update()
{
	mFloating += 0.03f;
}

//描画
void Pit::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;
	pObject.GetTexture3D()->SetColor();

	if (mUse == false)
	{
		pObject.GetTexture3D()->DrawBillboard(world);
		world *= Matrix::CreateScale(0.9f, 0.5f, 0.5f);
		world *= Matrix::CreateTranslation(mPos.x, mPos.y - (sin(mFloating) * 0.2f), mPos.z);
		
	}
	else
	{
		world *= Matrix::CreateRotationX(1.57f);
		world *= Matrix::CreateTranslation(mPos);
	}
	
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::PIT);
}

//Spawn
void Pit::Spawn(const Vector3& pos)
{
	mPos = pos;

	mCapsule.a = pos;
	mCapsule.b = pos;
	mCapsule.r = 1.0f;

	mUse = false;
}

//Capsuleの当たり判定を返す
const bool&  Pit::CheckHitCapsule(const Capsule& capsule)
{
	InputManager& inputManager = InputManager::GetInstance();

	if (mCapsule.HitCheck_Capsule2Capsule(mCapsule, capsule) == true&&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		return true;
	}

	return false;
}

void Pit::Use(const Vector3& pos)
{
	mPos = pos;
	mSphereCollision.mPos = pos;
	mSphereCollision.mRadius = 0.2f;
	mUse = true;
}