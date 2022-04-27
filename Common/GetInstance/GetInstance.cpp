#include"pch.h"
#include"GetInstance.h"
#include "DeviceResources.h"

using namespace std;
using namespace DirectX;

void GetVariousInstance::Initialize()
{
	ID3D11Device1* device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	ID3D11DeviceContext1* context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	//コモンステート
	mpCommonStates = make_unique<CommonStates>(device);

	//スプライトバッチ
	mpSpriteBatch = make_unique<SpriteBatch>(context);

	//スプライトフォント
	mpSpriteFont = make_unique<SpriteFont>(device, L"Resources/Fonts/mukasi.spritefont");

	//エフェクトファクトリー
	mpEffectFactory = make_unique<EffectFactory>(device);

	//アルファテストエフェクト
	mpAlphaTestEffect = make_unique<AlphaTestEffect>(device);

	//バーテックスポジションテクスチャ
	mpVertexPositionTexture = make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	//バーテックスポジションカラーテクスチャ
	mpVertexPositionColorTexture = make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
}