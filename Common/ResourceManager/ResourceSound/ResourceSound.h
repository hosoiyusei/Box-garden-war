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

	//�T�E���h�̃��[�h
	void Read_Sound();

	//�T�E���h�̎擾
	const int& GetBGM(
		const SOUND_BGM& sound);

	const int& GetSE(
		const SOUND_SE& sound);

	//�T�E���h�̖��O���擾
	const std::vector<const wchar_t*>& GetSoundName() { return mSoundName; }
};