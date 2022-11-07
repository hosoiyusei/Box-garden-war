#pragma once
#include<SimpleMath.h>

class Effect
{
private:

	//エフェクトの座標
	DirectX::SimpleMath::Vector3 mPos, mStartPos;

	//移動速度
	DirectX::SimpleMath::Vector3 mSpeed;

	//色
	DirectX::SimpleMath::Vector3 mColor;

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

	//描画するテクスチャ
	TEXTURE3D mTexture;

	//有向かどうかのフラグ
	bool mActive;

	//生きてる時間
	int mActiveTimer;

	//大きさ
	float mSize;

	bool mSetBillboardFlag;

public:

	//コンストラクタ
	Effect();
	//デストラクタ
	~Effect();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクトの実行
	void Play(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3 color
		, const TEXTURE3D& texture
		, const float& speed
		, const float& size
		, const bool& SetBillboard = false);

	void SetMoveVector(
		const DirectX::SimpleMath::Vector3& vel);

	//Activeフラグを返す
	const bool GetActive() { return mActive; }
};