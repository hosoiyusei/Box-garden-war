#pragma once
#include <Model.h>
#include"ModelType.h"
#include<map>

class ResourceModel
{
private:

	//���f���̔z��
	std::map<MODEL_NAME,std::unique_ptr<DirectX::Model>> mModelObject;

public:

	ResourceModel() :mModelObject{} {};
	~ResourceModel() {};

	//���f���̓ǂݍ���
	void Read_Model();

	//���f�����擾
	const DirectX::Model* GetModel(
		const MODEL_NAME& name);

	void SetColor(const MODEL_NAME& name, const  DirectX::FXMVECTOR& color);

private:

	void AddResource(const wchar_t* textureName, const MODEL_NAME& name);

	void LightOff(const MODEL_NAME& name, const  DirectX::FXMVECTOR& color);
};