#pragma once
#include<Mouse.h>
#include<Keyboard.h>
#include"../Singleton.h"

class InputManager : public Singleton<InputManager>
{
private:
	//マウス関連
	std::unique_ptr<DirectX::Mouse> mMouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mButtonStateTracker;
	DirectX::Mouse::State mMouseState;
	//キーボード関連
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
	//初期化
	void Initialize();

	void Reset();

	void Update();

	//各種ゲッタ
	const DirectX::Mouse::State& GetMouseState() { return mMouseState; }
	const DirectX::Keyboard::State& GetKeyboardState() { return mKeyboardState; }
	const DirectX::Mouse::ButtonStateTracker* GetButtonStateTracker()const { return mButtonStateTracker.get(); }
	const DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() const { return mKeyboardStateTracker.get(); }
};