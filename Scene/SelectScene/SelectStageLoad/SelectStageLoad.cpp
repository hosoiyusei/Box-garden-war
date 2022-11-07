#include"pch.h"
#include"SelectStageLoad.h"

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

using namespace DirectX;
using namespace DirectX::SimpleMath;

SelectStageLoad::SelectStageLoad()
	:mDrawFlag(false)
{

}

void SelectStageLoad::Initialize()
{
	
}

void SelectStageLoad::Update(const int& Stagenum)
{
	mDrawFlag = true;

	LoadStageNum(Stagenum);
}

void SelectStageLoad::Draw()
{
	for (int i = 0; i < static_cast<int>(mStage.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(mStage[i].size()); j++)
		{
			DrawStageTexture(mStage[i][j], i, j);
		}
	}
}

void SelectStageLoad::LoadStageNum(const int& Stagenum)
{
	switch (Stagenum)
	{
		case 1:
		{
			ReadStage("Resources/Stage/0000.csv", Stage_0_vertical, Stage_0_Horizontal);
			break;
		}
		case 2:
		{
			ReadStage("Resources/Stage/0001.csv", Stage_1_vertical, Stage_1_Horizontal);
			break;
		}
		case 3:
		{
			ReadStage("Resources/Stage/0002.csv", Stage_2_vertical, Stage_2_Horizontal);
			break;
		}
		case 4:
		{
			ReadStage("Resources/Stage/0003.csv", Stage_3_vertical, Stage_3_Horizontal);
			break;
		}
		case 5:
		{
			ReadStage("Resources/Stage/tutorial.csv", tutorial_vertical, tutorial_Horizontal);
			break;
		}
		default:
		{
			mDrawFlag = false;
			break;
		}
	}
}

void SelectStageLoad::ReadStage(
	const std::string& path
	, const int& vertical
	, const int& horizontal)
{
	mStage.clear();

	mHorizontal = horizontal;//����
	mVertical = vertical;//����

	//�X�e�[�W�̃f�[�^��ǂݍ���
	std::vector<std::string> verticaldata;
	std::vector<std::stringstream> horizontaldata;

	//�X�e�[�W�̃t�@�C�����J��
	std::ifstream ifs(path);

	for (int y = 0; y < vertical; y++)
	{
		verticaldata.push_back("");
		ifs >> verticaldata[y];//�c��̒ǉ�

		horizontaldata.push_back(std::stringstream());
		horizontaldata[y] << verticaldata[y];//����̒ǉ�

		mStage.push_back(std::vector<int>());

		for (int x = 0; x < horizontal; x++)
		{
			//�X�e�[�W�̔z��̒ǉ�
			mStage[y].push_back(0);

			//�X�e�[�W�f�[�^�̎擾
			horizontaldata[y] >> mStage[y][x];
			horizontaldata[y].ignore();
		}
	}
}

void SelectStageLoad::DrawStageTexture(const int& Stagenum, const int& i, const int& j)
{
	DrawManager& pObject = DrawManager::GetInstance();

	//�摜�̐؂���T�C�Y
	RECT rect1 = { 0,0,104,73 };

	int texturesize = 30;

	RECT rect2 = {
				 static_cast<int>(1100 + (j * texturesize) - ((mStage[i].size() * texturesize) / 2))
				,static_cast<int>(450 + (i * texturesize) - ((mStage.size() * texturesize) / 2))
				,static_cast<int>(1100 + (j * texturesize) + texturesize - ((mStage[i].size() * texturesize) / 2))
				,static_cast<int>(450 + (i * texturesize) + texturesize - ((mStage.size() * texturesize) / 2))
	};

	if (Stagenum == 0)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::TEST, rect1, rect2, Colors::SandyBrown);
	}
	else if (Stagenum == 1)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::TEST, rect1, rect2, Colors::Gray);
	}
	else if (Stagenum == 2)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::TEST, rect1, rect2, Colors::AliceBlue);
	}
	else if (Stagenum == 3 ||
		Stagenum == 4 ||
		Stagenum == 5)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::TEST, rect1, rect2, Colors::Red);
	}
	else if (Stagenum == -1)
	{
		pObject.GetTexture2D()->Draw(TEXTURE2D::TEST, rect1, rect2, Colors::LightGreen);
	}
}