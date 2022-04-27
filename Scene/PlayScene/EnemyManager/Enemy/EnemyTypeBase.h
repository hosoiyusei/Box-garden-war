#pragma once
#include<SimpleMath.h>
#include"EnemyLevel.h"
#include"../../BulletManager/Bullet/BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//前方宣言
class EffectManager;
class Player;

class EnemyTypeBase
{
public:

	//デストラクタ
	virtual ~EnemyTypeBase() = default;

	//Enemyを出現させる
	virtual void Spawn(EffectManager* pEffectManager,Player* pPlayer, const ENEMY_LEVEL& level) = 0;

	//移動の速さ
	virtual const float& Speed() = 0;

	//エフェクトの色の設定
	virtual const DirectX::SimpleMath::Vector3 GetEffectColor() = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw(const DirectX::SimpleMath::Vector3& pos, const float& angle) = 0;

	//エフェクトの描画
	virtual void EffectDraw(const DirectX::SimpleMath::Vector3& pos) = 0;

	//ダメージを受ける
	virtual const bool& Damage(const DirectX::SimpleMath::Vector3& pos,const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level) = 0;

	//死んでいるかどうか
	virtual const bool& Whetherdead() = 0;
};