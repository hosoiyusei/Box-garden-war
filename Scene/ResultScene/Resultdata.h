#pragma once

class Resultdata
{
public:

	//ƒVƒ“ƒOƒ‹ƒgƒ“
	static Resultdata* GetResultdataInstance()
	{
		static Resultdata instance;
		return &instance;
	}

private:
	Resultdata(const Resultdata&) = delete;
	Resultdata& operator=(const Resultdata&) = delete;
	Resultdata(const Resultdata&&) = delete;
	Resultdata&& operator=(const Resultdata&&) = delete;
private:

	bool mVictory;

	bool mGameOver;

	int mMoney;

private:

	Resultdata()
		: mVictory(false)
		, mGameOver(false)
		, mMoney(0)
	{}
	~Resultdata() {}
public:


	void SetVictory(const bool& Victory) { mVictory = Victory; }
	void SetGameOver(const bool& GameOver) { mGameOver = GameOver; }
	void SetMoney(const int& money) { mMoney = money; }

	const bool& GetVictory() { return mVictory; }
	const bool& GetGameOver() { return mGameOver; }
	const int& GetMoney() { return mMoney; }
};