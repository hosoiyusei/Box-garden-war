#pragma once
#include<GeometricPrimitive.h>
#include"GeometryType.h"
#include<map>

class ResourceGeometry
{
private:

	//Geometry‚Ì”z—ñ
	std::map<SHAPE,std::unique_ptr<DirectX::GeometricPrimitive>> mGeometry;

public:

	ResourceGeometry() :mGeometry{} {};
	~ResourceGeometry() {};

	//Geometry‚Ì“Ç‚İ‚İ
	void  Read_Geometry();

	//Geometry‚Ìæ“¾
	const DirectX::GeometricPrimitive* GetGeometry(
		const SHAPE& shape);

private:

	void AddResource(std::unique_ptr<DirectX::GeometricPrimitive> Geometry,const SHAPE& shape);
};