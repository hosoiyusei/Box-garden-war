#pragma once
#include"ObjectType.h"

class Object
{
private:

	//�I�u�W�F�N�g�̍��W
	DirectX::SimpleMath::Vector3 mPos;

	//�I�u�W�F�N�g�̎��
	OBJECT_TYPE mType;

	//���[���h
	DirectX::SimpleMath::Matrix mWorld;

public:

	//�R���X�g���N�^
	Object();
	//�f�X�g���N�^
	~Object();

	//������
	void Initialize(int stagetilenum);

	//�`��
	void Draw();

	//���W�̐ݒ�
	void SetPos(
		const float& x
		, const float& z);

	//�I�u�W�F�N�g�̍��W��Ԃ�
	const DirectX::SimpleMath::Vector3 GetPos();

	//�I�u�W�F�N�g�̎�ނ�Ԃ�
	const OBJECT_TYPE GetType()
	{
		return mType;
	}
};