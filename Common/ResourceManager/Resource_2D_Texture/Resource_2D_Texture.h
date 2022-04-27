#pragma once
#include"Texture_2D_Type.h"
#include<map>
class Resource_2D_Texture
{
private:

	//2Dのテクスチャ―の配列
	std::map<TEXTURE2D,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mTexture;

public:

	Resource_2D_Texture() :mTexture{} {};
	~Resource_2D_Texture() {};

	//2Dのテクスチャの読み込み
	void  Read_2D_Texture();

	//2Dのテクスチャを取得
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get2DTexture(
		const TEXTURE2D& Texture);

private:

	void AddResource(const wchar_t* textureName, const TEXTURE2D& Texture);
};