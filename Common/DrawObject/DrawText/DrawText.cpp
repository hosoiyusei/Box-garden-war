#include"pch.h"
#include"DrawText.h"

using namespace DirectX;

//コンストラクタ
Text::Text()
{

}

//デストラクタ
Text::~Text()
{

}

//テキストの描画
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
		pGI.GetSpriteBatch(), buf,//文字出す
		Pos,//表示の位置
		color,//色の指定
		Rotation,//回転
		DirectX::XMFLOAT2(0, 0),//よくわからんけど表示位置変更できる
		size);//サイズ

	pGI.GetSpriteBatch()->End();
}

//Int型の描画
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
		pGI.GetSpriteBatch(), buf,//文字出す
		Pos,//表示の位置
		color,//色の指定
		Rotation,//回転
		DirectX::XMFLOAT2(0, 0),//よくわからんけど表示位置変更できる
		size);//サイズ

	pGI.GetSpriteBatch()->End();
}

//Float型の描画
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
		pGI.GetSpriteBatch(), buf,//文字出す
		Pos,//表示の位置
		color,//色の指定
		Rotation,//回転
		DirectX::XMFLOAT2(0, 0),//よくわからんけど表示位置変更できる
		size);//サイズ

	pGI.GetSpriteBatch()->End();
}