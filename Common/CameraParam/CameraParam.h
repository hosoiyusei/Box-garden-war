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

	//�J�����̐ݒ�
	void SetParam(const VIEW& CameraView);

	//View�̎擾
	const DirectX::SimpleMath::Matrix& GetView()
	{
		return mView;
	}

	//�v���W�F�N�V�����̎擾
	const DirectX::SimpleMath::Matrix& GetProjection()
	{
		return mProjection;
	}
};