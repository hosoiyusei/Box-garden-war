#pragma once
#include<SimpleMath.h>

// �J�v�Z���̍\����
struct Capsule
{
	DirectX::SimpleMath::Vector3 mStart; // ���ԕ��̐����̊J�n�_
	DirectX::SimpleMath::Vector3 mEnd; // ���ԕ��̐����̏I���_

	float mRadius; // ���a

	Capsule()
		:mStart()
		, mEnd()
		, mRadius()
	{

	}

	// �J�v�Z���ƃJ�v�Z���̏Փ˔���֐�
	const bool HitCheck_Capsule2Capsule(
		  const Capsule& capsule1
		, const Capsule& capsule2);

	// �N�����v�֐�
	const float Clamp(
		  const float& n
		, const float& min
		, const float& max);

	// �Q�̐����̍ŒZ�����̕�����Ԃ��֐�
	// p1: ����1�̎n�_ q1: ����1�̏I�_
	// p2: ����2�̎n�_ q2: ����2�̏I�_
	// s: �����P��̍ŒZ�ʒu��\���W�� t: ����2��̍ŒZ�ʒu��\���W��
	// c1: �����P��̍ŒZ�����̈ʒu c2: ����2��̍ŒZ�����̈ʒu
	// �Ԃ�l: �Q�̐����̍ŒZ�����̕���
	const float ClosestPtSegmentSegment(
		  const DirectX::SimpleMath::Vector3& p1
		, const DirectX::SimpleMath::Vector3& q1
		, const DirectX::SimpleMath::Vector3& p2
		, const DirectX::SimpleMath::Vector3& q2
		, float& s
		, float& t
		, DirectX::SimpleMath::Vector3& c1
		, DirectX::SimpleMath::Vector3& c2);
};