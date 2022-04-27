#pragma once
#include"Texture_3D_Type.h"
#include<map>

class Resource_3D_Texture
{
private:

	//3D�̃e�N�X�`���\�̔z��
	std::map<TEXTURE3D,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>mTexture;

public:

	Resource_3D_Texture() :mTexture{} {};
	~Resource_3D_Texture() {};

	//3D�̃e�N�X�`���̓ǂݍ���
	void  Read_3D_Texture();

	//3D�̃e�N�X�`�����擾
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get3DTexture(
		const TEXTURE3D& Texture);

private:

	void AddResource(const wchar_t* textureName, const TEXTURE3D& Texture);
};