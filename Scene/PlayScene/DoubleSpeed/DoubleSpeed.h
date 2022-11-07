#pragma once
#include"../../../Common/Singleton.h"

class DoubleSpeed : public Singleton<DoubleSpeed>
{
private:

	//�{���̑��x
	float mSpeed;

	//�ꎞ��~
	bool mExecutionFlag;

public:

	DoubleSpeed();
	~DoubleSpeed() = default;

	const float& GetSpeed() { return mSpeed; }

	void SetSpeed(const float speed) { mSpeed = speed; }

	const bool& GetExecutionFlag() { return mExecutionFlag; }

	void SetExecutionFlag(const bool Execution) { mExecutionFlag = Execution; }
};