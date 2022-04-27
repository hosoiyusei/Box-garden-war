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

//�R���X�g���N�^
DrawTexture3D::DrawTexture3D()
	: mInputLayout()
	, blendstate()
	, mVertexShader()
	, mPixelShader()
	, mCBuffer()
	, mGeometryShader()
{

}

//�f�X�g���N�^
DrawTexture3D::~DrawTexture3D()
{

}

//������
void DrawTexture3D::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	auto device = pDR->GetD3DDevice();

	//���̓��C�A�E�g���쐬���邽�߂̏���
	const void* shaderByteCode;
	size_t byteCodeLength;

	pGI.GetAlphaTestEffect()->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	pGI.GetAlphaTestEffect()->SetReferenceAlpha(255);

	pGI.GetAlphaTestEffect()->SetVertexColorEnabled(false);//���_�J���[(off)

	//�g�p���钸�_�V�F�[�_�[���̎擾
	pGI.GetAlphaTestEffect()->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	BinaryFile HPSData = BinaryFile::LoadFile(L"Resources/Shaders/HoleEffect.cso");
	BinaryFile MPSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeEffect.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		mInputLayout.ReleaseAndGetAddressOf());

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, mVertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, mPixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	if (FAILED(device->CreatePixelShader(HPSData.GetData(), HPSData.GetSize(), NULL, mHolePixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	if (FAILED(device->CreatePixelShader(MPSData.GetData(), MPSData.GetSize(), NULL, mMeltPixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, mGeometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
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

//�`��̐ݒ�
void DrawTexture3D::SetDraw(const DirectX::SimpleMath::Matrix& world)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j 
	ID3D11SamplerState* samplers[1] = { pGI.GetCommonStates()->LinearClamp() };
	context->PSSetSamplers(0, 1, samplers);
	blendstate = pGI.GetCommonStates()->NonPremultiplied();

	CD3D11_DEFAULT default_state;

	CD3D11_BLEND_DESC bddesc(default_state);

	blendstate->GetDesc(&bddesc);
	bddesc.AlphaToCoverageEnable = TRUE;
	pDR->GetD3DDevice()->CreateBlendState(&bddesc, &blendstate);

	// �������菈�� 
	context->OMSetBlendState(blendstate.Get(), nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// �J�����O�͍�����i�����v���j 
	context->RSSetState(pGI.GetCommonStates()->CullCounterClockwise());

	// �s�����̂ݕ`�悷��ݒ� 
	pGI.GetAlphaTestEffect()->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	pGI.GetAlphaTestEffect()->SetReferenceAlpha(0);
	pGI.GetAlphaTestEffect()->SetWorld(world);
	pGI.GetAlphaTestEffect()->SetView(pCm.GetView());
	pGI.GetAlphaTestEffect()->SetProjection(pCm.GetProjection());
	pGI.GetAlphaTestEffect()->Apply(context);
	context->IASetInputLayout(mInputLayout.Get());
}

//�e�N�X�`����`��
void DrawTexture3D::DrawShader(
	const DirectX::SimpleMath::Matrix& world
	, const TEXTURE3D& Texture)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	auto context = pDR->GetD3DDeviceContext();

	// ���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[1] = {};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = pCm.GetView().Transpose();
	cbuff.matProj = pCm.GetProjection().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(mColor.x, mColor.y, mColor.z, mColor.w);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	
	//�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { pGI.GetCommonStates()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�������`��w��
	ID3D11BlendState* blendstate = pGI.GetCommonStates()->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(pGI.GetCommonStates()->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->PSSetShader(mPixelShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, pRm.Get3DTexture(Texture).GetAddressOf());
	
	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(mInputLayout.Get());
	
	// �|���S����`��
	pGI.GetVertexPositionColorTexture()->Begin();
	pGI.GetVertexPositionColorTexture()->Draw(
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);

	pGI.GetVertexPositionColorTexture()->End();

	//�V�F�[�_�̓o�^���������Ă���
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

	// ���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[1] = {};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = pCm.GetView().Transpose();
	cbuff.matProj = pCm.GetProjection().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(mColor.x, mColor.y, mColor.z, mColor.w);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);

	//�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { pGI.GetCommonStates()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�������`��w��
	ID3D11BlendState* blendstate = pGI.GetCommonStates()->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(pGI.GetCommonStates()->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->PSSetShader(mHolePixelShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, pRm.Get3DTexture(Texture).GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(mInputLayout.Get());

	// �|���S����`��
	pGI.GetVertexPositionColorTexture()->Begin();
	pGI.GetVertexPositionColorTexture()->Draw(
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);

	pGI.GetVertexPositionColorTexture()->End();

	//�V�F�[�_�̓o�^���������Ă���
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

	// ���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[1] = {};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = pCm.GetView().Transpose();
	cbuff.matProj = pCm.GetProjection().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(mColor.x, mColor.y, mColor.z, mColor.w);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);

	//�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { pGI.GetCommonStates()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�������`��w��
	ID3D11BlendState* blendstate = pGI.GetCommonStates()->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(pGI.GetCommonStates()->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(pGI.GetCommonStates()->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->PSSetShader(mMeltPixelShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, pRm.Get3DTexture(Texture).GetAddressOf());
	context->PSSetShaderResources(1, 1, pRm.Get3DTexture(TEXTURE3D::HIGHT).GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(mInputLayout.Get());

	// �|���S����`��
	pGI.GetVertexPositionColorTexture()->Begin();
	pGI.GetVertexPositionColorTexture()->Draw(
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);

	pGI.GetVertexPositionColorTexture()->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
}

//�r���{�[�h�̐ݒ�
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