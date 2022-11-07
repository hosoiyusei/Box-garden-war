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

	// �T�E���h���\�[�X�̃R���e�i�N���X�ւ̃|�C���^
	std::vector<std::unique_ptr<DirectX::SoundEffect>> m_soundEffect;
	// �I�[�f�B�I�G���W���ւ̃|�C���^ 
	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	// �T�E���h���\�[�X�̃R���e�i�N���X�ւ̃|�C���^
	std::vector < std::unique_ptr<DirectX::SoundEffectInstance>> m_soundEffectInstance;

public:

	//�T�E���h�̃��[�h
	void Read_Sound();

	//�T�E���h�̎��s
	void BGM_Run(
		const SOUND_BGM& sound
		, const BGM_RUN& run
		, const float& set = 0.0f);

	void SE_Run(
		const SOUND_SE& sound
		, const SE_RUN& run
		, const float& set = 0.0f
	);

	//�T�E���h�̍X�V
	void Update();

private:

	//BGM��Ԃ�
	DirectX::SoundEffectInstance* GetBGM(const SOUND_BGM& sound);

	//SE��Ԃ�
	const int GetSE(const SOUND_SE& sound);
};