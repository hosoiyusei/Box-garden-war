#include"pch.h"
#include"Object.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Object::Object()
	: mPos()
	, mCapsule()
	, mType(OBJECT_TYPE::NONE)
	, mWorld()
{

}

//�f�X�g���N�^
Object::~Object()
{

}

//������
void Object::Initialize(int stagetilenum)
{
	if (stagetilenum == 0)
	{
		mType = OBJECT_TYPE::TYPE_0;
	}
	else if (stagetilenum == 1)
	{
		mType = OBJECT_TYPE::TYPE_1;
	}
	else if (stagetilenum == -1)
	{
		mType = OBJECT_TYPE::TYPE_2;
	}
	else if (stagetilenum == 2)
	{
		mType = OBJECT_TYPE::TYPE_3;
	}
	else
	{
		mType = OBJECT_TYPE::TYPE_4;
	}
}

//�I�u�W�F�N�g�̍��W�̐ݒ�
void Object::SetPos(
	const float& x
	, const float& z)
{
	mPos.x = x;
	mPos.z = z;

	//Capsule�̓����蔻��̐ݒ�
	mCapsule.a = mPos;
	mCapsule.b = mPos;
	mCapsule.r = 0.6f;
}

//�`��
void Object::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	//���[���h�̏�����
	mWorld = Matrix::Identity;

	switch (mType)
	{
		case OBJECT_TYPE::TYPE_0:
		{
			mWorld = Matrix::CreateTranslation(mPos);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::White);
			break;
		}
		case OBJECT_TYPE::TYPE_1:
		{
			mWorld *= Matrix::CreateScale(1.0f, 1.0f, 1.0f);
			mWorld *= Matrix::CreateTranslation(mPos.x, 0.5f, mPos.z);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::Gray);
			break;
		}
		case OBJECT_TYPE::TYPE_2:
		{
			mWorld = Matrix::CreateTranslation(mPos.x, 0.1f, mPos.z);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::LightGreen);
			break;
		}
		case OBJECT_TYPE::TYPE_3:
		{
			mWorld = Matrix::CreateTranslation(mPos);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::Aqua);
			break;
		}
		case OBJECT_TYPE::TYPE_4:
		{
			mWorld = Matrix::CreateTranslation(mPos);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::Red);
			break;
		}
		case OBJECT_TYPE::NONE:
		{
			break;
		}
		default:
			break;
	}
}

const Vector3& Object::GetPos()
{
	switch (mType)
	{
		case OBJECT_TYPE::TYPE_0:
		{
			return Vector3(mPos.x, mPos.y + 0.6f, mPos.z);
			break;
		}
		case OBJECT_TYPE::TYPE_1:
		{
			return Vector3(mPos.x, mPos.y + 1.1f, mPos.z);
			break;
		}
		case OBJECT_TYPE::TYPE_2:
		{
			return Vector3(mPos.x, mPos.y + 0.7f, mPos.z);
			break;
		}
		case OBJECT_TYPE::TYPE_3:
		{
			return Vector3(mPos.x, mPos.y + 0.6f, mPos.z);
			break;
		}
		case OBJECT_TYPE::TYPE_4:
		{
			return Vector3(mPos.x, mPos.y + 0.6f, mPos.z);
			return mPos;
			break;
		}
		default:
			break;
	}

	return mPos;
}