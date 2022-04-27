#include"pch.h"
#include"ResourceModel.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//モデルの読み込み
void ResourceModel::Read_Model()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	auto device = pDR->GetD3DDevice();

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
	//モデルの杖
	AddResource(L"Resources/Models/Wand.CMO", MODEL_NAME::WAND);
	//モデルの箒
	AddResource(L"Resources/Models/Broom.CMO", MODEL_NAME::BROOM);
	//モデルの王冠
	AddResource(L"Resources/Models/Crown.CMO", MODEL_NAME::CROWN);
	//モデルの天球
	AddResource(L"Resources/Models/SkySphere.CMO", MODEL_NAME::SKY);
	//天球のlightingをなくす
	LightOff(MODEL_NAME::SKY, DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f));
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