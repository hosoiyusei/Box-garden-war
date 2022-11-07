#pragma once
#include<SimpleMath.h>
#include"BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//�O���錾
class EffectManager;

class BulletTypeBase
{
public:

	//�f�X�g���N�^
	virtual ~BulletTypeBase() = default;

	//�e���L���ȋ���
	virtual const float GetLen() = 0;

	//�X�s�[�h�̐ݒ�
	virtual const float GetSpeed() = 0;

	//�U����
	virtual const int GetOffensivePower() = 0;

	//����
	virtual void Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color,const UNIT_LEVEL& level) = 0;

	//�e�̎�ނ�Ԃ�
	virtual const BULLET_TYPE GetType() = 0;

	//�e�̍X�V
	virtual void Update(EffectManager* pEffectManager) = 0;

	//�e�̕`��
	virtual void Draw(const DirectX::SimpleMath::Vector3& pos) = 0;

	virtual const UNIT_LEVEL GetLevel() = 0;
};