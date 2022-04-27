#pragma once
#include<vector>
#include<SimpleMath.h>
#include"../Collision/Collision.h"
#include"Bullet/BulletType.h"
#include"../UnitManager/Unit/UnitLevel.h"

//�O���錾
class Enemy;
class EffectManager;

//�O���錾
class Bullet;

class BulletManager
{
private:

	//Bullet�̔z��
	std::vector<std::unique_ptr<Bullet>> mpBullet;

public:

	//�R���X�g���N�^
	BulletManager();
	//�f�X�g���N�^
	~BulletManager();

	//������
	void Initialize(EffectManager* pEffectManager);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�e�𔭎˂���
	void Shot(
		const DirectX::SimpleMath::Vector3& pos
		, const DirectX::SimpleMath::Vector3& target
		, const BULLET_TYPE& type
		, const int& power
		, const UNIT_LEVEL& level
		, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f));

	//�e�̓����蔻��
	bool CheckHitCollision(
		Enemy* pEnemy);
};