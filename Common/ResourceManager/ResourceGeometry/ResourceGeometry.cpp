#include"pch.h"
#include"ResourceGeometry.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Geometry�̓ǂݍ���
void  ResourceGeometry::Read_Geometry()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	//Geometry�̃L���[�u
	AddResource(GeometricPrimitive::CreateCube(context), SHAPE::CUBE);

	//Geometry��GeoSphere
	AddResource(GeometricPrimitive::CreateGeoSphere(context), SHAPE::GEOSPHERE);

	//Geometry��Sphere
	AddResource(GeometricPrimitive::CreateSphere(context), SHAPE::SPHERE);

	//Geometry��Cone
	AddResource(GeometricPrimitive::CreateCone(context), SHAPE::CONE);

	//Geometry��Cylinder
	AddResource(GeometricPrimitive::CreateCylinder(context), SHAPE::CYLINDER);

	//Geometry��Torus
	AddResource(GeometricPrimitive::CreateTorus(context), SHAPE::TORUS);
}

//Geometry�̎擾
const DirectX::GeometricPrimitive* ResourceGeometry::GetGeometry(
	const SHAPE& shape)
{
	return mGeometry[shape].get();
}

void ResourceGeometry::AddResource(std::unique_ptr<DirectX::GeometricPrimitive> Geometry, const SHAPE& shape)
{
	mGeometry[shape] = std::move(Geometry);
}