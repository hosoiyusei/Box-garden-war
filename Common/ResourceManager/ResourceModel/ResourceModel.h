#pragma once
#include <Model.h>
#include"ModelType.h"
#include<map>

class ResourceModel
{
private:

	//モデルの配列
	std::map<MODEL_NAME,std::unique_ptr<DirectX::Model>> mModelObject;

public:

	ResourceModel() :mModelObject{} {};
	~ResourceModel() {};

	//モデルの読み込み
	void Read_Model();

	//モデルを取得
	const DirectX::Model* GetModel(
		const MODEL_NAME& name);

	void SetColor(const MODEL_NAME& name, const  DirectX::FXMVECTOR& color);

private:

	void AddResource(const wchar_t* textureName, const MODEL_NAME& name);

	void LightOff(const MODEL_NAME& name, const  DirectX::FXMVECTOR& color);
};