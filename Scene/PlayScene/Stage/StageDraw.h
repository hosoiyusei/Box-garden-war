#pragma once
#include<SimpleMath.h>
#include"../Collision/Capsule.h"

//�O���錾
class StageRead;
class Object;

class StageDraw final
{
private:

	//���[���h
	DirectX::SimpleMath::Matrix mWorld;

	//�X�e�[�W�f�[�^�̃|�C���^
	StageRead* mpStageRead;
	 
	//�X�e�[�W�̃^�C��
	std::vector<
		std::vector<
		std::unique_ptr<Object>>> mpObject;

public:

	//�R���X�g���N�^
	StageDraw();
	//�f�X�g���N�^
	~StageDraw();

	//������
	void Initialize(StageRead* pStageRead);

	//�`��
	void Draw();

	//�v���C���[�̃}�E�X���C�L���X�g�̓����蔻��
	const DirectX::SimpleMath::Vector3& ObjectCollision(const Capsule& playerCapsule);
};