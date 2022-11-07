#pragma once
#include<string>
#include<vector>

//�X�e�[�W�̎��
enum class STAGE_NUM :int
{
	STAGE_0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	TUTORIAL,

	NUM,
};

class StageRead final
{
private:

	//�X�e�[�W�̗����Ɖ���
	int mHorizontal, mVertical;

	//�X�e�[�W�f�[�^�̔z��
	std::vector<std::vector<int>> mStage;

public:

	//�R���X�g���N�^
	StageRead();
	//�f�X�g���N�^
	~StageRead();

	//�ǂݍ��ރX�e�[�W��I��
	void SetStageNum(const STAGE_NUM& num);

	//�X�e�[�W�f�[�^�̎擾
	const int GetStageData(const int& x,const int& y)
	{
		return mStage[y][x];
	}

	//�X�e�[�W�̉����̎擾
	const int GetHorizontal()
	{
		return mHorizontal;
	}

	//�X�e�[�W�̗����̎擾
	const int GetVertical()
	{
		return mVertical;
	}

private:

	//�X�e�[�W��ǂݍ���
	void ReadStage(
		const std::string& path
		, const int& vertical
		, const int& horizontal);
};