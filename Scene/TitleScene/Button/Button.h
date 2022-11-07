#pragma once

class Button
{
private:

	//Button�̕`����W
	RECT rect;

public:

	Button() :rect{} {};
	~Button() = default;

	//�{�^���������ꂽ���̔���
	const bool Determining_if_the_mouse_is_on();

	//Button�̕`��
	void DrawButton(
		const RECT& texture_size
		, const TEXTURE2D& button_texture
		, _In_z_ const wchar_t* szFileName
		, const DirectX::XMFLOAT2& sentence_position_x
		, const DirectX::FXMVECTOR& sentence_color = DirectX::Colors::White
		, const float& sentence_size = 1.0f
		, const DirectX::FXMVECTOR& button_color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f)
		, const DirectX::FXMVECTOR& Color_when_the_mouse_cursor_is_on = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));

	//�`����W�̐ݒ�
	void SetRECT(const int& left, const int& top, const int& right, const int& bottom)
	{
		rect = { left,top,right,bottom };
	}

	//�}�E�X�J�[�\�����͈͂ɓ������Ƃ�
	const bool When_the_mouse_cursor_enters_the_range();
};