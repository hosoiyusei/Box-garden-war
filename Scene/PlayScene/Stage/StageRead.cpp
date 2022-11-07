#include"pch.h"
#include"StageRead.h"
#include<fstream>
#include<sstream>

//�X�e�[�W0============================================
const int Stage_0_vertical(11);
const int Stage_0_Horizontal(22);
//�X�e�[�W1============================================
const int Stage_1_vertical(17);
const int Stage_1_Horizontal(13);
//�X�e�[�W2============================================
const int Stage_2_vertical(10);
const int Stage_2_Horizontal(12);
//�X�e�[�W3============================================
const int Stage_3_vertical(10);
const int Stage_3_Horizontal(10);
//�`���[�g���A��============================================
const int tutorial_vertical(5);
const int tutorial_Horizontal(15);


//�R���X�g���N�^
StageRead::StageRead()
	:mStage{}
	, mHorizontal(0)
	, mVertical(0)
{

}

//�f�X�g���N�^
StageRead::~StageRead()
{

}

//�ǂݍ��ރX�e�[�W��I��
void StageRead::SetStageNum(const STAGE_NUM& num)
{
	switch (num)
	{
		case STAGE_NUM::STAGE_0:
		{
			ReadStage("Resources/Stage/0000.csv", Stage_0_vertical, Stage_0_Horizontal);
			break;
		}	
		case STAGE_NUM::STAGE_1:
		{
			ReadStage("Resources/Stage/0001.csv", Stage_1_vertical, Stage_1_Horizontal);
			break;
		}
		case STAGE_NUM::STAGE_2:
		{
			ReadStage("Resources/Stage/0002.csv", Stage_2_vertical, Stage_2_Horizontal);
			break;
		}
		case STAGE_NUM::STAGE_3:
		{
			ReadStage("Resources/Stage/0003.csv", Stage_3_vertical, Stage_3_Horizontal);			
			break;
		}
		case STAGE_NUM::TUTORIAL:
		{
			ReadStage("Resources/Stage/tutorial.csv", tutorial_vertical, tutorial_Horizontal);
			break;
		}
		case STAGE_NUM::NUM:{break;}
		default:break;
	}
}

/**************************************************************/

//�X�e�[�W�����[�h
void StageRead::ReadStage(
	const std::string& path
	, const int& vertical
	, const int& horizontal)
{
	mHorizontal = horizontal;//����
	mVertical = vertical;//����

	//�X�e�[�W�̃f�[�^��ǂݍ���
	std::vector<std::string> verticaldata;
	std::vector<std::stringstream> horizontaldata;

	//�X�e�[�W�̃t�@�C�����J��
	std::ifstream ifs(path);
	
	for (int y = 0; y < mVertical; y++)
	{
		verticaldata.push_back("");
		ifs >> verticaldata[y];//�c��̒ǉ�

		horizontaldata.push_back(std::stringstream());
		horizontaldata[y] << verticaldata[y];//����̒ǉ�

		mStage.push_back(std::vector<int>());

		for (int x = 0; x < mHorizontal; x++)
		{
			//�X�e�[�W�̔z��̒ǉ�
			mStage[y].push_back(0);

			//�X�e�[�W�f�[�^�̎擾
			horizontaldata[y] >> mStage[y][x];
			horizontaldata[y].ignore();
		}
	}
}