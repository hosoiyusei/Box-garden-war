#pragma once
#include"Texture_3D_Type.h"
#include<map>

class Resource_3D_Texture
{
private:

	//3Dのテクスチャ―の配列
	std::map<TEXTURE3D,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>mTexture;

public:

	Resource_3D_Texture() :mTexture{} {};
	~Resource_3D_Texture() {};

	//3Dのテクスチャの読み込み
	void  Read_3D_Texture();

	//3Dのテクスチャを取得
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get3DTexture(
		const TEXTURE3D& Texture);

private:

	void AddResource(const wchar_t* textureName, const TEXTURE3D& Texture);
};