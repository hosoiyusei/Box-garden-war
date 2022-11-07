#include"pch.h"
#include"CannonBall.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
CannonBall::CannonBall()
	:mOffensivePower(0)
	,mLevel()
{

}

//デストラクタ
CannonBall::~CannonBall()
{

}

//発射
void CannonBall::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	UNREFERENCED_PARAMETER(color);
	UNREFERENCED_PARAMETER(angle);
	mOffensivePower = power;
	mLevel = level;
}

//描画
void CannonBall::Draw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;

	world = Matrix::CreateScale(0.6f);
	world *= Matrix::CreateTranslation(pos);

	pObject.GetGeometry()->Draw(world, SHAPE::SPHERE, Colors::Black);
}