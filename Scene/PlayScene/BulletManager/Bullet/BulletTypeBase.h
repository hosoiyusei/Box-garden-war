#pragma once
#include<SimpleMath.h>
#include"BulletType.h"
#include"../../UnitManager/Unit/UnitLevel.h"

//前方宣言
class EffectManager;

class BulletTypeBase
{
public:

	//デストラクタ
	virtual ~BulletTypeBase() = default;

	//弾が有効な距離
	virtual const float GetLen() = 0;

	//スピードの設定
	virtual const float GetSpeed() = 0;

	//攻撃力
	virtual const int GetOffensivePower() = 0;

	//発射
	virtual void Shot(const int& power, const float& angle, const DirectX::SimpleMath::Color& color,const UNIT_LEVEL& level) = 0;

	//弾の種類を返す
	virtual const BULLET_TYPE GetType() = 0;

	//弾の更新
	virtual void Update(EffectManager* pEffectManager) = 0;

	//弾の描画
	virtual void Draw(const DirectX::SimpleMath::Vector3& pos) = 0;

	virtual const UNIT_LEVEL GetLevel() = 0;
};