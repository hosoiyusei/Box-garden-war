#pragma once

//前方宣言
class Effect;

class EffectManager
{
private:

	//Effectの配列
	std::vector<std::unique_ptr<Effect>> mpEffect;

public:

	//コンストラクタ
	EffectManager();
	//デストラクタ
	~EffectManager();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクトの実行
	void Play(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& color
		, const int& number
		, const TEXTURE3D& texture
		, const float& speed = 0.003f
		, const float& size = 0.3f);

	//エフェクトの実行
	void Play_2(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& color
		, const int& number
		, const TEXTURE3D& texture
		, const float& speed = 0.003f
		, const float& size = 0.3f);

	//エフェクトの実行
	void Play_3(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& color
		, const int& number
		, const TEXTURE3D& texture
		, const float& speed = 0.003f
		, const float& size = 0.3f);
};