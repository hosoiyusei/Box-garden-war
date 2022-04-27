#pragma once
#include"SoundType.h"
#include<vector>

class ResourceSound
{
private:

	std::vector<const wchar_t*> mSoundName;

public:

	ResourceSound() :mSoundName{} {};
	~ResourceSound() {};

	//サウンドのロード
	void Read_Sound();

	//サウンドの取得
	const int& GetBGM(
		const SOUND_BGM& sound);

	const int& GetSE(
		const SOUND_SE& sound);

	//サウンドの名前を取得
	const std::vector<const wchar_t*>& GetSoundName() { return mSoundName; }
};