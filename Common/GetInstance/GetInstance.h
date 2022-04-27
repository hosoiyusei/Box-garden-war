#pragma once
#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "DirectXTK/inc/Effects.h"
#include<PrimitiveBatch.h>
#include<VertexTypes.h>
#include"../Singleton.h"

class GetVariousInstance : public Singleton<GetVariousInstance>
{	
private:

	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> mpCommonStates;

	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> mpSpriteBatch;

	//�X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> mpSpriteFont;

	//�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> mpEffectFactory;

	//�A���t�@�e�X�g�G�t�F�N�g
	std::unique_ptr<DirectX::AlphaTestEffect> mpAlphaTestEffect;

	//�o�[�e�b�N�X�|�W�V�����e�N�X�`��
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> mpVertexPositionTexture;

	//�o�[�e�b�N�X�|�W�V�����J���[�e�N�X�`��
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> mpVertexPositionColorTexture;

public:

	//������
	void Initialize();

	//�R�����X�e�[�^�X�̎擾
	DirectX::CommonStates* GetCommonStates() { return mpCommonStates.get(); }

	//�X�v���C�g�o�b�`�̎擾
	DirectX::SpriteBatch* GetSpriteBatch() { return mpSpriteBatch.get(); }

	//�X�v���C�g�t�H���g�̎擾
	DirectX::SpriteFont* GetSpriteFont() { return mpSpriteFont.get(); }

	//�G�t�F�N�g�t�@�N�g���[�̎擾
	DirectX::EffectFactory* GetEffectFactory() { return mpEffectFactory.get(); }

	//�A���t�@�e�X�g�G�t�F�N�g�̎擾
	DirectX::AlphaTestEffect* GetAlphaTestEffect() { return mpAlphaTestEffect.get(); }

	//�o�[�e�b�N�X�|�W�V�����e�N�X�`���̎擾
	DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>*
		GetVertexPositionTexture() { return mpVertexPositionTexture.get(); }

	//�o�[�e�b�N�X�|�W�V�����J���[�e�N�X�`���̎擾
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>*
		GetVertexPositionColorTexture() { return mpVertexPositionColorTexture.get(); }
};

