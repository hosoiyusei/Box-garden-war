#pragma once
#include<string>
#include<vector>

//ステージの種類
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

	//ステージの立幅と横幅
	int mHorizontal, mVertical;

	//ステージデータの配列
	std::vector<std::vector<int>> mStage;

public:

	//コンストラクタ
	StageRead();
	//デストラクタ
	~StageRead();

	//読み込むステージを選択
	void SetStageNum(const STAGE_NUM& num);

	//ステージデータの取得
	const int GetStageData(const int& x,const int& y)
	{
		return mStage[y][x];
	}

	//ステージの横幅の取得
	const int GetHorizontal()
	{
		return mHorizontal;
	}

	//ステージの立幅の取得
	const int GetVertical()
	{
		return mVertical;
	}

private:

	//ステージを読み込む
	void ReadStage(
		const std::string& path
		, const int& vertical
		, const int& horizontal);
};