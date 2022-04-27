#pragma once

//�O���錾
class Player;
class ArrowUI;
class SummonUnitUI;
class Reinforcement;
class StageInformation;

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

public:

	//�R���X�g���N�^
	GameUI();
	//�f�X�g���N�^
	~GameUI();

	//������
	void Initialize(Player* pPlayer);

	//�`��
	void Draw();

private:

	void DrawNumbers(const int& number,const int& x,const int& y);
};