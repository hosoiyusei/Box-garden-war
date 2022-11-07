#include"pch.h"
#include"Magic.h"
#include"../../EffectManager/EffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Magic::Magic()
	:mColor()
	,mPos()
	, mOffensivePower()
	,mLevel()
{

}

//デストラクタ
Magic::~Magic()
{

}

//発射
void Magic::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	mColor = color;
	UNREFERENCED_PARAMETER(angle);
	mOffensivePower = power;
	mLevel = level;
}

void Magic::Update(EffectManager* pEffectManager)
{
	pEffectManager->Play(
		mPos
		, Vector3(mColor.x, mColor.y, mColor.z)
		, 1
		, TEXTURE3D::SHADOW
		, 0.0007f
		, 0.1f);
}

//描画
void Magic::Draw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();

	Matrix world = Matrix::Identity;

	mPos = pos;

	world = Matrix::CreateScale(0.3f);
	world *= Matrix::CreateTranslation(pos);

	pObject.GetGeometry()->Draw(world, SHAPE::SPHERE, mColor * 3.0f);
}