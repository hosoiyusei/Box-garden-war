#include"pch.h"
#include"ResourceModel.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//モデルの読み込み
void ResourceModel::Read_Model()
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	//読み込むファイル先を指定
	pGI.GetEffectFactory()->SetDirectory(L"Resources/Models");

	//モデルの剣
	AddResource(L"Resources/Models/Sword.CMO", MODEL_NAME::SWORD);
	//モデルの弓
	AddResource(L"Resources/Models/Bow.CMO", MODEL_NAME::BOW);
	//モデルの矢
	AddResource(L"Resources/Models/Arrow.CMO", MODEL_NAME::ARROW);
	//モデルの銃
	AddResource(L"Resources/Models/Gun.CMO", MODEL_NAME::GUN);
	//モデルの箒
	AddResource(L"Resources/Models/Broom.CMO", MODEL_NAME::BROOM);
	//モデルの王冠
	AddResource(L"Resources/Models/Clown.CMO", MODEL_NAME::CROWN);
	//モデルの天球
	AddResource(L"Resources/Models/SkySphere.CMO", MODEL_NAME::SKY);
	//ヘルメット
	AddResource(L"Resources/Models/Helmet.CMO", MODEL_NAME::HELMET);
	//マスク
	AddResource(L"Resources/Models/Mask.CMO", MODEL_NAME::MASK);
	//魔法使いの帽子
	AddResource(L"Resources/Models/Magichat.CMO", MODEL_NAME::MAGICHAT);

	AddResource(L"Resources/Models/tree.CMO", MODEL_NAME::tree);

	AddResource(L"Resources/Models/House.CMO", MODEL_NAME::HOUSE);

	AddResource(L"Resources/Models/atyahatto.CMO", MODEL_NAME::HAT);

	AddResource(L"Resources/Models/gun_hat.CMO", MODEL_NAME::GUNHAT);

	AddResource(L"Resources/Models/Cardboardbox.CMO", MODEL_NAME::BOX);

	
	//天球のlightingをなくす
	LightOff(MODEL_NAME::SKY, Color(1.0f, 1.0f, 1.0f));

	LightOff(MODEL_NAME::HOUSE, Color(1.0f, 1.0f, 1.0f));

	SetColor(MODEL_NAME::BOX, Colors::SandyBrown * 0.7f);

	SetColor(MODEL_NAME::SWORD, Colors::Green * 1.7f);

	SetColor(MODEL_NAME::ARROW, Colors::Red * 2.0f);
}

//モデルの配列を返す
const Model* ResourceModel::GetModel(
	const MODEL_NAME& name)
{
	return mModelObject[name].get();
}

void ResourceModel::AddResource(const wchar_t* textureName, const MODEL_NAME& name)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	auto device = pDR->GetD3DDevice();

	//モデルの剣
	mModelObject[name] = (Model::CreateFromCMO(device, textureName, *pGI.GetEffectFactory()));
}

void ResourceModel::LightOff(const MODEL_NAME& model, const  DirectX::FXMVECTOR& color)
{
	//あれば実行
	if (mModelObject.find(model) != mModelObject.end())
	{
		mModelObject[model]->UpdateEffects([&](IEffect* effect) {
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				// ライトの影響をなくす
				lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// エミッション色を白に設定する
				basicEffect->SetEmissiveColor(color);
			}
			});
	}
}

void ResourceModel::SetColor(const MODEL_NAME& model, const  FXMVECTOR& color)
{
	//あれば実行
	if (mModelObject.find(model) != mModelObject.end())
	{
		mModelObject[model]->UpdateEffects([&](IEffect* effect) {
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// エミッション色を白に設定する
				basicEffect->SetEmissiveColor(color);
			}
			});
	}
}