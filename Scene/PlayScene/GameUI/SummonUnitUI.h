#pragma once
#include"../UnitManager/Unit/UnitType.h"

#include"../../TitleScene/Button/Button.h"

//�O���錾
class Button;
class Player;
class Tutorial;

class SummonUnitUI
{
private:

	UNIT_TYPE mType;

	int mWindowPosX;

	bool mOnButtonFlag;

	std::map<UNIT_TYPE, std::unique_ptr<Button>> mpButtons;

	Player* mpPlayer;

	Tutorial* mpTutorial;

public:

	//�R���X�g���N�^
	SummonUnitUI();
	//�f�X�g���N�^
	~SummonUnitUI();

	void Initialize(Player* pPlayer, Tutorial* pTutorial);

	void Update();

	//�`��
	void Draw(const bool& Flag);

	Button* Summon_Unit_Button(const UNIT_TYPE& type) { return mpButtons[type].get(); }

private:

	void UnitName(const DirectX::XMFLOAT2& pos);

	void UnitAttack(const DirectX::XMFLOAT2& pos);

	void Unitattribute(const DirectX::XMFLOAT2& pos);

	void Money(const DirectX::XMFLOAT2& pos);

	void Change_Color(const UNIT_TYPE& type, const int& money,const int& mouse_scroll, const int& mouse_scroll2);

	void Button_Change_Color();
};