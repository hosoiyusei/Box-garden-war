#include"pch.h"
#include"DrawModel.h"
#include"DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
DrawModel::DrawModel()
{

}

//デストラクタ
DrawModel::~DrawModel()
{

}

//描画
void DrawModel::Draw(
	const Matrix& world
	, const MODEL_NAME& name)
{
	GetVariousInstance& pGI = GetVariousInstance::GetInstance();
	CameraParam& pCm = CameraParam::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	pRm.GetModel(name)->Draw(
		DX::DeviceResources::GetInstance()->GetD3DDeviceContext()
		, *pGI.GetCommonStates(),world
		, pCm.GetView()
		, pCm.GetProjection());
}