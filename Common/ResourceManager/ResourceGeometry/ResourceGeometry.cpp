#include"pch.h"
#include"ResourceGeometry.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Geometry‚Ì“Ç‚İ‚İ
void  ResourceGeometry::Read_Geometry()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	//Geometry‚ÌƒLƒ…[ƒu
	AddResource(GeometricPrimitive::CreateCube(context), SHAPE::CUBE);

	//Geometry‚ÌGeoSphere
	AddResource(GeometricPrimitive::CreateGeoSphere(context), SHAPE::GEOSPHERE);

	//Geometry‚ÌSphere
	AddResource(GeometricPrimitive::CreateSphere(context), SHAPE::SPHERE);

	//Geometry‚ÌCone
	AddResource(GeometricPrimitive::CreateCone(context), SHAPE::CONE);

	//Geometry‚ÌCylinder
	AddResource(GeometricPrimitive::CreateCylinder(context), SHAPE::CYLINDER);

	//Geometry‚ÌTorus
	AddResource(GeometricPrimitive::CreateTorus(context), SHAPE::TORUS);
}

//Geometry‚Ìæ“¾
const DirectX::GeometricPrimitive* ResourceGeometry::GetGeometry(
	const SHAPE& shape)
{
	return mGeometry[shape].get();
}

void ResourceGeometry::AddResource(std::unique_ptr<DirectX::GeometricPrimitive> Geometry, const SHAPE& shape)
{
	mGeometry[shape] = std::move(Geometry);
}