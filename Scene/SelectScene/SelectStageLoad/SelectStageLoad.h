#pragma once

class SelectStageLoad
{
private:

	std::vector<std::vector<int>> mStage;
	//ステージの立幅と横幅
	int mHorizontal, mVertical;

	bool mDrawFlag;

public:

	SelectStageLoad();
	~SelectStageLoad() = default;

	void Initialize();

	void Update(const int& Stagenum);

	void Draw();

private:

	void LoadStageNum(const int& Stagenum);

	void ReadStage(
		const std::string& path
		, const int& vertical
		, const int& horizontal);

	void DrawStageTexture(const int& Stagenum, const int& i, const int& j);
};