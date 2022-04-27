#include"pch.h"
#include"Shooting.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Shooting::Shooting()
	:mOffensivePower(0)
{

}

//デストラクタ
Shooting::~Shooting()
{

}

//発射
void Shooting::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	mOffensivePower = power;
	mLevel = level;
}

//描画
void Shooting::Draw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;
	world = Matrix::CreateScale(0.2f);
	world *= Matrix::CreateTranslation(pos);

	pObject.GetGeometry()->Draw(world, SHAPE::SPHERE, Colors::Black);
}