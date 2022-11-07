#pragma once
#include"ObjectType.h"

class Object
{
private:

	//オブジェクトの座標
	DirectX::SimpleMath::Vector3 mPos;

	//オブジェクトの種類
	OBJECT_TYPE mType;

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

public:

	//コンストラクタ
	Object();
	//デストラクタ
	~Object();

	//初期化
	void Initialize(int stagetilenum);

	//描画
	void Draw();

	//座標の設定
	void SetPos(
		const float& x
		, const float& z);

	//オブジェクトの座標を返す
	const DirectX::SimpleMath::Vector3 GetPos();

	//オブジェクトの種類を返す
	const OBJECT_TYPE GetType()
	{
		return mType;
	}
};