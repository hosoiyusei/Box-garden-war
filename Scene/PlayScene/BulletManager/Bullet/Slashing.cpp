#include"pch.h"
#include"Slashing.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Slashing::Slashing()
	:mOffensivePower(0)
{

}

//�f�X�g���N�^
Slashing::~Slashing()
{

}

//����
void Slashing::Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)
{
	mOffensivePower = power;
	mLevel = level;
}

//�`��
void Slashing::Draw(const Vector3& pos)
{
	//�x������
	pos;
}