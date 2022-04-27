#include"pch.h"
#include"SoundManager.h"
#include"Adx2.h"

void SoundManager::Read_Sound()
{
	ResourceManager& pRm = ResourceManager::GetInstance();

	// オーディオエンジンを作成する。
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags |= DirectX::AudioEngine_Debug;
#endif
	m_audEngine = std::make_unique<DirectX::AudioEngine>(eflags);

	for (int i = 0; i < pRm.GetSoundName().size(); i++)
	{
		// wavデータをロードする。
		m_soundEffect.push_back(std::make_unique<DirectX::SoundEffect>(m_audEngine.get(), pRm.GetSoundName()[i]));

		m_soundEffectInstance.push_back(m_soundEffect[i]->CreateInstance());
	}
}

void SoundManager::BGM_Run(
	const SOUND_BGM& sound
	, const BGM_RUN& run
	, const float& set)
{
	switch (run)
	{
		case BGM_RUN::PAUSE:	{GetBGM(sound)->Pause();break;}			//ポーズ
		case BGM_RUN::PITCH:	{GetBGM(sound)->SetPitch(set);break;}	//ピッチの設定
		case BGM_RUN::PLAY:		{GetBGM(sound)->Play(); break;}			//再生
		case BGM_RUN::STOP:		{GetBGM(sound)->Stop();break;}			//停止
		case BGM_RUN::LOOP:		{GetBGM(sound)->Play(true);break;}		//繰り返し再生
		case BGM_RUN::RESUME:	{GetBGM(sound)->Resume(); break; }		//ポーズの解除
		case BGM_RUN::VOLUME:	{GetBGM(sound)->SetVolume(set);break;}	//音量の設定
		default:break;
	}
}

void SoundManager::SE_Run(
	const SOUND_SE& sound
	, const SE_RUN& run
	, const float& set)
{
	ADX2& adx2 = ADX2::GetInstance();

	switch (run)
	{
		case SE_RUN::PLAY:		{adx2.Play(GetSE(sound));	break; }
		case SE_RUN::STOP:		{adx2.Stop(GetSE(sound));	break; }
		case SE_RUN::VOLUME:	{adx2.SetVolume(set);		break; }
		default:
			break;
	}
}

void SoundManager::Update()
{
	m_audEngine->Update();
}

/****************************************************************************************************/

//BGMの配列番号の取得
DirectX::SoundEffectInstance* SoundManager::GetBGM(
	const SOUND_BGM& sound)
{
	ResourceManager& pRm = ResourceManager::GetInstance();

	return m_soundEffectInstance[pRm.GetBGM(sound)].get();
}

//SEの配列番号の取得
const int& SoundManager::GetSE(
	const SOUND_SE& sound)
{
	ResourceManager& pRm = ResourceManager::GetInstance();

	return pRm.GetSE(sound);
}