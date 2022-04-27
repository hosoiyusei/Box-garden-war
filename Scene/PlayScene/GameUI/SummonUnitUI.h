#pragma once
#include"../UnitManager/Unit/UnitType.h"

//�O���錾
class Player;

class SummonUnitUI
{
private:

	UNIT_TYPE mType;

	Player* mpPlayer;

	int mWindowPosX;

public:

	//�R���X�g���N�^
	SummonUnitUI();
	//�f�X�g���N�^
	~SummonUnitUI();

	void Initialize(Player* pPlayer);

	//�`��
	void Draw(const bool& Flag, const int& X, const int& Y);

private:

	void UnitName(const DirectX::XMFLOAT2& pos);

	void UnitAttack(const DirectX::XMFLOAT2& pos);

	void Unitattribute(const DirectX::XMFLOAT2& pos);

	void Money(const DirectX::XMFLOAT2& pos);
};