#include"pch.h"
#include"Slashing.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Slashing::Slashing()
	:mOffensivePower(0)
{

}

//デストラクタ
Slashing::~Slashing()
{

}

//発射
void Slashing::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	mOffensivePower = power;
	mLevel = level;
}

//描画
void Slashing::Draw(const Vector3& pos)
{
	//警告除け
	pos;
}