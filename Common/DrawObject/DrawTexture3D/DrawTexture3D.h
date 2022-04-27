#pragma once
#include<SimpleMath.h>
#include<vector>
#include "BinaryFile.h"
#include"../../ResourceManager/ResourceManager.h"

class DrawTexture3D
{
private:

	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>mInputLayout;

	Microsoft::WRL::ComPtr<ID3D11BlendState>blendstate;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;

	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mHolePixelShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mMeltPixelShader;

	//ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer>	mCBuffer;

	//テクスチャの色
	DirectX::SimpleMath::Vector4 mColor;

public:

	//コンストラクタ
	DrawTexture3D();

	//デストラクタ
	~DrawTexture3D();

	//初期化
	void Initialize();

	//テクスチャを描画する設定をする
	void SetDraw(const DirectX::SimpleMath::Matrix& world);

	//テクスチャを描画
	void DrawShader(
		const DirectX::SimpleMath::Matrix& world
		, const TEXTURE3D& Texture);
	void HDrawShader(
		const DirectX::SimpleMath::Matrix& world
		, const TEXTURE3D& Texture);
	void MDrawShader(
		const DirectX::SimpleMath::Matrix& world
		, const TEXTURE3D& Texture);

	//テクスチャをビルボードにする
	void DrawBillboard(DirectX::SimpleMath::Matrix& world);

	void SetColor(
		  const float& color1 = 0.0f
		, const float& color2 = 0.0f
		, const float& color3 = 0.0f
		, const float& color4 = 1.0f
	);
};