#include"pch.h"
#include"DrawTexture2D.h"

using namespace DirectX;

//コンストラクタ
DrawTexture2D::DrawTexture2D()
{

}

//デストラクタ
DrawTexture2D::~DrawTexture2D()
{

}

//描画
void DrawTexture2D::Draw(
	  const TEXTURE2D& Texture
	, const RECT& recr
	, const RECT& recr2
	, const FXMVECTOR& color
	, const float& Rotation)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();
	
	pGI.GetSpriteBatch()->Begin(
		SpriteSortMode_Deferred
		, pGI.GetCommonStates()->NonPremultiplied());

	pGI.GetSpriteBatch()->Draw(
		pRm.Get2DTexture(Texture).Get(),
		recr2,//表示する座標
		&recr,//切り取り範囲
		color,//色
		Rotation);//回転
	pGI.GetSpriteBatch()->End();
}