#pragma once
#include"../../../Common/Singleton.h"

class Volume : public Singleton<Volume>
{
private:

	//BGM�̉���
	float mBgmVolume;
	//SE�̉���
	float mSeVolume;

public:

	Volume();
	~Volume();

	const float& GetSEVolume() { return mSeVolume; }

	const float& GetBgmVolume() { return mBgmVolume; }

	void SetSeVolume(const float se) { mSeVolume = se; }

	void SetBgmVolume(const float bgm) { mBgmVolume = bgm; }
};