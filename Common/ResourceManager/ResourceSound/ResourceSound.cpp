#include"pch.h"
#include"ResourceSound.h"

//サウンドのロード
void ResourceSound::Read_Sound()
{
	mSoundName.push_back(L"Resources/Sound/Title.wav");
	mSoundName.push_back(L"Resources/Sound/Play.wav");
}

//サウンドの番号を返す
const int& ResourceSound::GetBGM(
	const SOUND_BGM& sound)
{
	switch (sound)
	{
		case SOUND_BGM::TITLE_BGM:		{return 0;break;}
		case SOUND_BGM::PLAY_BGM:		{return 1;break;}
		default:break;
	}

	return 0;
}

const int& ResourceSound::GetSE(
	const SOUND_SE& sound)
{
	switch (sound)
	{
		case SOUND_SE::SE_SLASHING:		{return 0; break; }
		case SOUND_SE::SE_ARROW:		{return 1;break;}
		case SOUND_SE::SE_GUN:			{return 2;break;}
		case SOUND_SE::SE_CANNON:		{return 3;break;}
		case SOUND_SE::SE_MAGIC:		{return 4;break;}
		case SOUND_SE::SE_DAMAGE:		{return 5; break;}
		case SOUND_SE::SE_BUTTON1:		{return 6; break; }
		case SOUND_SE::SE_BUTTON2:		{return 7; break; }
		default:			break;
	}

	return 0;
}