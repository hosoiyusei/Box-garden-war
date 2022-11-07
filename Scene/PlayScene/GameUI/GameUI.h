#pragma once
#include"SummonUnitUI.h"

//�O���錾
class Player;
class ArrowUI;
class Tutorial;

class Reinforcement;
class StageInformation;
class EnemyManager;
class UnitManager;
class Button;
class PlaySetting;

class GameUI
{
private:

	//�v���C���[�̃|�C���^
	Player* mpPlayer;

	//������E�ꎞ��~��UI
	std::unique_ptr<ArrowUI> mpArrowUI;

	//Unit���Ăяo���Ƃ���UI
	std::unique_ptr<SummonUnitUI> mpSummonUnitUI;

	//Unit����������Ƃ���UI
	std::unique_ptr<Reinforcement> mpReinforcement;

	//�X�e�[�W�̏���UI
	std::unique_ptr<StageInformation> mpStageInformation;

	std::unique_ptr<PlaySetting> mpPlaySetting;

	EnemyManager* mpEnemyManager;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

	bool mBackSelectFlag;

	bool mSettingFlag;

public:

	//�R���X�g���N�^
	GameUI();
	//�f�X�g���N�^
	~GameUI();

	//������
	void Initialize(EnemyManager* pEnemyManager, Player* pPlayer, UnitManager* pUnitManager, Tutorial* pTutorial);

	void Update();

	//�`��
	void Draw();

	Button* Summon_Unit_Button(const UNIT_TYPE& type);

	const bool BackSelectScene();

private:

	void DrawNumbers(const int& number,const int& x,const int& y);
};