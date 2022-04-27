#pragma once
#include<GeometricPrimitive.h>
#include"GeometryType.h"
#include<map>

class ResourceGeometry
{
private:

	//Geometry�̔z��
	std::map<SHAPE,std::unique_ptr<DirectX::GeometricPrimitive>> mGeometry;

public:

	ResourceGeometry() :mGeometry{} {};
	~ResourceGeometry() {};

	//Geometry�̓ǂݍ���
	void  Read_Geometry();

	//Geometry�̎擾
	const DirectX::GeometricPrimitive* GetGeometry(
		const SHAPE& shape);

private:

	void AddResource(std::unique_ptr<DirectX::GeometricPrimitive> Geometry,const SHAPE& shape);
};