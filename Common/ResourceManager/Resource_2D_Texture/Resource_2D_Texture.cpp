#include"pch.h"
#include"Resource_2D_Texture.h"
#include<WICTextureLoader.h>
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//2Dのテクスチャの読み込み
void Resource_2D_Texture::Read_2D_Texture()
{
	AddResource(L"Resources/Textures/Window.png", TEXTURE2D::WINDOW);
	AddResource(L"Resources/Textures/Plus.png", TEXTURE2D::PLUS);
	AddResource(L"Resources/Textures/Minus.png", TEXTURE2D::MINUS);
	AddResource(L"Resources/Textures/Sword.png", TEXTURE2D::SWORD);
	AddResource(L"Resources/Textures/BowAndArrow.png", TEXTURE2D::BOW_AND_ARROW);
	AddResource(L"Resources/Textures/Gun.png", TEXTURE2D::GUN);
	//AddResource(L"Resources/Textures/MagicWand.png", TEXTURE2D::MAGICWAND);
	AddResource(L"Resources/Textures/Cannon.png", TEXTURE2D::CANNON);
	AddResource(L"Resources/Textures/Test.png", TEXTURE2D::TEST);
	AddResource(L"Resources/Textures/PowerUp.png", TEXTURE2D::POWERUP);
	AddResource(L"Resources/Textures/Reproduction.png", TEXTURE2D::REPRODUCTION);
	AddResource(L"Resources/Textures/FastForward.png", TEXTURE2D::FASTFORWRD);
	AddResource(L"Resources/Textures/Pause.png", TEXTURE2D::PAUSE);
	AddResource(L"Resources/Textures/Execution.png", TEXTURE2D::EXECUTION);
	AddResource(L"Resources/Textures/Title.png", TEXTURE2D::TITLE);
	AddResource(L"Resources/Textures/Shogun.png", TEXTURE2D::SHOGUN);
	AddResource(L"Resources/Textures/Pit.png", TEXTURE2D::PIT);
	AddResource(L"Resources/Textures/Mallet.png", TEXTURE2D::MALLET);
	AddResource(L"Resources/Textures/Money.png", TEXTURE2D::MONEY);
	AddResource(L"Resources/Textures/ti.png", TEXTURE2D::TI);
	AddResource(L"Resources/Textures/kuu.png", TEXTURE2D::KUU);
	AddResource(L"Resources/Textures/victory2.png", TEXTURE2D::VECTORY);
	AddResource(L"Resources/Textures/defeat2.png", TEXTURE2D::DEFEAT);
	AddResource(L"Resources/Textures/Wall.jpg", TEXTURE2D::WALL);
	AddResource(L"Resources/Textures/num.png", TEXTURE2D::NUM);
	AddResource(L"Resources/Textures/Gage.png", TEXTURE2D::GAGE);
	AddResource(L"Resources/Textures/Gage_Frame.png", TEXTURE2D::GAGE_FRAME);
	AddResource(L"Resources/Textures/Target2.png", TEXTURE2D::TARGET);
	AddResource(L"Resources/Textures/Tutorial.png", TEXTURE2D::TUTORIAL);
	AddResource(L"Resources/Textures/MaxFastForward.png", TEXTURE2D::MAXFASTFORWARD);
	AddResource(L"Resources/Textures/Heart.png", TEXTURE2D::HEART);
	AddResource(L"Resources/Textures/Garbagecan.png", TEXTURE2D::GARBAGECAN);
	AddResource(L"Resources/Textures/waruikaoIcon.png", TEXTURE2D::human);
	AddResource(L"Resources/Textures/gear.png", TEXTURE2D::GEAR);
}

//2Dのテクスチャを返す
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Resource_2D_Texture::Get2DTexture(
	const TEXTURE2D& Texture)
{
	return mTexture[Texture];
}

void Resource_2D_Texture::AddResource(const wchar_t* textureName, const TEXTURE2D& Texture)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto device = pDR->GetD3DDevice();

	CreateWICTextureFromFile(device, textureName, nullptr, mTexture[Texture].ReleaseAndGetAddressOf());
}