#pragma once
#include<SimpleMath.h>
#include"../../BulletManager/Bullet/BulletType.h"
#include"UnitLevel.h"
#include"../../Collision/Collision.h"

//前方宣言
class EnemyManager;
class BulletManager;
class EffectManager;

class UnitTypeBase
{
public:

	//デストラクタ
	virtual ~UnitTypeBase() = default;

	//出現したとき
	virtual void Spawn(const DirectX::SimpleMath::Vector3& pos) = 0;

	//レベルの設定
	virtual void SetLevel(const UNIT_LEVEL& level) = 0;

	//更新
	virtual void Update(
		EnemyManager* pEnemyManager
		, BulletManager* pBulletManager
		, EffectManager* pEffectManager
		, const DirectX::SimpleMath::Vector3& pos) = 0;

	//描画
	virtual void Draw(const DirectX::SimpleMath::Vector3& pos) = 0;

	//Unitのエフェクトの描画
	virtual void EffectDraw(const DirectX::SimpleMath::Vector3& pos, EffectManager* pEffectManager) = 0;

	//強化中のフラグを返す
	virtual const bool GetReinforcementFlag() = 0;

	//当たり判定を返す
	virtual const SphereCollision& GetCollision() = 0;

	//Unitのパワーアップ
	virtual void PowerUp(const SphereCollision& GetCollision, const UNIT_LEVEL& level) = 0;

	//パワーアップの解除
	virtual void Release_power_ups() = 0;

	virtual void SetColor(const DirectX::SimpleMath::Vector3& color) = 0;

	//攻撃力
	virtual const int GetPower() = 0;
};