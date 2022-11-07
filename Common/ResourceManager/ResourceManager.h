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

//�O���錾
class ResourceGeometry;
class Resource_2D_Texture;
class Resource_3D_Texture;
class ResourceSound;

class ResourceManager : public Singleton<ResourceManager>
{
private:

	//Geometry�̃��\�[�X
	std::unique_ptr<ResourceGeometry> mpResourceGeometry;

	//���f���̃��\�[�X
	std::unique_ptr<ResourceModel> mpResourceModel;

	//2D�̃e�N�X�`���̃��\�[�X
	std::unique_ptr<Resource_2D_Texture> mpResource_2D_Texture;

	//3D�̃e�N�X�`���̃��\�[�X
	std::unique_ptr<Resource_3D_Texture> mpResource_3D_Texture;

	//�T�E���h�̃��\�[�X
	std::unique_ptr<ResourceSound> mpResourceSound;

public:

	//�R���X�g���N�^
	ResourceManager();
	//�f�X�g���N�^
	~ResourceManager();

	//�S�ēǂݍ���
	void AllRead();

	//Geometry�̎擾
	const DirectX::GeometricPrimitive* GetGeometry(
		const SHAPE& shape);

	//���f�����擾
	const DirectX::Model* GetModel(
		const MODEL_NAME& name);

	//2D�̃e�N�X�`�����擾
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get2DTexture(
		const TEXTURE2D& Texture);

	//3D�̃e�N�X�`�����擾
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Get3DTexture(
		const TEXTURE3D& Texture);

	//�T�E���h�̎擾
	const int GetBGM(
		const SOUND_BGM& sound);

	//�T�E���h�̎擾
	const int GetSE(
		const SOUND_SE& sound);

	//�T�E���h�̖��O���擾
	const std::vector<const wchar_t*>& GetSoundName();

	ResourceModel* GetResourceModel() { return mpResourceModel.get(); }
};