#pragma once
#include"DrawGeometry/DrawGeometry.h"
#include"DrawModel/DrawModel.h"
#include"DrawText/DrawText.h"
#include"DrawTexture2D/DrawTexture2D.h"
#include"DrawTexture3D/DrawTexture3D.h"
#include"../Singleton.h"

class DrawManager : public Singleton<DrawManager>
{
private:

	std::unique_ptr<DrawGeometry> mpDrawGeometry;
	std::unique_ptr<DrawModel> mpDrawModel;
	std::unique_ptr<Text> mpText;
	std::unique_ptr<DrawTexture2D> mpDrawTexture2D;
	std::unique_ptr<DrawTexture3D> mpDrawTexture3D;

public:

	//‰Šú‰»
	void Initialize();

	//DrawGeometry‚Ìæ“¾
	DrawGeometry* GetGeometry() { return mpDrawGeometry.get(); }

	//DrawModel‚Ìæ“¾
	DrawModel* GetModel() { return mpDrawModel.get(); }

	//Text‚Ìæ“¾
	Text* GetText() { return mpText.get(); }

	//DrawTexture2D‚Ìæ“¾
	DrawTexture2D* GetTexture2D() { return mpDrawTexture2D.get(); }

	//DrawTexture3D‚Ìæ“¾
	DrawTexture3D* GetTexture3D() { return mpDrawTexture3D.get(); }
};