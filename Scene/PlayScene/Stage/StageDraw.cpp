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
	for (int y = 0; y < mpStageRead->GetVertical(); y++)
	{
		for (int x = 0; x < mpStageRead->GetHorizontal(); x++)
		{
			//�`��
			mpObject[y][x]->Draw();
		}
	}
}

//�v���C���[�̃}�E�X���C�L���X�g�̓����蔻��
const DirectX::SimpleMath::Vector3& StageDraw::ObjectCollision(
	const Capsule& playerCapsule)
{
	for (int y = 0; y < mpStageRead->GetVertical(); y++)
	{
		for (int x = 0; x < mpStageRead->GetHorizontal(); x++)
		{
			//�}�E�X�̃��C�Ɠ������Ă�����
			if (mpObject[y][x]->CheckHitCollision(playerCapsule) == true)
			{
				//�I�u�W�F�N�g�̍��W��Ԃ�
				return mpObject[y][x]->GetPos();

				break;
			}
		}
	}

	//�������Ă��Ȃ�������K���ȍ��W��Ԃ�
	//return Vector3(0.0f, 0.0f, 10000);
}