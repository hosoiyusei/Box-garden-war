#pragma once
#include<SimpleMath.h>
#include<vector>
#include "BinaryFile.h"
#include"../../ResourceManager/ResourceManager.h"

class DrawTexture3D
{
private:

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>mInputLayout;

	Microsoft::WRL::ComPtr<ID3D11BlendState>blendstate;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;

	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mHolePixelShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mMeltPixelShader;

	//�W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer>	mCBuffer;

	//�e�N�X�`���̐F
	DirectX::SimpleMath::Vector4 mColor;

public:

	//�R���X�g���N�^
	DrawTexture3D();

	//�f�X�g���N�^
	~DrawTexture3D();

	//������
	void Initialize();

	//�e�N�X�`����`�悷��ݒ������
	void SetDraw(const DirectX::SimpleMath::Matrix& world);

	//�e�N�X�`����`��
	void DrawShader(
		const DirectX::SimpleMath::Matrix& world
		, const TEXTURE3D& Texture);
	void HDrawShader(
		const DirectX::SimpleMath::Matrix& world
		, const TEXTURE3D& Texture);
	void MDrawShader(
		const DirectX::SimpleMath::Matrix& world
		, const TEXTURE3D& Texture);

	//�e�N�X�`�����r���{�[�h�ɂ���
	void DrawBillboard(DirectX::SimpleMath::Matrix& world);

	void SetColor(
		  const float& color1 = 0.0f
		, const float& color2 = 0.0f
		, const float& color3 = 0.0f
		, const float& color4 = 1.0f
	);
};