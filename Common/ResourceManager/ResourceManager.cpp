#include"pch.h"
#include"ResourceManager.h"
#include"DeviceResources.h"
#include<WICTextureLoader.h>

#include"ResourceGeometry/ResourceGeometry.h"
#include"ResourceModel/ResourceModel.h"
#include"Resource_2D_Texture/Resource_2D_Texture.h"
#include"Resource_3D_Texture/Resource_3D_Texture.h"
#include"ResourceSound/ResourceSound.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
ResourceManager::ResourceManager()
{

}

//デストラクタ
ResourceManager::~ResourceManager()
{

}

//全ての読み込み
void ResourceManager::AllRead()
{
	mpResourceGeometry = std::make_unique<ResourceGeometry>();
	mpResourceModel = std::make_unique<ResourceModel>();
	mpResource_2D_Texture = std::make_unique<Resource_2D_Texture>();
	mpResource_3D_Texture = std::make_unique<Resource_3D_Texture>();
	mpResourceSound = std::make_unique<ResourceSound>();

	mpResourceGeometry->Read_Geometry();
	mpResourceModel->Read_Model();
	mpResource_2D_Texture->Read_2D_Texture();
	mpResource_3D_Texture->Read_3D_Texture();
	mpResourceSound->Read_Sound();
}

//ジオメトリーの配列を返す
const DirectX::GeometricPrimitive* ResourceManager::GetGeometry(
	const SHAPE& shape)
{
	return mpResourceGeometry->GetGeometry(shape);
}

//モデルの配列を返す
const DirectX::Model* ResourceManager::GetModel(
	const MODEL_NAME& name)
{
	return mpResourceModel->GetModel(name);
}

//2Dのテクスチャを返す
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& ResourceManager::Get2DTexture(
	const TEXTURE2D& Texture)
{
	return mpResource_2D_Texture->Get2DTexture(Texture);
}

//テクスチャを返す
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& ResourceManager::Get3DTexture(
	const TEXTURE3D& Texture)
{
	return mpResource_3D_Texture->Get3DTexture(Texture);
}

//サウンドの番号を返す
const int& ResourceManager::GetBGM(
	const SOUND_BGM& sound)
{
	return mpResourceSound->GetBGM(sound);
}

//サウンドの取得
const int& ResourceManager::GetSE(
	const SOUND_SE& sound)
{
	return mpResourceSound->GetSE(sound);
}

//サウンドの名前を取得
const std::vector<const wchar_t*>& ResourceManager::GetSoundName()
{
	return mpResourceSound->GetSoundName();
}