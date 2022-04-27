#pragma once
#include"../UnitManager/Unit/UnitType.h"

//前方宣言
class Player;

class SummonUnitUI
{
private:

	UNIT_TYPE mType;

	Player* mpPlayer;

	int mWindowPosX;

public:

	//コンストラクタ
	SummonUnitUI();
	//デストラクタ
	~SummonUnitUI();

	void Initialize(Player* pPlayer);

	//描画
	void Draw(const bool& Flag, const int& X, const int& Y);

private:

	void UnitName(const DirectX::XMFLOAT2& pos);

	void UnitAttack(const DirectX::XMFLOAT2& pos);

	void Unitattribute(const DirectX::XMFLOAT2& pos);

	void Money(const DirectX::XMFLOAT2& pos);
};