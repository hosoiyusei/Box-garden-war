#include"pch.h"
#include"Shoot.h"
#include"../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Shoot::Shoot()
	:mOffensivePower(0)
	, mAngle(0.0f)
	,mColor()
	,mPos()
{

}

//デストラクタ
Shoot::~Shoot()
{

}

//発射
void Shoot::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	mAngle = angle;
	mOffensivePower = power;
	mLevel = level;
	mColor = color;
}

//弾の更新
void Shoot::Update(EffectManager* pEffectManager)
{
	UNREFERENCED_PARAMETER(pEffectManager);
}

//描画
void Shoot::Draw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	//ワールドの初期化
	Matrix world = Matrix::Identity;

	mPos = pos;

	world = Matrix::CreateScale(0.2f, 0.2f, 0.08f);
	world *= Matrix::CreateRotationY(-mAngle - 1.56f);
	world *= Matrix::CreateTranslation(pos);
	pObject.GetModel()->Draw(world, MODEL_NAME::ARROW);
}