#pragma once
#include<Audio.h>
#include"../ResourceManager/ResourceManager.h"
#include<vector>
#include"../Singleton.h"

enum class BGM_RUN :int
{
	PLAY,
	STOP,
	PAUSE,
	PITCH,
	LOOP,
	RESUME,
	VOLUME,
};

enum class SE_RUN :int
{
	PLAY,
	STOP,
	VOLUME,
};

class SoundManager : public Singleton<SoundManager>
{
private:

	// サウンドリソースのコンテナクラスへのポインタ
	std::vector<std::unique_ptr<DirectX::SoundEffect>> m_soundEffect;
	// オーディオエンジンへのポインタ 
	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	// サウンドリソースのコンテナクラスへのポインタ
	std::vector < std::unique_ptr<DirectX::SoundEffectInstance>> m_soundEffectInstance;

public:

	//サウンドのロード
	void Read_Sound();

	//サウンドの実行
	void BGM_Run(
		const SOUND_BGM& sound
		, const BGM_RUN& run
		, const float& set = 0.0f);

	void SE_Run(
		const SOUND_SE& sound
		, const SE_RUN& run
		, const float& set = 0.0f
	);

	//サウンドの更新
	void Update();

private:

	//BGMを返す
	DirectX::SoundEffectInstance* GetBGM(const SOUND_BGM& sound);

	//SEを返す
	const int GetSE(const SOUND_SE& sound);
};