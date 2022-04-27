#pragma once

class Text
{
public:

	//コンストラクタ
	Text();
	//デストラクタ
	~Text();

	//テキストの描画
	void TextDraw(
		_In_z_ const wchar_t* szFileName
		, const DirectX::XMFLOAT2& Pos
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f
		, const float& size = 1.0f);

	//Int型の描画
	void DrawInt(
		const int& i
		, const DirectX::XMFLOAT2& Pos
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f
		, const float& size = 1.0f);

	//Float型の描画
	void DrawFloat(
		const float& f
		, const DirectX::XMFLOAT2& Pos
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f
		, const float& size = 1.0f);
};