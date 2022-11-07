#pragma once
#include<Mouse.h>
#include<Keyboard.h>
#include"../Singleton.h"

class InputManager : public Singleton<InputManager>
{
private:
	//�}�E�X�֘A
	std::unique_ptr<DirectX::Mouse> mMouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mButtonStateTracker;
	DirectX::Mouse::State mMouseState;
	//�L�[�{�[�h�֘A
	std::unique_ptr<DirectX::Keyboard> mKeyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> mKeyboardStateTracker;
	DirectX::Keyboard::State mKeyboardState;

public:
	InputManager()
		:mMouse()
		, mButtonStateTracker()
		, mMouseState()
		, mKeyboard()
		, mKeyboardStateTracker()
		, mKeyboardState()
	{

	}
	//������
	void Initialize();

	void Reset();

	void Update();

	//�e��Q�b�^
	const DirectX::Mouse::State& GetMouseState() { return mMouseState; }
	const DirectX::Keyboard::State& GetKeyboardState() { return mKeyboardState; }
	const DirectX::Mouse::ButtonStateTracker* GetButtonStateTracker()const { return mButtonStateTracker.get(); }
	const DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() const { return mKeyboardStateTracker.get(); }
};