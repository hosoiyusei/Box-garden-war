#include"pch.h"
#include"SoundManager.h"
#include"Adx2.h"

void SoundManager::Read_Sound()
{
	ResourceManager& pRm = ResourceManager::GetInstance();

	// �I�[�f�B�I�G���W�����쐬����B
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags |= DirectX::AudioEngine_Debug;
#endif
	m_audEngine = std::make_unique<DirectX::AudioEngine>(eflags);

	for (int i = 0; i < pRm.GetSoundName().size(); i++)
	{
		// wav�f�[�^�����[�h����B
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
		case BGM_RUN::PAUSE:	{GetBGM(sound)->Pause();break;}			//�|�[�Y
		case BGM_RUN::PITCH:	{GetBGM(sound)->SetPitch(set);break;}	//�s�b�`�̐ݒ�
		case BGM_RUN::PLAY:		{GetBGM(sound)->Play(); break;}			//�Đ�
		case BGM_RUN::STOP:		{GetBGM(sound)->Stop();break;}			//��~
		case BGM_RUN::LOOP:		{GetBGM(sound)->Play(true);break;}		//�J��Ԃ��Đ�
		case BGM_RUN::RESUME:	{GetBGM(sound)->Resume(); break; }		//�|�[�Y�̉���
		case BGM_RUN::VOLUME:	{GetBGM(sound)->SetVolume(set);break;}	//���ʂ̐ݒ�
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

//BGM�̔z��ԍ��̎擾
DirectX::SoundEffectInstance* SoundManager::GetBGM(
	const SOUND_BGM& sound)
{
	ResourceManager& pRm = ResourceManager::GetInstance();

	return m_soundEffectInstance[pRm.GetBGM(sound)].get();
}

//SE�̔z��ԍ��̎擾
const int& SoundManager::GetSE(
	const SOUND_SE& sound)
{
	ResourceManager& pRm = ResourceManager::GetInstance();

	return pRm.GetSE(sound);
}