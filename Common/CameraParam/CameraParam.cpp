#include"pch.h"
#include"CameraParam.h"
#include "DeviceResources.h"

void CameraParam::SetParam(const VIEW& CameraView)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// ウィンドウサイズの取得
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);
	mWorld = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Vector3    eye(CameraView.eyeX, CameraView.eyeY, CameraView.eyeZ);              // カメラの座標
	DirectX::SimpleMath::Vector3 target(CameraView.targetX, CameraView.targetY, CameraView.targetZ);				// カメラの注視点
	DirectX::SimpleMath::Vector3     up(CameraView.upX, CameraView.upY, CameraView.upZ);				// カメラの頭の向き
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);	// 固定カメラを使う
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 画角
	float aspectRatio = width / height;							// 画面縦横比
	float nearPlane = 1.0f;                                     // カメラから一番近い投影面
	float farPlane = 10000.0f;                                    // カメラから一番遠い投影面
	mProjection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}