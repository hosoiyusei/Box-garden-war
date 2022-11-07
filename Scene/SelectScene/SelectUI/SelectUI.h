#pragma once
#include"../../IScene.h"

class Button;
class SelectStageLoad;

class SelectUI
{
private:

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

	int mStage_draw_num;

	//�V�[���ړ��̃t�F�[�h�̃t���O
	bool mMoveFadeFlag;

	bool mBackTitle_Flag;

	std::unique_ptr<SelectStageLoad> mpSelectStageLoad;

public:

	//�R���X�g���N�^
	SelectUI();
	//�f�X�g���N�^
	~SelectUI();

	//������
	void Initialize();

	//�X�V
	const bool Update();

	//�`��
	void Draw();

	const GAME_SCENE Title_Back();

private:

	//�}�E�X���N���b�N�����Ƃ��̃C�x���g
	void ClickEvent(const int& stagenum);
};