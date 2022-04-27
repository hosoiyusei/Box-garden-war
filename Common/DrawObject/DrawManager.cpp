#include"pch.h"
#include"DrawManager.h"

//‰Šú‰»
void DrawManager::Initialize()
{
	mpDrawGeometry = std::make_unique<DrawGeometry>();
	mpDrawModel = std::make_unique<DrawModel>();
	mpText = std::make_unique<Text>();
	mpDrawTexture2D = std::make_unique<DrawTexture2D>();
	mpDrawTexture3D = std::make_unique<DrawTexture3D>();

	mpDrawTexture3D->Initialize();
}