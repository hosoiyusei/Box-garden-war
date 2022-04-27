#include"pch.h"
#include"DrawGeometry.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
DrawGeometry::DrawGeometry()
{

}

//�f�X�g���N�^
DrawGeometry::~DrawGeometry()
{
	
}

//�`��
void DrawGeometry::Draw(
	const Matrix& world
	, const SHAPE& shape
	, FXMVECTOR& color)
{
	CameraParam& pCm = CameraParam::GetInstance(); 
	ResourceManager& pRm = ResourceManager::GetInstance();
	
	pRm.GetGeometry(shape)->Draw(
		world
		, pCm.GetView()
		, pCm.GetProjection()
		, color);
}

//�`��(�J���[)
void DrawGeometry::DrawSetColor(
	const Matrix& world
	, const SHAPE& shape
	, const Color& color)
{
	CameraParam& pCm = CameraParam::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	pRm.GetGeometry(shape)->Draw(
		world
		, pCm.GetView()
		, pCm.GetProjection()
		, color);
}