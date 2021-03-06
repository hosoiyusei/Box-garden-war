#pragma once
#include<GeometricPrimitive.h>
#include"GeometryType.h"
#include<map>

class ResourceGeometry
{
private:

	//Geometryの配列
	std::map<SHAPE,std::unique_ptr<DirectX::GeometricPrimitive>> mGeometry;

public:

	ResourceGeometry() :mGeometry{} {};
	~ResourceGeometry() {};

	//Geometryの読み込み
	void  Read_Geometry();

	//Geometryの取得
	const DirectX::GeometricPrimitive* GetGeometry(
		const SHAPE& shape);

private:

	void AddResource(std::unique_ptr<DirectX::GeometricPrimitive> Geometry,const SHAPE& shape);
};