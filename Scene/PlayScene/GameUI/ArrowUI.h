#pragma once

class Button;

class ArrowUI
{
private:

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

public:

	ArrowUI();
	~ArrowUI() = default;

	//‰Šú‰»
	void Initialize();

	//•`‰æ
	void Draw();
};