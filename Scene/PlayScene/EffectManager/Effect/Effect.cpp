#include"pch.h"
#include"Effect.h"
#include<random>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Effect::Effect()
	:mActive(false)
	, mPos()
	, mWorld()
	, mSpeed()
	, mActiveTimer(0)
	, mStartPos()
	, mColor()
	, mTexture(TEXTURE3D::NONE)
	, mSize(0.0f)
	, mSetBillboardFlag(false)
{

}

//�f�X�g���N�^
Effect::~Effect()
{

}

//������
void Effect::Initialize()
{

}

//�X�V
void Effect::Update()
{
	mPos += mSpeed;

	mActiveTimer++;

	Vector3 len = mStartPos - mPos;

	if (len.Length() > 1.0f)
	{
		mActive = false;
	}

	if (mActiveTimer > 50)
	{
		mActive = false;
	}
}

//�`��
void Effect::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	pObject.GetTexture3D()->SetColor(mColor.x, mColor.y, mColor.z);

	//���W�̐ݒ�
	mWorld = Matrix::Identity;
	if (mSetBillboardFlag == false)
	{
		pObject.GetTexture3D()->DrawBillboard(mWorld);
	}
	else
	{
		mWorld *= Matrix::CreateRotationX(1.57f);
	}
	mWorld *= Matrix::CreateScale(mSize);
	mWorld *= Matrix::CreateTranslation(mPos);
	pObject.GetTexture3D()->DrawShader(mWorld, mTexture);
}

//�G�t�F�N�g�̎��s
void Effect::Play(
	const  Vector3& pos
	, const Vector3 color
	, const TEXTURE3D& texture
	, const float& speed
	, const float& size
	, const bool& SetBillboard)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(-10, 10);

	mSpeed = Vector3(
		  static_cast<float>(dist(mt)) * speed
		, static_cast<float>(dist(mt)) * speed
		, static_cast<float>(dist(mt)) * speed);

	mColor = color;

	mPos = pos;

	mStartPos = pos;

	mActiveTimer = 0;

	mSize = size;

	mTexture = texture;

	//�A�N�e�B�u�ɂ���
	mActive = true;

	mSetBillboardFlag = SetBillboard;
}

void Effect::SetMoveVector(
	const DirectX::SimpleMath::Vector3& vel)
{
	mSpeed = vel * 0.3f;
	mSpeed.y = 0.02f;
}