#include"pch.h"
#include"Money.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Money::Money()
	:mCapsule()
	, mPos()
	, mFloating(0.0f)
	, mSphereCollision()
	, mUse(false)
{

}

//�f�X�g���N�^
Money::~Money()
{

}

//������
void Money::Initialize()
{

}

//�X�V
void Money::Update()
{
	mFloating += 0.03f;
}

//�`��
void Money::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;
	pObject.GetTexture3D()->SetColor();

	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale(0.6f);
	world *= Matrix::CreateTranslation(mPos.x, mPos.y - static_cast<float>((sin(mFloating) * 0.2f)), mPos.z);

	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::MONEY);
}

//Spawn
void Money::Spawn(const Vector3& pos)
{
	mPos = pos;

	mCapsule.mStart = pos;
	mCapsule.mEnd = pos;
	mCapsule.mRadius = 1.0f;

	mUse = false;
}

//Capsule�̓����蔻���Ԃ�
const bool Money::CheckHitCapsule(const Capsule& capsule)
{
	InputManager& inputManager = InputManager::GetInstance();

	if (mCapsule.HitCheck_Capsule2Capsule(mCapsule, capsule) == true &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		return true;
	}

	return false;
}