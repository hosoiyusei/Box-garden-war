#include"pch.h"
#include"Button.h"

#pragma warning(disable:26812)

//�}�E�X������Ă��邩�̔���
const bool Button::Determining_if_the_mouse_is_on()
{
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	int left = static_cast<int>(rect.left);
	int right = static_cast<int>(rect.right);
	int top = static_cast<int>(rect.top);
	int bottom = static_cast<int>(rect.bottom);

	if (
		left < mouseX &&
		right > mouseX &&
		top < mouseY &&
		bottom > mouseY &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		return true;
	}

	return false;
}

void Button::DrawButton(
	const RECT& texture_size
	, const TEXTURE2D& button_texture
	, _In_z_ const wchar_t* szFileName
	, const DirectX::XMFLOAT2& sentence_position_x
	, const DirectX::FXMVECTOR& color
	, const float& sentence_size
	, const DirectX::FXMVECTOR& button_color
	, const DirectX::FXMVECTOR& Color_when_the_mouse_cursor_is_on)
{
	DrawManager& pObject = DrawManager::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;
	RECT test = { 0,0,100,100 };

	int left = static_cast<int>(rect.left);
	int right = static_cast<int>(rect.right);
	int top = static_cast<int>(rect.top);
	int bottom = static_cast<int>(rect.bottom);

	if (
		left < mouseX &&
		right > mouseX &&
		top < mouseY &&
		bottom > mouseY)
	{
		//�͈͓��Ȃ�F��ς���
		pObject.GetTexture2D()->Draw(button_texture, texture_size, rect, Color_when_the_mouse_cursor_is_on);
	}
	else
	{
		pObject.GetTexture2D()->Draw(button_texture, texture_size, rect, button_color);
	}

	pObject.GetText()->TextDraw(
		szFileName
		, DirectX::XMFLOAT2(left + sentence_position_x.x, top + sentence_position_x.y)
		, color
		, 0.0f
		, sentence_size
	);
}

//�}�E�X�J�[�\�����͈͂ɓ������Ƃ�
const bool Button::When_the_mouse_cursor_enters_the_range()
{
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	int left = static_cast<int>(rect.left);
	int right = static_cast<int>(rect.right);
	int top = static_cast<int>(rect.top);
	int bottom = static_cast<int>(rect.bottom);

	if (
		left < mouseX &&
		right > mouseX &&
		top < mouseY &&
		bottom > mouseY )
	{
		return true;
	}

	return false;
}