#include"pch.h"
#include"ResourceModel.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//���f���̓ǂݍ���
void ResourceModel::Read_Model()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();

	auto device = pDR->GetD3DDevice();

	//�ǂݍ��ރt�@�C������w��
	pGI.GetEffectFactory()->SetDirectory(L"Resources/Models");

	//���f���̌�
	AddResource(L"Resources/Models/Sword.CMO", MODEL_NAME::SWORD);
	//���f���̋|
	AddResource(L"Resources/Models/Bow.CMO", MODEL_NAME::BOW);
	//���f���̖�
	AddResource(L"Resources/Models/Arrow.CMO", MODEL_NAME::ARROW);
	//���f���̏e
	AddResource(L"Resources/Models/Gun.CMO", MODEL_NAME::GUN);
	//���f���̏�
	AddResource(L"Resources/Models/Wand.CMO", MODEL_NAME::WAND);
	//���f�����
	AddResource(L"Resources/Models/Broom.CMO", MODEL_NAME::BROOM);
	//���f���̉���
	AddResource(L"Resources/Models/Crown.CMO", MODEL_NAME::CROWN);
	//���f���̓V��
	AddResource(L"Resources/Models/SkySphere.CMO", MODEL_NAME::SKY);
	//�V����lighting���Ȃ���
	LightOff(MODEL_NAME::SKY, DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f));
}

//���f���̔z���Ԃ�
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

	//���f���̌�
	mModelObject[name] = (Model::CreateFromCMO(device, textureName, *pGI.GetEffectFactory()));
}

void ResourceModel::LightOff(const MODEL_NAME& model, const  DirectX::FXMVECTOR& color)
{
	//����Ύ��s
	if (mModelObject.find(model) != mModelObject.end())
	{
		mModelObject[model]->UpdateEffects([&](IEffect* effect) {
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				// ���C�g�̉e�����Ȃ���
				lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �G�~�b�V�����F�𔒂ɐݒ肷��
				basicEffect->SetEmissiveColor(color);
			}
			});
	}
}