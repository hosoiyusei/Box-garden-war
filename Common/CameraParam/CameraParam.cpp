#include"pch.h"
#include"CameraParam.h"
#include "DeviceResources.h"

void CameraParam::SetParam(const VIEW& CameraView)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// �E�B���h�E�T�C�Y�̎擾
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);
	mWorld = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Vector3    eye(CameraView.eyeX, CameraView.eyeY, CameraView.eyeZ);              // �J�����̍��W
	DirectX::SimpleMath::Vector3 target(CameraView.targetX, CameraView.targetY, CameraView.targetZ);				// �J�����̒����_
	DirectX::SimpleMath::Vector3     up(CameraView.upX, CameraView.upY, CameraView.upZ);				// �J�����̓��̌���
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);	// �Œ�J�������g��
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ��p
	float aspectRatio = width / height;							// ��ʏc����
	float nearPlane = 1.0f;                                     // �J���������ԋ߂����e��
	float farPlane = 10000.0f;                                    // �J���������ԉ������e��
	mProjection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}