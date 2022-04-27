#include"pch.h"
#include"DrawGeometry.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
DrawGeometry::DrawGeometry()
{

}

//デストラクタ
DrawGeometry::~DrawGeometry()
{
	
}

//描画
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

//描画(カラー)
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