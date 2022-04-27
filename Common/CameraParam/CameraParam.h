#pragma once
#include<memory>
#include<SimpleMath.h>
#include"Scene/Utility.h"
#include"../Singleton.h"

class CameraParam : public Singleton<CameraParam>
{
private:

	DirectX::SimpleMath::Matrix mWorld, mView, mProjection;

public:

	//カメラの設定
	void SetParam(const VIEW& CameraView);

	//Viewの取得
	const DirectX::SimpleMath::Matrix& GetView()
	{
		return mView;
	}

	//プロジェクションの取得
	const DirectX::SimpleMath::Matrix& GetProjection()
	{
		return mProjection;
	}
};