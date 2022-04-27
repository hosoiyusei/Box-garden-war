#include"pch.h"
#include"Shoot.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Shoot::Shoot()
	:mOffensivePower(0)
	, mAngle(0.0f)
{

}

//�f�X�g���N�^
Shoot::~Shoot()
{

}

//����
void Shoot::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	mAngle = angle;
	mOffensivePower = power;
	mLevel = level;
}

//�`��
void Shoot::Draw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	//���[���h�̏�����
	Matrix world = Matrix::Identity;

	world = Matrix::CreateScale(0.08f);
	world *= Matrix::CreateRotationY(-mAngle-1.56f);
	world *= Matrix::CreateTranslation(pos);
	pObject.GetModel()->Draw(world, MODEL_NAME::ARROW);
}