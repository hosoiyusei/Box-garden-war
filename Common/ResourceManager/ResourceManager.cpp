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

//�R���X�g���N�^
ResourceManager::ResourceManager()
{

}

//�f�X�g���N�^
ResourceManager::~ResourceManager()
{

}

//�S�Ă̓ǂݍ���
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

//�W�I���g���[�̔z���Ԃ�
const DirectX::GeometricPrimitive* ResourceManager::GetGeometry(
	const SHAPE& shape)
{
	return mpResourceGeometry->GetGeometry(shape);
}

//���f���̔z���Ԃ�
const DirectX::Model* ResourceManager::GetModel(
	const MODEL_NAME& name)
{
	return mpResourceModel->GetModel(name);
}

//2D�̃e�N�X�`����Ԃ�
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& ResourceManager::Get2DTexture(
	const TEXTURE2D& Texture)
{
	return mpResource_2D_Texture->Get2DTexture(Texture);
}

//�e�N�X�`����Ԃ�
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& ResourceManager::Get3DTexture(
	const TEXTURE3D& Texture)
{
	return mpResource_3D_Texture->Get3DTexture(Texture);
}

//�T�E���h�̔ԍ���Ԃ�
const int& ResourceManager::GetBGM(
	const SOUND_BGM& sound)
{
	return mpResourceSound->GetBGM(sound);
}

//�T�E���h�̎擾
const int& ResourceManager::GetSE(
	const SOUND_SE& sound)
{
	return mpResourceSound->GetSE(sound);
}

//�T�E���h�̖��O���擾
const std::vector<const wchar_t*>& ResourceManager::GetSoundName()
{
	return mpResourceSound->GetSoundName();
}