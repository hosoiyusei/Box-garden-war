#pragma once

class Button;

class PlaySetting
{
private:

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

	bool mBackSelectFlag;

public:

	PlaySetting();
	~PlaySetting() = default;

	void Initialize();

	void Update();

	void Draw();

	const bool GetBackSelectFlag() {return mBackSelectFlag;}

	void Sound_gage_draw();

	void Setting_Update();
};