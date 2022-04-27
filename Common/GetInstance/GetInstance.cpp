#include"pch.h"
#include"GetInstance.h"
#include "DeviceResources.h"

using namespace std;
using namespace DirectX;

void GetVariousInstance::Initialize()
{
	ID3D11Device1* device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	ID3D11DeviceContext1* context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	//�R�����X�e�[�g
	mpCommonStates = make_unique<CommonStates>(device);

	//�X�v���C�g�o�b�`
	mpSpriteBatch = make_unique<SpriteBatch>(context);

	//�X�v���C�g�t�H���g
	mpSpriteFont = make_unique<SpriteFont>(device, L"Resources/Fonts/mukasi.spritefont");

	//�G�t�F�N�g�t�@�N�g���[
	mpEffectFactory = make_unique<EffectFactory>(device);

	//�A���t�@�e�X�g�G�t�F�N�g
	mpAlphaTestEffect = make_unique<AlphaTestEffect>(device);

	//�o�[�e�b�N�X�|�W�V�����e�N�X�`��
	mpVertexPositionTexture = make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	//�o�[�e�b�N�X�|�W�V�����J���[�e�N�X�`��
	mpVertexPositionColorTexture = make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
}