#include"pch.h"
#include"Resource_3D_Texture.h"
#include<WICTextureLoader.h>
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//3Dのテクスチャの読み込み
void Resource_3D_Texture::Read_3D_Texture()
{
	AddResource(L"Resources/Textures/TridentLogo.png", TEXTURE3D::TRIDENTLOGO);
	AddResource(L"Resources/Textures/shadow.png", TEXTURE3D::SHADOW);
	AddResource(L"Resources/Textures/Target.png", TEXTURE3D::TARGET);
	AddResource(L"Resources/Textures/EnemyHP.png", TEXTURE3D::ENEMY_HP);
	AddResource(L"Resources/Textures/PowerUpEffect.png", TEXTURE3D::POWER_UP_EFFECT);
	AddResource(L"Resources/Textures/Pit.png", TEXTURE3D::PIT);
	AddResource(L"Resources/Textures/Mallet.png", TEXTURE3D::MALLET);
	AddResource(L"Resources/Textures/Money.png", TEXTURE3D::MONEY);
	AddResource(L"Resources/Textures/hight.jpg", TEXTURE3D::HIGHT);
	AddResource(L"Resources/Textures/victory.png", TEXTURE3D::VICTORY);
	AddResource(L"Resources/Textures/defeat.png", TEXTURE3D::DEFEAT);
	AddResource(L"Resources/Textures/Grassland.jpeg", TEXTURE3D::GRASSLAND);
	AddResource(L"Resources/Textures/land.png", TEXTURE3D::LAND);
	AddResource(L"Resources/Textures/range.png", TEXTURE3D::RANGE);
	AddResource(L"Resources/Textures/Fade3D.png", TEXTURE3D::FADE3D);
}

//テクスチャを返す
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Resource_3D_Texture::Get3DTexture(
	const TEXTURE3D& Texture)
{
	return mTexture[Texture];
}

void Resource_3D_Texture::AddResource(const wchar_t* textureName, const TEXTURE3D& Texture)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto device = pDR->GetD3DDevice();

	CreateWICTextureFromFile(device, textureName, nullptr, mTexture[Texture].ReleaseAndGetAddressOf());
}