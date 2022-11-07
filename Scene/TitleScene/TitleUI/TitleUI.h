#pragma once
#include"../../Scene.h"

class Button;

class TitleUI
{
private:

	//�ݒ�̃t���O
	bool mSettingFlag;

	GAME_SCENE mScene;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

public:

	//�R���X�g���N�^
	TitleUI();
	//�f�X�g���N�^
	~TitleUI();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�V�[����Ԃ�
	GAME_SCENE GetScene() { return mScene; }

private:

	//�ݒ�̍X�V
	void Setting_Update();

	//�ݒ�̕`��
	void DrawSetting();

	//���ʂ̃Q�[�W�̕`��
	void Sound_gage_draw();
};