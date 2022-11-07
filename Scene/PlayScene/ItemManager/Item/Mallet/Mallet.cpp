#include"pch.h"
#include"Mallet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Mallet::Mallet()
	:mCapsule()
	, mPos()
	, mFloating(0.0f)
	, mSphereCollision()
	, mUse(false)
{

}

//デストラクタ
Mallet::~Mallet()
{

}

//初期化
void Mallet::Initialize()
{

}

//更新
void Mallet::Update()
{
	mFloating += 0.03f;
}

//描画
void Mallet::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;
	pObject.GetTexture3D()->SetColor();

	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale(0.6f);
	world *= Matrix::CreateTranslation(mPos.x, mPos.y - static_cast<float>((sin(mFloating) * 0.2f)), mPos.z);

	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::MALLET);
}

//Spawn
void Mallet::Spawn(const Vector3& pos)
{
	mPos = pos;

	mCapsule.mStart = pos;
	mCapsule.mEnd = pos;
	mCapsule.mRadius = 1.0f;

	mUse = false;
}

//Capsuleの当たり判定を返す
const bool Mallet::CheckHitCapsule(const Capsule& capsule)
{
	InputManager& inputManager = InputManager::GetInstance();

	if (mCapsule.HitCheck_Capsule2Capsule(mCapsule, capsule) == true &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		return true;
	}

	return false;
}