#include"pch.h"
#include"DrawTexture3D.h"
#include"DeviceResources.h"

using namespace DX;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::vector<D3D11_INPUT_ELEMENT_DESC> DrawTexture3D::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//コンストラクタ
DrawTexture3D::DrawTexture3D()
	: mInputLayout()
	, blendstate()
	, mVertexShader()
	, mPixelShader()
	, mCBuffer()
	, mGeometryShader()
{

}

//デストラクタ
DrawTexture3D::~DrawTexture3D()
{

}

//初期化
void DrawTexture3D::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	auto device = pDR->GetD3DDevice();

	//入力レイアウトを作成するための準備
	const void* shaderByteCode;
	size_t byteCodeLength;

	pGI.GetAlphaTestEffect()->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	pGI.GetAlphaTestEffect()->SetReferenceAlpha(255);

	pGI.GetAlphaTestEffect()->SetVertexColorEnabled(false);//頂点カラー(off)

	//使用する頂点シェーダー情報の取得
	pGI.GetAlphaTestEffect()->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	BinaryFile HPSData = BinaryFile::LoadFile(L"Resources/Shaders/HoleEffect.cso");
	BinaryFile MPSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeEffect.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		mInputLayout.ReleaseAndGetAddressOf());

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, mVertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, mPixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	if (FAILED(device->CreatePixelShader(HPSData.GetData(), HPSData.GetSize(), NULL, mHolePixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	if (FAILED(device->CreatePixelShader(MPSData.GetData(), MPSData.GetSize(), NULL, mMeltPixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, mGeometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &mCBuffer);
}

//描画の設定
void DrawTexture3D::SetDraw(const DirectX::SimpleMath::Matrix& world)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード） 
	ID3D11SamplerState* samplers[1] = { pGI.GetCommonStates()->LinearClamp() };
	context->PSSetSamplers(0, 1, samplers);
	blendstate = pGI.GetCommonStates()->NonPremultiplied();

	CD3D11_DEFAULT default_state;

	CD3D11_BLEND_DESC bddesc(default_state);

	blendstate->GetDesc(&bddesc);
	bddesc.AlphaToCoverageEnable = TRUE;
	pDR->GetD3DDevice()->CreateBlendState(&bddesc, &blendstate);

	// 透明判定処理 
	context->OMSetBlendState(blendstate.Get(), nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する 
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// カリングは左周り（反時計回り） 
	context->RSSetState(pGI.GetCommonStates()->CullCounterClockwise());

	// 不透明のみ描画する設定 
	pGI.GetAlphaTestEffect()->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	pGI.GetAlphaTestEffect()->SetReferenceAlpha(0);
	pGI.GetAlphaTestEffect()->SetWorld(world);
	pGI.GetAlphaTestEffect()->SetView(pCm.GetView());
	pGI.GetAlphaTestEffect()->SetProjection(pCm.GetProjection());
	pGI.GetAlphaTestEffect()->Apply(context);
	context->IASetInputLayout(mInputLayout.Get());
}

//テクスチャを描画
void DrawTexture3D::DrawShader(
	const DirectX::SimpleMath::Matrix& world
	, const TEXTURE3D& Texture)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	// 頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[1] = {};

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = pCm.GetView().Transpose();
	cbuff.matProj = pCm.GetProjection().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(mColor.x, mColor.y, mColor.z, mColor.w);

	//受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	
	//画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { pGI.GetCommonStates()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//半透明描画指定
	ID3D11BlendState* blendstate = pGI.GetCommonStates()->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(pGI.GetCommonStates()->CullNone());

	//シェーダをセットする
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->PSSetShader(mPixelShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);

	//ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, pRm.Get3DTexture(Texture).GetAddressOf());
	
	//インプットレイアウトの登録
	context->IASetInputLayout(mInputLayout.Get());
	
	// 板ポリゴンを描画
	pGI.GetVertexPositionColorTexture()->Begin();
	pGI.GetVertexPositionColorTexture()->Draw(
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);

	pGI.GetVertexPositionColorTexture()->End();

	//シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
}

void DrawTexture3D::HDrawShader(
	const DirectX::SimpleMath::Matrix& world
	, const TEXTURE3D& Texture)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	// 頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[1] = {};

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = pCm.GetView().Transpose();
	cbuff.matProj = pCm.GetProjection().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(mColor.x, mColor.y, mColor.z, mColor.w);

	//受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);

	//画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { pGI.GetCommonStates()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//半透明描画指定
	ID3D11BlendState* blendstate = pGI.GetCommonStates()->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(pGI.GetCommonStates()->CullNone());

	//シェーダをセットする
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->PSSetShader(mHolePixelShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);

	//ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, pRm.Get3DTexture(Texture).GetAddressOf());

	//インプットレイアウトの登録
	context->IASetInputLayout(mInputLayout.Get());

	// 板ポリゴンを描画
	pGI.GetVertexPositionColorTexture()->Begin();
	pGI.GetVertexPositionColorTexture()->Draw(
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);

	pGI.GetVertexPositionColorTexture()->End();

	//シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
}
void DrawTexture3D::MDrawShader(
	const DirectX::SimpleMath::Matrix& world
	, const TEXTURE3D& Texture)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	// 頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[1] = {};

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = pCm.GetView().Transpose();
	cbuff.matProj = pCm.GetProjection().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(mColor.x, mColor.y, mColor.z, mColor.w);

	//受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);

	//画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { pGI.GetCommonStates()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//半透明描画指定
	ID3D11BlendState* blendstate = pGI.GetCommonStates()->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(pGI.GetCommonStates()->CullNone());

	//シェーダをセットする
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->PSSetShader(mMeltPixelShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);

	//ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, pRm.Get3DTexture(Texture).GetAddressOf());
	context->PSSetShaderResources(1, 1, pRm.Get3DTexture(TEXTURE3D::HIGHT).GetAddressOf());

	//インプットレイアウトの登録
	context->IASetInputLayout(mInputLayout.Get());

	// 板ポリゴンを描画
	pGI.GetVertexPositionColorTexture()->Begin();
	pGI.GetVertexPositionColorTexture()->Draw(
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);

	pGI.GetVertexPositionColorTexture()->End();

	//シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
}

//ビルボードの設定
void DrawTexture3D::DrawBillboard(DirectX::SimpleMath::Matrix& world)
{
	CameraParam& pCm = CameraParam::GetInstance();

	Matrix billboardMat = pCm.GetView().Invert();
	billboardMat._41 = 0;
	billboardMat._42 = 0;
	billboardMat._43 = 0;
	world *= billboardMat;
}

void DrawTexture3D::SetColor(
	  const float& color1
	, const float& color2
	, const float& color3
	, const float& color4
)
{
	mColor.x = color1;
	mColor.y = color2;
	mColor.z = color3;
	mColor.w = color4;
}