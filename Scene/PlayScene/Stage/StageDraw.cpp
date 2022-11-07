#include"pch.h"
#include"StageDraw.h"
#include"StageRead.h"

#include"Object/Object.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
StageDraw::StageDraw()
	:mWorld()
	, mpStageRead(nullptr)
	,mpObject{}
{

}

//�f�X�g���N�^
StageDraw::~StageDraw()
{

}

//������
void StageDraw::Initialize(StageRead* pStageRead)
{
	mpStageRead = pStageRead;

	for (int y = 0; y < mpStageRead->GetVertical(); y++)
	{
		//�z��̒ǉ�
		mpObject.push_back(std::vector<std::unique_ptr<Object>>());

		for (int x = 0; x < mpStageRead->GetHorizontal(); x++)
		{
			//�z��̒ǉ�
			mpObject[y].push_back(std::make_unique<Object>());

			//������
			mpObject[y][x]->Initialize(mpStageRead->GetStageData(x, y));

			//���W�̐ݒ�
			mpObject[y][x]->SetPos(
				  static_cast<float>(x)
				, static_cast<float>(y));
		}
	}
}

//�`��
void StageDraw::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	for (int y = 0; y < mpStageRead->GetVertical(); y++)
	{
		for (int x = 0; x < mpStageRead->GetHorizontal(); x++)
		{
			//�`��
			mpObject[y][x]->Draw();
		}
	}

	Matrix world;

	world = Matrix::Identity;
	world *= Matrix::CreateScale(18.0f,18.0f,24.0f);
	world *= Matrix::CreateTranslation(
		static_cast<float>(mpStageRead->GetHorizontal()) / 2.0f, -5.0f
		, static_cast<float>(mpStageRead->GetVertical()) / 2.0f);
	pObject.GetModel()->Draw(world, MODEL_NAME::BOX);
}

//�v���C���[�̃}�E�X���C�L���X�g�̓����蔻��
const DirectX::SimpleMath::Vector3 StageDraw::ObjectCollision(
	const Vector3& playerCapsule)
{
	for (int y = 0; y < mpStageRead->GetVertical(); y++)
	{
		for (int x = 0; x < mpStageRead->GetHorizontal(); x++)
		{
			if (mpObject[y][x]->GetPos().x + 0.5f > playerCapsule.x &&
				mpObject[y][x]->GetPos().x - 0.5f < playerCapsule.x &&
				mpObject[y][x]->GetPos().z + 0.5f > playerCapsule.z &&
				mpObject[y][x]->GetPos().z - 0.5f < playerCapsule.z)
			{
				//�I�u�W�F�N�g�̍��W��Ԃ�
				return mpObject[y][x]->GetPos();

				break;
			}
		}
	}

	return Vector3(0.0f,0.1f,0.0f);
}