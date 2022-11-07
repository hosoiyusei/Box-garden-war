#pragma once
#include<SimpleMath.h>

struct SphereCollision
{
	//îºåa
	float mRadius;

	//ç¿ïW
	DirectX::SimpleMath::Vector3 mPos;

	SphereCollision()
		:mRadius(0.0f)
		, mPos()
	{

	}

	const bool CheckHit(const SphereCollision& Collision);
};