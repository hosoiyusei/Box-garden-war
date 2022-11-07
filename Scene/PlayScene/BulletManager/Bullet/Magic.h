#pragma once
#include"BulletTypeBase.h"
#include"BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

class Magic :public BulletTypeBase
{
private:

	//�e�̐F
	DirectX::SimpleMath::Color mColor;

	DirectX::SimpleMath::Vector3 mPos;

	//�U����
	int mOffensivePower;

	UNIT_LEVEL mLevel;

public:

	Magic();
	~Magic();

	//�e���L���ȋ���
	const float GetLen() override { return 8.0f; }

	//�X�s�[�h�̐ݒ�
	const float GetSpeed()override { return 0.1f; }

	//�U����
	const int GetOffensivePower()override { return mOffensivePower; }

	//����
	void Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color, const UNIT_LEVEL& level)override;

	//�e�̎�ނ�Ԃ�
	const BULLET_TYPE GetType()override { return BULLET_TYPE::MAGIC; }

	//�e�̍X�V
	void Update(EffectManager* pEffectManager)override;

	//�e�̕`��
	void Draw(const DirectX::SimpleMath::Vector3& pos)override;


	const UNIT_LEVEL GetLevel()override { return mLevel; }
};