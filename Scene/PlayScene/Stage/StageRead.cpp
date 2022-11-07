#include"pch.h"
#include"StageRead.h"
#include<fstream>
#include<sstream>

//ステージ0============================================
const int Stage_0_vertical(11);
const int Stage_0_Horizontal(22);
//ステージ1============================================
const int Stage_1_vertical(17);
const int Stage_1_Horizontal(13);
//ステージ2============================================
const int Stage_2_vertical(10);
const int Stage_2_Horizontal(12);
//ステージ3============================================
const int Stage_3_vertical(10);
const int Stage_3_Horizontal(10);
//チュートリアル============================================
const int tutorial_vertical(5);
const int tutorial_Horizontal(15);


//コンストラクタ
StageRead::StageRead()
	:mStage{}
	, mHorizontal(0)
	, mVertical(0)
{

}

//デストラクタ
StageRead::~StageRead()
{

}

//読み込むステージを選択
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

//ステージをロード
void StageRead::ReadStage(
	const std::string& path
	, const int& vertical
	, const int& horizontal)
{
	mHorizontal = horizontal;//横幅
	mVertical = vertical;//立幅

	//ステージのデータを読み込む
	std::vector<std::string> verticaldata;
	std::vector<std::stringstream> horizontaldata;

	//ステージのファイルを開く
	std::ifstream ifs(path);
	
	for (int y = 0; y < mVertical; y++)
	{
		verticaldata.push_back("");
		ifs >> verticaldata[y];//縦列の追加

		horizontaldata.push_back(std::stringstream());
		horizontaldata[y] << verticaldata[y];//横列の追加

		mStage.push_back(std::vector<int>());

		for (int x = 0; x < mHorizontal; x++)
		{
			//ステージの配列の追加
			mStage[y].push_back(0);

			//ステージデータの取得
			horizontaldata[y] >> mStage[y][x];
			horizontaldata[y].ignore();
		}
	}
}