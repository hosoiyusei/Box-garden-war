#include"pch.h"
#include"InputManager.h"
#include"DeviceResources.h"

void InputManager::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	mKeyboard = std::make_unique<DirectX::Keyboard>();
	mKeyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	mMouse = std::make_unique<DirectX::Mouse>();
	mMouse->SetWindow(pDR->GetHwnd());
	mButtonStateTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

void InputManager::Reset()
{
	mMouse->ResetScrollWheelValue();
	
}

void InputManager::Update()
{
	mKeyboardState = mKeyboard->GetState();
	mKeyboardStateTracker->Update(mKeyboardState);
	mMouseState = mMouse->GetState();
	mButtonStateTracker->Update(mMouseState);
}