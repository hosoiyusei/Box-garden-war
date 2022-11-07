#pragma once
#include <Model.h>
#include<GeometricPrimitive.h>

#include"ResourceGeometry/GeometryType.h"
#include"ResourceModel/ModelType.h"
#include"Resource_2D_Texture/Texture_2D_Type.h"
#include"Resource_3D_Texture/Texture_3D_Type.h"
#include"ResourceSound/SoundType.h"
#include"../Singleton.h"
#include"ResourceModel/ResourceModel.h"

//前方宣言
class ResourceGeometry;
class Resource_2D_Texture;
class Resource_3D_Texture;
class ResourceSound;

class ResourceManager : public Singleton<ResourceManager>
{
private:

	//Geometryのリソース
	std::unique_ptr<ResourceGeometry> mpResourceGeometry;

	//モデルのリソース
	std::unique_ptr<ResourceModel> mpResourceModel;

	//2Dのテクスチャのリソース
	std::unique_ptr<Resource_2D_Texture> mpResource_2D_Texture;

	//3Dのテクスチャのリソース
	std::unique_ptr<Resource_3D_Texture> mpResource_3D_Texture;

	//サウンドのリソース
	std::unique_ptr<ResourceSound> mpResourceSound;

public:

	//コンストラクタ
	ResourceManager();
	//デストラクタ
	~ResourceManager();

	//全て読み込み
	void AllRead();

	//Geometryの取得
	const DirectX::GeometricPrimitive* GetGeometry(
		const SHAPE& shape);

	//モデルを取得
	const DirectX::Model* GetModel(
		const MODEL_NAME& name);

	//2Dのテクスチャを取得
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get2DTexture(
		const TEXTURE2D& Texture);

	//3Dのテクスチャを取得
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get3DTexture(
		const TEXTURE3D& Texture);

	//サウンドの取得
	const int GetBGM(
		const SOUND_BGM& sound);

	//サウンドの取得
	const int GetSE(
		const SOUND_SE& sound);

	//サウンドの名前を取得
	const std::vector<const wchar_t*>& GetSoundName();

	ResourceModel* GetResourceModel() { return mpResourceModel.get(); }
};