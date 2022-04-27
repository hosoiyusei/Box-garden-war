#include"pch.h"
#include"DrawTexture2D.h"

using namespace DirectX;

//�R���X�g���N�^
DrawTexture2D::DrawTexture2D()
{

}

//�f�X�g���N�^
DrawTexture2D::~DrawTexture2D()
{

}

//�`��
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
		recr2,//�\��������W
		&recr,//�؂���͈�
		color,//�F
		Rotation);//��]
	pGI.GetSpriteBatch()->End();
}