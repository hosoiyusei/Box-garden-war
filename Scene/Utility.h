#pragma once

struct Float2
{
	float mX;
	float mY;

	Float2()
		: mX(0.0f)
		, mY(0.0f)
	{

	}
};

struct Int2
{
	int mX;
	int mY;

	Int2()
		: mX(0)
		, mY(0)
	{

	}
};

struct VIEW
{
	float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;

	VIEW()
		:eyeX(0.0f)
		, eyeY(2.0f)
		, eyeZ(10.0f)
		, targetX(0.0f)
		, targetY(0.0f)
		, targetZ(0.0f)
		, upX(0.0f)
		, upY(1.0f)
		, upZ(0.0f)
	{

	}
};