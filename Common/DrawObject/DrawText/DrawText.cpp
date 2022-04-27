#include"pch.h"
#include"DrawText.h"

using namespace DirectX;

//�R���X�g���N�^
Text::Text()
{

}

//�f�X�g���N�^
Text::~Text()
{

}

//�e�L�X�g�̕`��
void Text::TextDraw(_In_z_ const wchar_t* szFileName
	, const DirectX::XMFLOAT2& Pos
	, const DirectX::FXMVECTOR& color
	, const float& Rotation
	, const float& size)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	pGI.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, pGI.GetCommonStates()->NonPremultiplied());

	wchar_t buf[32];
	swprintf_s(buf, 32, szFileName);

	pGI.GetSpriteFont()->DrawString(
		pGI.GetSpriteBatch(), buf,//�����o��
		Pos,//�\���̈ʒu
		color,//�F�̎w��
		Rotation,//��]
		DirectX::XMFLOAT2(0, 0),//�悭�킩��񂯂Ǖ\���ʒu�ύX�ł���
		size);//�T�C�Y

	pGI.GetSpriteBatch()->End();
}

//Int�^�̕`��
void Text::DrawInt(const int& i
	, const DirectX::XMFLOAT2& Pos
	, const DirectX::FXMVECTOR& color
	, const float& Rotation
	, const float& size)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	pGI.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, pGI.GetCommonStates()->NonPremultiplied());
	wchar_t buf[32];
	swprintf_s(buf, 32, L"%d", i);

	pGI.GetSpriteFont()->DrawString(
		pGI.GetSpriteBatch(), buf,//�����o��
		Pos,//�\���̈ʒu
		color,//�F�̎w��
		Rotation,//��]
		DirectX::XMFLOAT2(0, 0),//�悭�킩��񂯂Ǖ\���ʒu�ύX�ł���
		size);//�T�C�Y

	pGI.GetSpriteBatch()->End();
}

//Float�^�̕`��
void Text::DrawFloat(const float& f
	, const DirectX::XMFLOAT2& Pos
	, const DirectX::FXMVECTOR& color
	, const float& Rotation
	, const float& size)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	pGI.GetSpriteBatch()->Begin(SpriteSortMode_Deferred, pGI.GetCommonStates()->NonPremultiplied());
	wchar_t buf[32];
	swprintf_s(buf, 32, L"%f", f);

	pGI.GetSpriteFont()->DrawString(
		pGI.GetSpriteBatch(), buf,//�����o��
		Pos,//�\���̈ʒu
		color,//�F�̎w��
		Rotation,//��]
		DirectX::XMFLOAT2(0, 0),//�悭�킩��񂯂Ǖ\���ʒu�ύX�ł���
		size);//�T�C�Y

	pGI.GetSpriteBatch()->End();
}