#include"pch.h"
#include"Collision.h"

const bool SphereCollision::CheckHit(const SphereCollision& Collision)
{
	//2�_�̈ʒu�����_����x�N�g���ɂ���
	float x = Collision.mPos.x - mPos.x;
	float y = Collision.mPos.y - mPos.y;
	float z = Collision.mPos.z - mPos.z;

	//�x�N�g���̒������v�Z
	float l = (x * x) + (y * y) + (z * z);

	//���a�̍��v���擾
	float circleLen = mRadius + Collision.mRadius;

	//���a�̍��v��2�悷��(sqrt�͏������d�����ߎg��Ȃ����߂̏��u)
	circleLen *= circleLen;

	//�x�N�g����2�̉~�̔��a���Z����Γ������Ă���
	if (l <= circleLen)
	{
		return true;
	}

	//�������Ă��Ȃ�
	return false;
}