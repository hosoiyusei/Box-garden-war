#pragma once
#include"../../../Common/Singleton.h"

class DoubleSpeed : public Singleton<DoubleSpeed>
{
private:

	float mSpeed;

	bool mExecutionFlag;

public:

	DoubleSpeed();
	~DoubleSpeed();

	const float& GetSpeed() { return mSpeed; }

	void SetSpeed(const float speed) { mSpeed = speed; }

	const bool& GetExecutionFlag() { return mExecutionFlag; }

	void SetExecutionFlag(const bool Execution) { mExecutionFlag = Execution; }
};