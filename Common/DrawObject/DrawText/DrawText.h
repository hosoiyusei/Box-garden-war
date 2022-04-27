#pragma once

class Text
{
public:

	//�R���X�g���N�^
	Text();
	//�f�X�g���N�^
	~Text();

	//�e�L�X�g�̕`��
	void TextDraw(
		_In_z_ const wchar_t* szFileName
		, const DirectX::XMFLOAT2& Pos
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f
		, const float& size = 1.0f);

	//Int�^�̕`��
	void DrawInt(
		const int& i
		, const DirectX::XMFLOAT2& Pos
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f
		, const float& size = 1.0f);

	//Float�^�̕`��
	void DrawFloat(
		const float& f
		, const DirectX::XMFLOAT2& Pos
		, const DirectX::FXMVECTOR& color = DirectX::Colors::White
		, const float& Rotation = 0.0f
		, const float& size = 1.0f);
};