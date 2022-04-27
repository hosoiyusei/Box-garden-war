#pragma once
#include"../../Scene.h"

class TitleUI
{
private:

	//�ݒ�̃t���O
	bool mSettingFlag;

	GAME_SCENE mScene;

public:

	//�R���X�g���N�^
	TitleUI();
	//�f�X�g���N�^
	~TitleUI();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�V�[����Ԃ�
	GAME_SCENE GetScene() { return mScene; }

private:

	//�ݒ�̕`��
	void DrawSetting();
};