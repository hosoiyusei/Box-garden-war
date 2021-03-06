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

	//初期化
	void Initialize();

	//DrawGeometryの取得
	DrawGeometry* GetGeometry() { return mpDrawGeometry.get(); }

	//DrawModelの取得
	DrawModel* GetModel() { return mpDrawModel.get(); }

	//Textの取得
	Text* GetText() { return mpText.get(); }

	//DrawTexture2Dの取得
	DrawTexture2D* GetTexture2D() { return mpDrawTexture2D.get(); }

	//DrawTexture3Dの取得
	DrawTexture3D* GetTexture3D() { return mpDrawTexture3D.get(); }
};