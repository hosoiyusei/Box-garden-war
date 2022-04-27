#pragma once
#include"BulletTypeBase.h"
#include"BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

class Shoot :public BulletTypeBase
{
private:

	//UŒ‚—Í
	int mOffensivePower;

	//Œü‚«
	float mAngle;

	UNIT_LEVEL mLevel;

public:

	Shoot();
	~Shoot();

	//’e‚ª—LŒø‚È‹——£
	const float& GetLen() override { return 4.0f; }

	//ƒXƒs[ƒh‚Ìİ’è
	const float& GetSpeed()override { return 0.1f; }

	//UŒ‚—Í
	const int& GetOffensivePower()override { return mOffensivePower; }

	//”­Ë
	void Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)override;

	//’e‚Ìí—Ş‚ğ•Ô‚·
	const BULLET_TYPE& GetType()override { return BULLET_TYPE::SHOOT; }

	//’e‚ÌXV
	void Update(EffectManager* pEffectManager)override {};

	//’e‚Ì•`‰æ
	void Draw(const DirectX::SimpleMath::Vector3& pos)override;

	const UNIT_LEVEL GetLevel()override { return mLevel; }
};