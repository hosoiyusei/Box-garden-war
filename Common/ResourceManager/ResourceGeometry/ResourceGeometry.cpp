#include"pch.h"
#include"ResourceGeometry.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Geometryの読み込み
void  ResourceGeometry::Read_Geometry()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	//Geometryのキューブ
	AddResource(GeometricPrimitive::CreateCube(context), SHAPE::CUBE);

	//GeometryのGeoSphere
	AddResource(GeometricPrimitive::CreateGeoSphere(context), SHAPE::GEOSPHERE);

	//GeometryのSphere
	AddResource(GeometricPrimitive::CreateSphere(context), SHAPE::SPHERE);

	//GeometryのCone
	AddResource(GeometricPrimitive::CreateCone(context), SHAPE::CONE);

	//GeometryのCylinder
	AddResource(GeometricPrimitive::CreateCylinder(context), SHAPE::CYLINDER);

	//GeometryのTorus
	AddResource(GeometricPrimitive::CreateTorus(context), SHAPE::TORUS);
}

//Geometryの取得
const DirectX::GeometricPrimitive* ResourceGeometry::GetGeometry(
	const SHAPE& shape)
{
	return mGeometry[shape].get();
}

void ResourceGeometry::AddResource(std::unique_ptr<DirectX::GeometricPrimitive> Geometry, const SHAPE& shape)
{
	mGeometry[shape] = std::move(Geometry);
}