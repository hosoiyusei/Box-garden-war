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

	//コモンステート
	std::unique_ptr<DirectX::CommonStates> mpCommonStates;

	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> mpSpriteBatch;

	//スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> mpSpriteFont;

	//エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> mpEffectFactory;

	//アルファテストエフェクト
	std::unique_ptr<DirectX::AlphaTestEffect> mpAlphaTestEffect;

	//バーテックスポジションテクスチャ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> mpVertexPositionTexture;

	//バーテックスポジションカラーテクスチャ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> mpVertexPositionColorTexture;

public:

	//初期化
	void Initialize();

	//コモンステータスの取得
	DirectX::CommonStates* GetCommonStates() { return mpCommonStates.get(); }

	//スプライトバッチの取得
	DirectX::SpriteBatch* GetSpriteBatch() { return mpSpriteBatch.get(); }

	//スプライトフォントの取得
	DirectX::SpriteFont* GetSpriteFont() { return mpSpriteFont.get(); }

	//エフェクトファクトリーの取得
	DirectX::EffectFactory* GetEffectFactory() { return mpEffectFactory.get(); }

	//アルファテストエフェクトの取得
	DirectX::AlphaTestEffect* GetAlphaTestEffect() { return mpAlphaTestEffect.get(); }

	//バーテックスポジションテクスチャの取得
	DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>*
		GetVertexPositionTexture() { return mpVertexPositionTexture.get(); }

	//バーテックスポジションカラーテクスチャの取得
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>*
		GetVertexPositionColorTexture() { return mpVertexPositionColorTexture.get(); }
};

