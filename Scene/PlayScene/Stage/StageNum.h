#pragma once
#include"StageRead.h"
#include"../../../Common/Singleton.h"

class StageNum : public Singleton<StageNum>
{
private:

	//���[�h����X�e�[�W
	STAGE_NUM stage;

public:

	//�R���X�g���N�^
	StageNum():stage(STAGE_NUM::NUM) {};
	//�f�X�g���N�^
	~StageNum() {};

	//���[�h����X�e�[�W�̔ԍ���Ԃ�
	const STAGE_NUM& GetStageNum() { return stage; }

	//�X�e�[�W���Z�b�g
	void SetStage(const int& stagenum)
	{
		if (stagenum == 0)
		{
			stage = STAGE_NUM::STAGE_0;
		}
		else if (stagenum == 1)
		{
			stage = STAGE_NUM::STAGE_1;
		}
		else if (stagenum == 2)
		{
			stage = STAGE_NUM::STAGE_2;
		}
		else if (stagenum == 3)
		{
			stage = STAGE_NUM::STAGE_3;
		}
		else if (stagenum == 4)
		{
			stage = STAGE_NUM::TUTORIAL;
		}
	}
};